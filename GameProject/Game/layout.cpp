#include "layout.h"
#include "room.h"// It doesn't like to be in the .h file. We get errors then

// Essentials

Layout::Layout()
{
    //
}

Layout::~Layout(){
    for(auto layoutelements:*layout){// Can this be done more efficient?
        delete layoutelements;
    }

}

void Layout::SetUp(LabyrinthClass *ptoLaby){
    LayoutIsGenerated=0;
    LayoutIsAllocated=0;

    floor_Index=-1;
    layoutIndex=-1;
    SideLength=0;
    PointerToLaby=ptoLaby;
    layout=new std::vector<Layoutelement *>;

    IsSetup=1;
}



// Functions


int Layout::to1D(unsigned row, unsigned column){
    if(row>SideLength||column>SideLength){// aka overflow.
        std::cout<<"Error: overflow in LabyrinthClass::to1D. (row,column)=("<<row<<","<<column<<") exceeds lenght="<<SideLength<<std::endl;
        return -1;// use it as a flag.
    }
    return row*SideLength+column;
}


void Layout::printLayout(){
    unsigned column=0;
    for(auto element:*layout){
        std::cout<<element->FIndex();// Put here what you want to print.
        if(column+1==SideLength){
            std::cout<<std::endl;
            column=0;
        }else{
            std::cout<<" ";
            column++;
        }
    }
}

bool Layout::createEmptyLayout(){
    if(!IsSetup){// If NOT setup then throw error
        std::cout<<"Error Layout::createEmptyLayout, Layout object is not setup"<<std::endl;
        return 0;
    }
    if(LayoutIsAllocated){// if ALREADY allocated throw error.
        std::cout<<"Error Layout::createEmptyLayout, Layout was already allocated"<<std::endl;
        return 0;
    }
    for(unsigned i=0;i<SideLength*SideLength;i++){// Can this be done more efficient?
        Layoutelement *newelement=new Layoutelement;// Default constructer sets it automaticly on no room.
        newelement->setLIndex(i);
        layout->push_back(newelement);
    }
    LayoutIsAllocated=1;
    return 1;
}

void Layout::setElementIndex(){
    if(!LayoutIsAllocated){
        std::cout<<"Error Layout::setElementIndex, layout was not allocated"<<std::endl;
        return;
    }
    int f_index=0;
    for(auto elements:*layout){
        if(elements->IsRoom()){
            elements->setFIndex(f_index);
            f_index++;
        }
    }
}

void Layout::setDoorType(){
    for(auto elem:*layout){
        if(elem->IsRoom()){
            int type=0;
            int row=elem->Row(SideLength);
            int col=elem->Col(SideLength);
            if(!(row-1<0)){// we are not at the top;
                if(layout->at(to1D(row-1,col))->IsRoom()) type=type|1;//UP: bitwise or operator with 0001
            }if(!(col+1>=SideLength)){// We are not at the far most right side
                if(layout->at(to1D(row,col+1))->IsRoom()) type=type|2;//RIGHT: bitwise or operator with 0010
            }if(!(row+1>=SideLength)){// We are not at the bottom
                if(layout->at(to1D(row+1,col))->IsRoom()) type=type|4;//DOWN: bitwise or operator with 0100
            }if(!(col-1<0)){// We are not at the far most left side
                if(layout->at(to1D(row,col-1))->IsRoom()) type=type|8;//LEFT: bitwise or operator with 1000
            }
            elem->setDoorType(type);
        }
    }
}

bool Layout::ValidDirection(unsigned dir){
    // Check if layout is setup in the first place
    if(!IsSetup){
        std::cout<<"Error Layout::ValidDirection, Layout object is not setup"<<std::endl;
        return 0;
    }
    // First check if Direction is just a valid entry
    if(!(dir==0||dir==1||dir==2||dir==3)){// Use Door::Direction for this
        return 0;
    }
    // Next simply check if we are not go out of boundry.
    int Row=layoutIndex/SideLength;
    int Column=layoutIndex%SideLength;
    switch (dir) {
    case 0:// Right
        if(Column+1>=SideLength){// Do >= if for some weird reason the Row was already wrong
            return 0;
        }else{
            Column++;// If everything is ok update the column/row for the next check
        }
        break;
    case 1:// Left
        if(Column-1<0){
            return 0;
        }else{
            Column--;
        }
        break;
    case 2:// Up
        if(Row-1<0){
            return 0;
        }else{
            Row--;
        }
        break;
    case 3:// Down
        if(Row+1>=SideLength){
            return 0;
        }else{
            Row++;
        }
        break;
    }
    // Lastly check if there is really a room there.
    if(layout->at(to1D(Row,Column))->IsRoom()){
        return 1;
    }
    return 0;
}


