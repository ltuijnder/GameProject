#include "labyrinthclass.h"
#include "gameclass.h"
#include "scenemanager.h"
#include "room.h"

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
}

void LabyrinthClass::Setup(GameClass *Game){
    //Flags
    LayoutIsGenerated=0;
    FloorIsGenerated=0;
    IsStarted=0;

    //Variables
    NextLevel=0;
    Floor=new std::vector<Room*>;// Change QGraphicsScene to Room
    TESTCurrentNumber=0;// REMOVE

    // Generate SUch that Floor is filled:
    //GenerateLayout();
    BuildFloor();

    Floor->at(0)->TestDowncast();// THIS WORKS (DELETE THIS) HEY YOU YEAH YOU DELETE THIS

    //Links
    QObject::connect(this,SIGNAL(ChangeScene(Room*)),Game->SManager,SLOT(ChangeCurrentScene(Room*)));
    QObject::connect(Game,SIGNAL(GameHasStarted()),this,SLOT(StartLayout()));

}

/******* SLOTS *******/

void LabyrinthClass::StartLayout(){
    // The we send the StartSecen to Scene Manager
    emit ChangeScene(Floor->at(TESTCurrentNumber));
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

void LabyrinthClass::RoomTransfer(char Direction){
    // Pass
}


/******* Functions *******/

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
        PointerToRoom->Setup();// First setup should always be called to set all the default values of room good
        // Set up the type based on the layout generated? Then maybe for needs to changed... for now do it outside the forloop
        QObject::connect(this,SIGNAL(GenerateRooms()),PointerToRoom,SLOT(FillUp()));// Establish connection allowing the rooms to generate
    }
    Floor->at(0)->SetRoomType(0);// Create its types
    Floor->at(1)->SetRoomType(1);

    LayoutIsGenerated=1;
}

void LabyrinthClass::BuildFloor(){
    if(FloorIsGenerated) ClearFloor(); //Clear previous floor (if there is one)
    GenerateLayout();
    emit GenerateRooms();
    FloorIsGenerated=1;
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

QString LabyrinthClass::SaveRooms(){
    QString stringrooms("");
    for(auto room:*Floor){
        stringrooms.append("**Room**\n");
        stringrooms.append("***RoomHeader***\n");
        //stringrooms.append(room->SaveHeader());// This all information just associated to the room it self.
        stringrooms.append("***RoomHeader***\n");
        stringrooms.append(room->SaveObjects());
        stringrooms.append("**Room**\n");
    }
    return stringrooms;
}
