#include "layoutelement.h"

Layoutelement::Layoutelement()
{
    // This default constructer is called when we use new Layoutelement.
    isRoom=0;
    Floorindex=-1;
    Layoutindex=-1;
    DoorType=0;
}


void Layoutelement::setRoom(bool boolian){
    isRoom=boolian;
}

void Layoutelement::setFIndex(int Findex){
    Floorindex=Findex;
}

void Layoutelement::setLIndex(int Lindex){
    Layoutindex=Lindex;
}

void Layoutelement::setDoorType(int type){
    DoorType=type;
}

int Layoutelement::Row(unsigned sidelength){
    return Layoutindex/sidelength;
}

int Layoutelement::Col(unsigned sidelength){
    return Layoutindex%sidelength;
}