unsigned Layout::NextRoomIndex(unsigned Direction){
    if(ValidDirection(Direction)){
        int row=layoutIndex/SideLength;
        int column=layoutIndex%SideLength;
        switch (Direction) {
        case 0:// right Use Door::Right
            column++;
            break;
        case 1:// left
            column--;
            break;
        case 2:// Up
            row--;// remembre that the top row is 0;
            break;
        case 3:
            row++;
            break;
        }
        layoutIndex=to1D(row,column);
        floor_Index=layout->at(layoutIndex)->FIndex();
        return floor_Index;
    }else{
        std::cout<<"Error NextRoomIndex: invalid entry or direction"<<std::endl;
        return -1;
    }
}

void Layout::setSideLength(int level){
    SideLength=5+level*2;
}

void Layout::FillFloor(std::vector<Room *> *Floor){
    if(!IsSetup){
        std::cout<<"Error Layout::FillFloor, Layout object is not setup"<<std::endl;
        return;
    }if(!LayoutIsGenerated){
        std::cout<<"Error Layout::FillFloor, Layout is not generated"<<std::endl;
        return;
    }
    // Go to the directory where the templates are.
    QDir dir=QDir::home();// Start from home folder.
    try{
        if(!dir.cd(".GameProject")) throw "HOME/.GameProject";
        dir.cd(".GameProject");
        if(!dir.cd("Templates")) throw "HOME/.GameProject/Templates";
        dir.cd("Templates");
    }catch(const char* msg){
        std::cout<<"Error directory '"<<msg<<"' does not exist"<<std::endl;
    }
    // Create the random number generator that will help us guide to pick the room.
    int seed=42;
    std::default_random_engine generator (seed);// For explanation look at: http://www.cplusplus.com/reference/random/uniform_int_distribution/operator()/

    // Now we loop over every room in the layout. And again go to the correct subfolder.
    for(auto room:*layout){
        if(room->IsRoom()){
            try{
                CdTemplateType(dir,room->doorType());
            }catch(int DoorType){
                std::cout<<"Error Template directory '"<<DoorType<<"' does not exist"<<std::endl;
                continue;
            }
            // Get a list of all the files While we also remove the 2 trivial ones
            QStringList StringList=dir.entryList(QStringList()<<"*.txt",QDir::Files);// We only want to look at files that end with .txt
            if(StringList.size()==0){
                dir.cdUp();// Important go back up.
                continue;//If no rooms are given we cannot go further
            }
            // Now we are going to randomly pick an entry. If neccessary we can even apply filters in entryList if we want to be more specific.
            std::uniform_int_distribution<int> Distr(0,StringList.size()-1);// Do minus one because we Stringlist.at(StringList.size()) is overflow.
            Distr(generator); // The number is ALWAYS zero for some weird reason so that why we random generate here for nothing.
            QString RoomFile=StringList.at(Distr(generator));

            // Now open the content of the file.
            std::string filename(dir.path().toStdString()+"/"+RoomFile.toStdString());
            std::ifstream file(filename.c_str());
            if(!file){
                std::cout<<"Error in FillFloor couldn't open "<<filename<<std::endl;
                dir.cdUp();// Important go back up.
                continue;
            }
            std::stringstream buffer;// The reason for this very complicated conversion thing can be motivated by the following
            buffer<< file.rdbuf();// See second answer: https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
            std::string stdstring=buffer.str();// https://stackoverflow.com/questions/662976/how-do-i-convert-from-stringstream-to-string-in-c
            QString FileContent=QString::fromUtf8(stdstring.data(),stdstring.size());// Togheter with comment: https://stackoverflow.com/questions/4338067/convert-stdstring-to-qstring

            // Finally after a long series of conversion and openings we allocate the new room and load it. Then add it to Floor.
            //std::cout<<FileContent.toStdString()<<std::endl;
            Room *newRoom=new Room;
            newRoom->Setup(PointerToLaby);
            QString RoomHeader=FileContent.section("***RoomHeader***",1,1);
            QString SceneObjects=FileContent.section("***RoomHeader***",2,2);
            newRoom->LoadHeader(RoomHeader);
            newRoom->LoadObjects(SceneObjects);
            Floor->push_back(newRoom);


            dir.cdUp();// Important go back up.
        }
    }

}

bool Layout::IsLayoutGenerated(){
    return LayoutIsGenerated;
}

int Layout::FloorIndex(){
    return floor_Index;
}

//---------------------------------
/**** Random number generation ****/
//---------------------------------

