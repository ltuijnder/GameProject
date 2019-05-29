#include "room.h"
#include "SceneObjects/sceneobject.h"
//#include "SceneObjects/dummyellipse.h"
#include "SceneObjects/testqobject.h"
#include "SceneObjects/player.h"
#include "SceneObjects/wall.h"

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
        TestQobject *Elli0=new TestQobject;
        Elli0->Init();// Important     
        Objects->push_back(Elli0);// Here DummyEllipse gets converted to SceneObject
        Elli0->setPos(200,-200);
        addItem(Elli0);

        Wall *Brick=new Wall;
        Brick->Init();
        Brick->setPos(125,125);
        addSceneObject(Brick);

        Wall *Brick2=new Wall;
        Brick2->Init();
        Brick2->setPos(100,175);
        addSceneObject(Brick2);


    }else{
        TestQobject *Elli1=new TestQobject;
        Elli1->Init();// Important
        Elli1->setPos(200,-200);
        Objects->push_back(Elli1);// Here DummyEllipse gets converted to SceneObject
        addItem(Elli1);

        Wall *Brick=new Wall;
        Brick->Init();
        Objects->push_back(Brick);
        Brick->setPos(-125,-125);
        addItem(Brick);
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

void Room::addSceneObject(SceneObject *NewObject){
    // we don't do the init here, since one might first want to change some properties of the object
    // Before adding to the scene.
    Objects->push_back(NewObject);
    addItem(NewObject);
}

