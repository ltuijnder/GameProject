#include "wall.h"

/******* Essential Functions *******/

Wall::Wall(QObject *parent) : SceneObject(parent)
{

}


void Wall::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    width=200;
    height=200;
    //setRect(-width/2,-height/2,width,height);
    color.setNamedColor("Grey");

    IsInit=1;
}


/******* SLOTS *******/


/******* Functions *******/

QRectF Wall::boundingRect() const{
    return QRectF(-width/2,-height/2,width,height);
    //return *this;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-width/2,-height/2,width,height);
    //painter->drawRect(*this);
}


float Wall::Width() const{
    return width;
}

float Wall::Height() const{
    return height;
}

void Wall::SetGeometry(float newwidth, float newheight){
    width=newwidth;
    height=newheight;
}
