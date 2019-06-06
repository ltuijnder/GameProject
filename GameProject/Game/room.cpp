#include "room.h"
#include "SceneObjects/sceneobject.h"
//#include "SceneObjects/dummyellipse.h"
#include "SceneObjects/testqobject.h"
#include "SceneObjects/player.h"
#include "SceneObjects/wall.h"
#include "SceneObjects/Enemies/enemies.h"
#include "SceneObjects/Enemies/runner.h"

/******* Essential Functions *******/

Room::Room(QObject *parent) : QGraphicsScene(parent)
{

}

Room::~Room(){
    //delete Objects;// Deletes the vector, but not the Objects in the vector! However this is done by the scene automaticly.
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
    //Objects=new std::vector<SceneObject*>;// Dynamically allocate the vector.

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
        Elli0->Init(this);// Important
        Elli0->setPos(200,-200);
        addItem(Elli0);

        Wall *Brick=new Wall;
        Brick->Init(this);
        Brick->setPos(125,125);
        addItem(Brick);

        Wall *Brick2=new Wall;
        Brick2->Init(this);
        Brick2->setPos(100,175);
        addItem(Brick2);

        // Ad our first enemy.
        Runner *Satan= new Runner;
        Satan->Init(this);
        Satan->setPos(-400,-400);
        addItem(Satan);

    }else{
        TestQobject *Elli1=new TestQobject;
        Elli1->Init(this);// Important
        Elli1->setPos(200,-200);
        addItem(Elli1);

        Wall *Brick=new Wall;
        Brick->Init(this);
        Brick->setPos(-125,-125);
        addItem(Brick);
    }
    IsFilled=1;
}

void Room::DeleteSceneObject(SceneObject *ToDelete){
    removeItem(ToDelete);// Remove the QGraphicsItems from scene
    delete ToDelete;// Finally delete de dynamicly allocated memory.
}


/******* Functions *******/


void Room::SetRoomType(int Type){
    RoomType=Type;
    RoomTypeIsSet=1;
}

void Room::SetRoomPosition(int Pos){
    Position=Pos;
}

int Room::NumberOfEnemies(){
    int Amount=0;
    QList<QGraphicsItem *> ItemsList=items();
    for(auto Item:ItemsList){
        int type=Item->type();
        if(type>=Enemies::Type && type<Enemies::Type_EnemiesMAX){
            Amount++;
        }
    }
    return Amount;
}

std::vector<SceneObject *> Room::collidingObjects(SceneObject *Object){
    QList<QGraphicsItem *> GraphicsItemsList=collidingItems(Object);
    std::vector<SceneObject *> ObjectsList;
    for(auto GraphicsItem:GraphicsItemsList){
        ObjectsList.push_back(dynamic_cast<SceneObject *>(GraphicsItem));
    }
    return ObjectsList;
}


void Room::TestDowncast(){// Delete this
     QList<QGraphicsItem *> ItemsList=items();
     for(auto Item:ItemsList){
         // Down try to down cast. And not do QGraphcisCast.
         SceneObject* MySceneObject=dynamic_cast<SceneObject *>(Item);
         MySceneObject->TestFunc();
     }
}