bool Layout::generateLayout(){
    if(!IsSetup){
        std::cout<<"Error Layout::generateLayout, Layout object is not setup"<<std::endl;
        return 0;
    }
    if(LayoutIsGenerated){
        std::cout<<"Error Layout::generateLayout, Layout object is already generated"<<std::endl;
        return 0;
    }
    if(!createEmptyLayout()){// Create an empty layout. And check if it succeeded
        std::cout<<"Error Layout::generateLayout, Layout object is already allocated"<<std::endl;
        return 0;
    }
    // Now do the random generation stuff.
    int seed=42;
    std::default_random_engine generator (seed);// For explanation look at: http://www.cplusplus.com/reference/random/uniform_int_distribution/operator()/
    std::uniform_int_distribution<int> Distr(0,SideLength*SideLength-1);

    // First choose a random start point.
    Distr(generator);// For some VERY weird reason. The first number is ALWAYS zeros, so let it run one time.
    int R1_LIndex=Distr(generator);

    int level=(SideLength-5)/2;

    // Now Choose a second random point. But this one needs to be some minimum distance away.
    std::vector<int> Options;// The viable Lindexes.
    int minDist=4+level*2;// !! DO THIS BETTER // the minimum distance between the first 2 points.
    FurtherThen(minDist,R1_LIndex,Options);
    std::uniform_int_distribution<int> DistrOption(0,Options.size()-1);// Make distribution with the correct vary size.
    int R2_LIndex=Options.at(DistrOption(generator));// Randomly choose our second point

    // Now connect these two point by setting the rooms inbetween.
    std::uniform_int_distribution<int> CoinFlip(0,1);// We need a coinflip. To determine which way we are going to connect the the 2 paths.
    ConnectTwoPoints(R1_LIndex,R2_LIndex,CoinFlip(generator));

    // Now we choose a extra points. Demanding also some required distance.
    // For now just choose a third point. at a distance dependend on level
    minDist=3+level;
    int R3_LIndex;
    int ClosestToR3;
    do{
        R3_LIndex=Distr(generator);
        ClosestRooms(R3_LIndex,Options);
        std::uniform_int_distribution<int> TempDist(0,Options.size()-1);// this is local in the scope of while so gets destroyed everytime. Which is needed since Option will vary size
        ClosestToR3=Options.at(TempDist(generator));
        //std::cout<<"Row:"<<R3_LIndex/SideLength<<" Col:"<<R3_LIndex%SideLength<<" CL_row"<<ClosestToR3/SideLength<<" CL_col"<<ClosestToR3%SideLength<<" distance="<<dist(R3_LIndex,ClosestToR3)<<std::endl;

    }while(dist(R3_LIndex,ClosestToR3)<minDist);
    ConnectTwoPoints(R3_LIndex,ClosestToR3,CoinFlip(generator));// Maybe to get desired effect don't connect to closest room.

    // Now choose a start position.
    Options.clear();
    for(auto element:*layout){
        if(element->IsRoom()){
            Options.push_back(element->LIndex());
        }
    }
    std::uniform_int_distribution<int> DistrOption3(0,Options.size()-1);// this is stupid.
    layoutIndex=Options.at(DistrOption3(generator));
    std::cout<<layoutIndex/SideLength<<" "<<layoutIndex%SideLength<<std::endl;

    // Now that everything is generated. Determine the floor index of each floor.
    setElementIndex();
    setDoorType();

    printLayout();
    // set the floor index.
    floor_Index=layout->at(layoutIndex)->FIndex();// Important that this is after
    LayoutIsGenerated=1;
    return 1;
}

void Layout::ClosestRooms(int Lindex,std::vector<int> &Solution){
    // This is ineffiecient. but it will do for now.
    Solution.clear();// delete what might have been init.
    int minDist=SideLength+SideLength;
    for(auto element:*layout){
        if(element->IsRoom()){
            int LI=element->LIndex();
            int d=dist(Lindex,LI);
            if(d<minDist){
                minDist=d;
                Solution.clear();// we found a new minimum thus all that was safed. remove it
                Solution.push_back(LI);
            }else if(d==minDist){// We found another room that is on par of minimum.
                Solution.push_back(LI);
            }
        }
    }
}

// Does not work fix it later. !
void Layout::FurtherThenFromLayout(int d, std::vector<int> &Solution){// One could upgrade this function by doing a specific range of distances. Also upgrade FurtherThen!
    std::vector<int> Rooms;// create a vector that contains all the rooms.
    for(auto element:*layout){// Fill Rooms
        if(element->IsRoom()){
            Rooms.push_back(element->LIndex());
        }
    }
    // Now we loop over every room
    std::vector<int> Sol;// Create a temp vector that already will hold solution
    for(auto room:Rooms){
        std::vector<int> buffer;
        FurtherThen(d,room,buffer);// Fill buffer with all the correct solution seen form room.
        std::cout<<std::endl;
        Sol.insert(Sol.end(),buffer.begin(),buffer.end());// Add the 2 vectors together based on:https://stackoverflow.com/questions/201718/concatenating-two-stdvectors
        // Now we need to remove duplicates in buffer. we follow: https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
        std::sort(Sol.begin(), Sol.end());// First sort everything
        Sol.erase( std::unique( Sol.begin(), Sol.end() ), Sol.end() );// Then push all the unique elements forward. and then erase the elements that are pushed backwards (which are the dublicates)
    }
    Solution=Sol;// So here we reset everything that was in Solution!
}

