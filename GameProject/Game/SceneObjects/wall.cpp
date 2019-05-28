#include "wall.h"

/******* Essential Functions *******/

Wall::Wall(QObject *parent) : SceneObject(parent)
{

}


void Wall::Init(){
    SceneObject::Init();
    if(IsInit) return;

    // Set Default Values
    width=200;
    height=200;
    color.setNamedColor("Grey");

}


/******* SLOTS *******/


/******* Functions *******/

QRectF Wall::boundingRect() const{
    return QRectF(-width/2,-height/2,width,height);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-width/2,-height/2,width,height);
}
