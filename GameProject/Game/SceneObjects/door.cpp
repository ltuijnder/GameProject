#include "door.h"

// *** Essential Functions *** //

Door::Door(QObject *parent) : CollisionClass(parent)
{

}

void Door::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    Team=SceneObject::NoTeam;
    InitCollision(200,100);
    color.setNamedColor("Brown");

    if(room!=nullptr){
        QObject::connect(CurrentRoom,SIGNAL(RoomIsCleared()),this,SLOT(OpenDoors()));
    }

    IsInit=1;
}


// *** Slots *** //

void Door::OpenDoors(){
    SetPenetrability(1);
}

// *** Functions *** //

QRectF Door::boundingRect() const{
    return QRectF(-w()/2,-h()/2,w(),h());
}

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-w()/2,-h()/2,w(),h());
}
