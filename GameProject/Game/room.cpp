#include "room.h"
//#include "graphicsitems.h" // Just now for the moment of adding ellipse
#include "SceneObjects/sceneobject.h"
#include "SceneObjects/dummyellipse.h"

/******* Essential Functions *******/

Room::Room(QObject *parent) : QGraphicsScene(parent)
{

}

Room::~Room(){
    delete Objects;// Deletes the vector, but not the Objects in the vector! However this is done by the scene automaticly.
}

void Room::Setup(){
    if(IsSetup){//  let rooms only be setup once.
        std::cout<<"ERROR: In Class Room: Room was already Setup"<<std::endl;
        return;
    }
    // Bools
    IsFilled=0;
    RoomTypeIsSet=0;

    // Variables
    RoomType=0;
    Position=0;
    Objects=new std::vector<SceneObject*>;// Dynamically allocate the vector.

    IsSetup=1;
}

/******* SLOTS *******/

void Room::FillUp(){
    if(!RoomTypeIsSet){
        std::cout<<"ERROR: In Class Room: Tried to fillUp without a roomtype being set"<<std::endl;
        return;
    }
    // Fill up the room (Do this by calling Load Room Or something some functionality I haven't thought out yet)
    // For now just use 2 rooms, With room 0 being type 0 and room 1 being type 1;
    if(RoomType==0){
        //Ellipse *Elli0=new Ellipse;
        DummyEllipse *Elli0=new DummyEllipse;
        Elli0->Init();// Important
        Objects->push_back(Elli0);// Here DummyEllipse gets converted to SceneObject
        addItem(Elli0);
    }else{
        DummyEllipse *Elli1=new DummyEllipse;
        Elli1->Init();// Important
        Objects->push_back(Elli1);// Here DummyEllipse gets converted to SceneObject
        addItem(Elli1);
    }
    IsFilled=1;
}


/******* Functions *******/


void Room::SetRoomType(int Type){
    RoomType=Type;
    RoomTypeIsSet=1;
}

void Room::SetRoomPosition(int Pos){
    Position=Pos;
}

void Room::TESTdx(double dxnew){
    // Will not work. :/
}




