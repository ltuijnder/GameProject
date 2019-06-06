#include "sceneobject.h"

/******* Essential Functions *******/
SceneObject::SceneObject(QObject *parent) : QObject(parent)
{

}


void SceneObject::Init(Room *room){// For some weird reason one can not let an virtual function be defined
    if(IsInit){
       std::cout<<"ERROR in SceneObject, Was already initialised"<<std::endl;
       return;
    }
    ObjectType=0; // type =0 means that Its the base class. SceneObject (aka its nothing)
    IsWritten=0;
    IsCollisionClass=1; // More then often it is.
    IsLiving=0;// More then often it is not
    Team=NoTeam;// More then often the team is neutral.
    CurrentRoom=room;

    // Don't set IsInit, this is done in the derivived classes
}

/******* SLOTS *******/




/******* Functions *******/


void SceneObject::TestFunc(){
    std::cout<<"SceneObject::TestFunc()"<<std::endl;
}


int SceneObject::GetTeam(){
    return Team;
}
