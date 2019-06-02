#include "enemies.h"

/******* Essential Functions *******/

Enemies::Enemies(QObject *parent) : SceneObject(parent)
{

}

void Enemies::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    ThePlayer=nullptr;
    // set the rest of the defaults in the derived classes.
    if(room!=nullptr){
        QObject::connect(this,SIGNAL(DeleteMe(SceneObject*)),room,SLOT(DeleteSceneObject(SceneObject*)));
    }

    // Don't set the flag IsInit here equalt to 1 since we have subclasses
}

/******* SLOTS *******/


/******* Functions *******/

QRectF Enemies::boundingRect() const{
    return QRectF(-width/2,-height/2,width,height);
}

void Enemies::TakeDamage(float Damage){
    health-=Damage;
    if(health<=0) emit DeleteMe(this);
}

void Enemies::SetPlayer(Player *_ThePlayer){
    ThePlayer=_ThePlayer;
}
