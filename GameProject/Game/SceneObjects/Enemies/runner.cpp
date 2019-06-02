#include "runner.h"

/******* Essential Functions *******/

Runner::Runner(QObject *parent) : Enemies(parent)
{

}

void Runner::Init(Room *room){
    Enemies::Init(room);
    if(IsInit) return;

    // Default Values
    width=50;
    height=50;
    health=50;
    IsSpecial=0;
    speed=8;
    color.setNamedColor("red");

    IsInit=1;
}

/******* SLOTS *******/



/******* Functions *******/

void Runner::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-width/2,-height/2,width,height);
}




void Runner::advance(int Phase){
    if(!Phase) return;

    // Calculate Movement based on player

    // See if collision happend

    // Next see if collision is with player -> then deal damage

    // If it is a wall update possition.

}
