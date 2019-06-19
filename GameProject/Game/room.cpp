#include "room.h"
#include "SceneObjects/sceneobject.h"
#include "SceneObjects/testqobject.h"
#include "SceneObjects/player.h"
#include "SceneObjects/wall.h"
#include "SceneObjects/Enemies/enemies.h"
#include "SceneObjects/Enemies/runner.h"
#include "SceneObjects/projectile.h"
#include "SceneObjects/door.h"

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
    IsCleared=0;

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
        //addItem(Elli0);
        QString Savestring=Elli0->SaveTestQobject();
        delete Elli0;

        TestQobject *Elli=new TestQobject;
        Elli->Init(this);
        Elli->Load(Savestring);
        addItem(Elli);

        Wall *Brick=new Wall;
        Brick->Init(this);
        Brick->setPos(125,125);
        //addItem(Brick);
        Savestring=Brick->SaveWall();
        delete Brick;

        Wall *LoadBrick=new Wall;
        LoadBrick->Init(this);
        LoadBrick->Load(Savestring);
        addItem(LoadBrick);

//        Wall *Brick2=new Wall;
//        Brick2->Init(this);
//        Brick2->setPos(100,175);
//        addItem(Brick2);

        // Ad our first enemy.
        Runner *Satan= new Runner;
        Satan->Init(this);
        Satan->setPos(-400,-400);
        //addItem(Satan);
        Savestring=Satan->SaveRunner();
        delete Satan;

        Runner *Lucifer= new Runner;
        Lucifer->Init(this);
        Lucifer->Load(Savestring);
        addItem(Lucifer);

        // Ad our first Door.
        Door *deur= new Door;
        deur->Init(this);
        deur->setPos(-300,-300);
        //addItem(deur);
        Savestring=deur->SaveDoor();
        delete deur;

        Door *porte= new Door;
        porte->Init(this);
        porte->Load(Savestring);
        addItem(porte);

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

void Room::CheckClear(){
    int NumberEnemies=NumberOfEnemies();
    if(!NumberEnemies){
        std::cout<<NumberEnemies<<std::endl;
        emit RoomIsCleared();
        IsCleared=1;
    }
}
/******* Functions *******/



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

void Room::SetRoomType(int Type){
    RoomType=Type;
    RoomTypeIsSet=1;
}

void Room::SetRoomPosition(int Pos){
    Position=Pos;
}


QString Room::SaveHeader(){
    return QString("");
}

void Room::LoadHeader(QString str){
    if(!IsSetup){// if NOT setup then not persuit.
        std::cout<<"Error Room::LoadHeader room was not setup so cannot load"<<std::endl;
        return;
    }
    //pass
}


QString Room::SaveObjects(){
    QString stringobjects("");
    QList<QGraphicsItem *> GraphicsItemsList=items();
    SceneObject *Object;
    stringobjects.append("***SceneObject***\n");
    for(auto GraphicsItem:GraphicsItemsList){
        if(GraphicsItem->type()==Player::Type) continue; // The player will not be safed in here it is safed differently.
        Object=dynamic_cast<SceneObject *>(GraphicsItem);
        stringobjects.append(Object->Save());
        stringobjects.append("***SceneObject***\n");
    }
    return stringobjects;
}

void Room::LoadObjects(QString str){
    if(!IsSetup){// If NOT setup then not peruist
        std::cout<<"Error LoadObject room was not setup so cannot load "<<std::endl;
        return;
    }if(IsFilled){// if IS filled up then not persuit
        std::cout<<"Error LoadObject is already filled up cannot load"<<std::endl;
    }
    QStringList strL=str.split("***SceneObject***");
    int type=0;// instead of makint them in every for loop which is unnecesarry just make it once here
    QString loadstring("");
    for(int i=1;i<strL.size()-1;i++){// We don't want the first and last
        type=strL[i].section("--",1,1).toInt();
        loadstring=strL[i].section("--",2,2);
        // Now based on the type we need to already explicit new that type
        // else init and load would never know which class to pick. In downcasting you ALWAYS need to specific.

        // Check if enemy
        SceneObject *TheObject=nullptr;
        if(type>Enemies::Type&&type<Enemies::Type_EnemiesMAX){// Don't switch this since switches are bad with condition
            switch (type) {
            case Runner::Type:
                Runner *Satan=new Runner;
                TheObject=Satan;
                break;
            }
        }
        switch (type) {
        case Wall::Type:{// We have to be explicit with the scopes in the scope else error: see https://stackoverflow.com/questions/5685471/error-jump-to-case-label
            Wall *TrumpWall=new Wall;
            TheObject=TrumpWall;
            break;
        }
        case Door::Type:{
            Door *porte=new Door;
            TheObject=porte;
            break;
        }
        case TestQobject::Type:{
            TestQobject *letest=new TestQobject;
            TheObject=letest;
            break;
        }
        case Projectile::Type:{
            Projectile *bullet=new Projectile;
            TheObject=bullet;
            break;
        }
        }
        if(TheObject!=nullptr){
            TheObject->Init(this);
            TheObject->Load(loadstring);
            addItem(TheObject);
        }else{
            std::cout<<"Warning Room::LoadObjects an object was not loaded with type number: "<<type<<std::endl;
        }
    }

    IsFilled=1;

}
