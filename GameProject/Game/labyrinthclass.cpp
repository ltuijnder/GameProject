#include "labyrinthclass.h"
#include "gameclass.h"
#include "scenemanager.h"
#include "room.h"
#include "labyrinthclass.h"

/******* Essential Functions *******/

LabyrinthClass::LabyrinthClass(QObject *parent) : QObject(parent)// Call constructer of inherted classes.
{
    //Nothing
}

LabyrinthClass::~LabyrinthClass(){
    // Maybe just call clear floor?
    for(auto PointerToRoom:*Floor){
        delete PointerToRoom;
    }
    delete Floor;
    delete Floorplan;// calls the deconstructor of Floorplan
}

void LabyrinthClass::Setup(GameClass *Game){
    //Flags
    LayoutIsGenerated=0;
    FloorIsGenerated=0;
    IsStarted=0;
    IsLoaded=0;

    //Variables
    Level=0;
    Floor=new std::vector<Room*>;// Change QGraphicsScene to Room
    Floorplan=new Layout;
    Floorplan->SetUp(this);
    Floorplan->setSideLength(Level);// Important set the level.
    TESTCurrentNumber=0;// REMOVE

    //Links
    QObject::connect(this,SIGNAL(ChangeScene(Room*)),Game->SManager,SLOT(ChangeCurrentScene(Room*)));
    QObject::connect(Game,SIGNAL(GameHasStarted()),this,SLOT(StartLayout()));

    IsSetup=1;

}

/******* SLOTS *******/

void LabyrinthClass::StartLayout(){
    // Maybe emit Loading screen!
    if(!IsLoaded){// if no previous game has been loaded we random generate a new one.
        //GenerateNewFloor();
        Floorplan->generateLayout();
        Floorplan->FillFloor(Floor);
        FloorIsGenerated=1;
    }
    // The we send the StartSecene to Scene Manager
    emit ChangeScene(Floor->at(Floorplan->FloorIndex()));

    //emit ChangeScene(Floor->at(TESTCurrentNumber));
    IsStarted=1;
}


void LabyrinthClass::TESTPressedC(){// REMOVE ME
    if(TESTCurrentNumber==0){
        emit ChangeScene(Floor->at(1));// Here we up cast the Object Room to QGraphicsScene!
        TESTCurrentNumber=1;
    }else{
        emit ChangeScene(Floor->at(0));
        TESTCurrentNumber=0;
    }
}

void LabyrinthClass::ChangeRoom(unsigned Direction){
    if(!Floorplan->ValidDirection(Direction)){
        std::cout<<"Error LabyrinthClass::ChangeRoom invalid direction "<<std::endl;
        return;
    }
    emit ChangeScene(Floor->at(Floorplan->NextRoomIndex(Direction)));
}

void LabyrinthClass::GenerateNewFloor(){
    if(FloorIsGenerated) ClearFloor(); //Clear previous floor (if there is one)
    GenerateLayout();
    emit GenerateRooms();
    FloorIsGenerated=1;
}

/******* Functions *******/

// This is outdated. But is still used for manual making.
// But to create really you shoot use Floorplan->Layout.
void LabyrinthClass::GenerateLayout(){
    if(LayoutIsGenerated){
        std::cout<<"Error: Layout has already been generated, First delete the old floor"<<std::endl;
        return;
    }
    // Now we do some generation stuff here (still don't really now How I'm going to do it)
    // Probabily create the variable layout, and based on variable layout set the rooms type via for loop.
    // For now just create 2 rooms.
    Floor->push_back(new Room);
    Floor->push_back(new Room);
    for(auto PointerToRoom:*Floor){// Loop over the "empty" Rooms
        PointerToRoom->Setup(this);// First setup should always be called to set all the default values of room good
        // Set up the type based on the layout generated? Then maybe for needs to changed... for now do it outside the forloop
        QObject::connect(this,SIGNAL(GenerateRooms()),PointerToRoom,SLOT(FillUp()));// Establish connection allowing the rooms to generate
    }
    Floor->at(0)->SetRoomType(0);// Create its types
    Floor->at(1)->SetRoomType(1);

    LayoutIsGenerated=1;
}

void LabyrinthClass::ClearFloor(){// Probabibly some deletes here.
    if(LayoutIsGenerated){// clear Layout
        //Pass
    }
    if(FloorIsGenerated){// Clear floor
        //Pass
    }
    LayoutIsGenerated=0;
    FloorIsGenerated=0;
}

QString LabyrinthClass::SaveHeader(){
    QString savestring("");
    savestring.append("--");// Let "," be the splitter on this level
    // Save information just from LabyrinthClass
    savestring.append(",");
    savestring.append(QString::number(Level));
    savestring.append(",");
    // Save Layout
    savestring.append("--");
    savestring.append(Floorplan->Save());
    savestring.append("--");
    return savestring;
}

void LabyrinthClass::LoadHeader(QString str){
    if(!IsSetup){// if NOT setup then not persuit
        std::cout<<"Error LabyrinthClass::LoadHeader the class was not setup"<<std::endl;
        return;
    }else if(LayoutIsGenerated){// if IS generated then not persuit
        std::cout<<"Error LabyrinthClass::LoadHeader the layout was already generated"<<std::endl;
        return;
    }
    QStringList strL=str.split("--");
    QStringList strL2=strL[1].split(",");
    // Load specific information
    Level=strL2[1].toInt();

    // Load Layout
    Floorplan->Load(strL[2]);
    //LoadLayout(strL[2]);

    LayoutIsGenerated=1;
}



QString LabyrinthClass::SaveRooms(){
    QString stringrooms("");
    stringrooms.append("**Room**\n");
    for(auto room:*Floor){
        stringrooms.append("***RoomHeader***\n");
        stringrooms.append(room->SaveHeader());// This all information just associated to the room it self.
        stringrooms.append("***RoomHeader***\n");
        stringrooms.append(room->SaveObjects());
        stringrooms.append("***RoomHeader***\n");
        stringrooms.append("**Room**\n");
    }
    return stringrooms;
}

void LabyrinthClass::LoadFloor(QString str){
    if(!IsSetup){// if NOT setup then not persuit
        std::cout<<"Error LoadFloor, the labyrinthClass was not setup!"<<std::endl;
        return;
    }if(FloorIsGenerated){// if IS generated then not persuit
        std::cout<<"Error LoadFloor, the labyrinthClass floor was already generated."<<std::endl;
        return;
    }
    QStringList strL=str.split("**Room**");
    for(int i=1;i<strL.size()-1;i++ ){// Work for int rather then range based loop since we want don't want to accest the first and the last element
        QString RoomHeader=strL[i].section("***RoomHeader***",1,1);
        QString SceneObjects=strL[i].section("***RoomHeader***",2,2);
        Room *newRoom =new Room;
        newRoom->Setup(this);

        newRoom->LoadHeader(RoomHeader);
        newRoom->LoadObjects(SceneObjects);
        Floor->push_back(newRoom);
    }
    FloorIsGenerated=1;
    IsLoaded=1;
}
