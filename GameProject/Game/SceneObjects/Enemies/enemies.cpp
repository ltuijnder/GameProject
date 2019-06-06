#include "enemies.h"

/******* Essential Functions *******/

Enemies::Enemies(QObject *parent) : SceneObject(parent), LivingClass(), CollisionClass()
{

}

void Enemies::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Associated to livining
    Team=SceneObject::TeamEnemy;
    IsLiving=1;
    InitLiving(Team,0);// Set Health to 0 for now.

    // Associated to CollisionClass
    IsCollisionClass=1;
    InitCollision(0,0,Team);// For now set geometry to zero.

    ThePlayer=nullptr;
    PlayerIsSet=0;
    // set the rest of the defaults in the derived classes.
    if(room!=nullptr){
        QObject::connect(this,SIGNAL(Died(SceneObject*)),room,SLOT(DeleteSceneObject(SceneObject*)));
    }

    // Don't set the flag IsInit here equalt to 1 since we have subclasses
}

/******* SLOTS *******/


/******* Functions *******/

void Enemies::CheckDied(){
    if(FlagIsAlive()) return;
    emit Died(this);
}

QRectF Enemies::boundingRect() const{
    return QRectF(-w()/2,-h()/2,w(),h());
}

void Enemies::SetPlayer(Player *_ThePlayer){
    ThePlayer=_ThePlayer;
}

void Enemies::SetPlayerViaRoom(){
    QList<QGraphicsItem *> ItemsList=CurrentRoom->items();
    for(auto Item:ItemsList){
        if(Item->type()==Player::Type){// Not multiplayer friendly
            ThePlayer=qgraphicsitem_cast<Player *>(Item);
            PlayerIsSet=1;
            return;
        }
    }
    std::cout<<"Warning! Could not find player in the room!"<<std::endl;
}
