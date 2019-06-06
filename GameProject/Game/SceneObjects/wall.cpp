#include "wall.h"

/******* Essential Functions *******/

Wall::Wall(QObject *parent) : SceneObject(parent),CollisionClass()
{

}


void Wall::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    Team=SceneObject::NoTeam;
    InitCollision(200,200,Team);
    color.setNamedColor("Grey");

    IsInit=1;
}


/******* SLOTS *******/


/******* Functions *******/

QRectF Wall::boundingRect() const{
    return QRectF(-w()/2,-h()/2,w(),h());
    //return *this;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-w()/2,-h()/2,w(),h());
    //painter->drawRect(*this);
}


//float Wall::Width() const{
//    return width;
//}

//float Wall::Height() const{
//    return height;
//}

//void Wall::SetGeometry(float newwidth, float newheight){
//    width=newwidth;
//    height=newheight;
//}
