#include "labyrinthclass.h"
#include "gameclass.h"
#include "scenemanager.h"
#include "graphicsitems.h" // Just for the test to include the ellipse

/******* Essential Functions *******/

LabyrinthClass::LabyrinthClass(QObject *parent) : QObject(parent)
{
    //Nothing
}

LabyrinthClass::~LabyrinthClass(){
    for(auto PointerToRoom:*VRooms){
        delete PointerToRoom;
    }
    delete VRooms;
}

void LabyrinthClass::Setup(GameClass *Game){
    //Flags
    LayoutIsGenerated=0;
    RoomsAreFilled=0;
    //Variables
    Level=0;
    VRooms=new std::vector<QGraphicsScene*>;// In begin empty
    TESTCurrentNumber=0;

    // Generate SUch that VRoom is filled:
    GenerateLayout();

    //Links
    QObject::connect(this,SIGNAL(ChangeScene(QGraphicsScene*)),Game->SManager,SLOT(ChangeCurrentScene(QGraphicsScene*)));
    QObject::connect(Game,SIGNAL(GameHasStarted()),this,SLOT(StartLayout()));
}

/******* SLOTS *******/

void LabyrinthClass::StartLayout(){
    // The we send the StartSecen to Scene Maneger
    emit ChangeScene(VRooms->at(TESTCurrentNumber));
    IsStarted=1;
}


void LabyrinthClass::TESTPressedC(){
    if(TESTCurrentNumber==0){
        emit ChangeScene(VRooms->at(1));
        TESTCurrentNumber=1;
    }else{
        emit ChangeScene(VRooms->at(0));
        TESTCurrentNumber=0;
    }
}


/******* Functions *******/

void LabyrinthClass::GenerateLayout(){// this is test
    if(LayoutIsGenerated){
        std::cout<<"Error: Layout has already been generated, First delete the old floor"<<std::endl;
        return;
    }
    // Next is just for the test now.
    VRooms->push_back(new QGraphicsScene);
    VRooms->push_back(new QGraphicsScene);
    Ellipse *Elli1=new Ellipse;
    Ellipse *Elli2=new Ellipse;
    VRooms->at(0)->addItem(Elli1);
    VRooms->at(1)->addItem(Elli2);
}