int Layout::dist(int refLindex, int othLindex){
    int drow=std::abs(refLindex/SideLength-othLindex/SideLength);
    int dcol=std::abs(refLindex%SideLength-othLindex%SideLength);
    return drow+dcol;
}

void Layout::FurtherThen(int d,int refLindex, std::vector<int> &Solution){
    for(auto element:*layout){
        if(dist(refLindex,element->LIndex())>=d){
            Solution.push_back(element->LIndex());
        }
    }
}

void Layout::ConnectTwoPoints(int Lindex1, int Lindex2, bool b){
    int row1=Lindex1/SideLength;
    int col1=Lindex1%SideLength;// for debugging use-> std::cout<<" Row1:"<<row1<<" Col1:"<<col1<<" Row2:"<<row2<<" Col2:"<<col2<<std::endl;
    int row2=Lindex2/SideLength;
    int col2=Lindex2%SideLength;
    bool r=row2>row1;
    bool c=col2>col1;
    if(b){// We do first the row.
        for(;r?row1<=row2:row1>=row2;r?row1++:--row1){// Based on the bool r we either go up with row1 or down.
            //std::cout<<"Test1 row1:"<<row1<<" col1:"<<col1<<std::endl;
            layout->at(to1D(row1,col1))->setRoom(1);
        }r?row1--:row1++;// In the for loop we overschoted the variable row by 1. so undo it.
        for(;c?col1<=col2:col1>=col2;c?col1++:col1--){
            layout->at(to1D(row1,col1))->setRoom(1);
        }// Here we again overschot but the function is finished so no need to correct it.
    }else{// Here we do firt the column.
        for(;c?col1<=col2:col1>=col2;c?col1++:col1--){
            layout->at(to1D(row1,col1))->setRoom(1);
        }c?col1--:col1++;
        for(;r?row1<=row2:row1>=row2;r?row1++:row1--){
            layout->at(to1D(row1,col1))->setRoom(1);
        }r?row1--:row1++;
    }
}


// Just a big switch no need to put it in betwee the functions just put it at the end.

void Layout::CdTemplateType(QDir &dir,int DoorType){
    switch (DoorType) {
    case 0:// No doors
        if(!dir.cd("Plate_0")) throw DoorType;
        dir.cd("Plate_0");
        break;
    case 1:// Up
        if(!dir.cd("Plate_1")) throw DoorType;
        dir.cd("Plate_1");
        break;
    case 2:// Right
        if(!dir.cd("Plate_2")) throw DoorType;
        dir.cd("Plate_2");
        break;
    case 3:// Up+Right
        if(!dir.cd("Plate_3")) throw DoorType;
        dir.cd("Plate_3");
        break;
    case 4:// Down
        if(!dir.cd("Plate_4")) throw DoorType;
        dir.cd("Plate_4");
        break;
    case 5:// Down+Up
        if(!dir.cd("Plate_5")) throw DoorType;
        dir.cd("Plate_5");
        break;
    case 6:// Down+Right
        if(!dir.cd("Plate_6")) throw DoorType;
        dir.cd("Plate_6");
        break;
    case 7:// Down+Up+Right
        if(!dir.cd("Plate_7")) throw DoorType;
        dir.cd("Plate_7");
        break;
    case 8:// Left
        if(!dir.cd("Plate_8")) throw DoorType;
        dir.cd("Plate_8");
        break;
    case 9:// Left+Up
        if(!dir.cd("Plate_9")) throw DoorType;
        dir.cd("Plate_9");
        break;
    case 10:// Left+Right
        if(!dir.cd("Plate_10")) throw DoorType;
        dir.cd("Plate_10");
        break;
    case 11:// Left+Up+Right
        if(!dir.cd("Plate_11")) throw DoorType;
        dir.cd("Plate_11");
        break;
    case 12:// Left+Down
        if(!dir.cd("Plate_12")) throw DoorType;
        dir.cd("Plate_12");
        break;
    case 13:// Left+Down+Up
        if(!dir.cd("Plate_13")) throw DoorType;
        dir.cd("Plate_13");
        break;
    case 14:// Left+Down+Right
        if(!dir.cd("Plate_14")) throw DoorType;
        dir.cd("Plate_14");
        break;
    case 15:// Left+Down+Up+Right
        if(!dir.cd("Plate_15")) throw DoorType;
        dir.cd("Plate_15");
        break;
    default:
        throw DoorType;
        break;
    }
}
