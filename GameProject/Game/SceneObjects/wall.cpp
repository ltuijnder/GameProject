#include "wall.h"

/******* Essential Functions *******/

Wall::Wall(QObject *parent) : CollisionClass(parent)
{

}


void Wall::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    Team=SceneObject::NoTeam;
    InitCollision(200,200);
    color.setNamedColor("Grey");

    IsInit=1;
}


/******* SLOTS *******/


/******* Functions *******/

QRectF Wall::boundingRect() const{
    return QRectF(-w()/2,-h()/2,w(),h());
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-w()/2,-h()/2,w(),h());
}
