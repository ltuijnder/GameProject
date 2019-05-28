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
        Objects->push_back(Brick);
        Brick->setPos(125,125);
        addItem(Brick);
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

void Room::TESTdx(double dxnew){
    // Armed with new knowledge we can tackle the problem
    QList<QGraphicsItem *>Items=items();// returns a QList of all GraphicsItems in the
    // Lets check what the type is of the item
    QGraphicsItem *Item=Items.at(0);
    if(Item->type()==SceneObject::Type){
        std::cout<<"Type=SceneObject"<<std::endl;
    }else if (Item->type()==TestQobject::Type) {
        std::cout<<"Type=DummyEllipse"<<std::endl;
        TestQobject *PElli=qgraphicsitem_cast<TestQobject *>(Item);// Works
        PElli->TestFunc();
        double dx=PElli->TestGetParm();
        std::cout<<"Extracted Parameter dx="+std::to_string(dx)<<std::endl;
    }
    // Lets now see if casting to the SceneObject class is also https://doc.qt.io/qt-5/qlist.html#atpossible since we need to do it for the safe.
    SceneObject *PObject=qgraphicsitem_cast<SceneObject *>(Item);
    if(PObject==nullptr){// We cannot upcast to a base class !!. No biggy we just keep the vector with of SceneObjects.
        std::cout<<"It Failed"<<std::endl;
    }else{
        // What is now the type?
        if(PObject->type()==SceneObject::Type){
            std::cout<<"Type= SceneObject"<<std::endl;
        }else{
            std::cout<<"Type != SceneObject"<<std::endl;
        }
        // What's the virtual function?
        PObject->TestFunc();
    }
    std::cout<<"The End"<<std::endl;
}




