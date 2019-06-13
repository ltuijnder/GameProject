#include "sceneobject.h"

/******* Essential Functions *******/
SceneObject::SceneObject(QObject *parent) : QObject(parent)
{
    //ObjectType=0; // type =0 means that Its the base class. SceneObject (aka its nothing)
    IsWritten=0;
    IsCollisionClass=0;
    IsLiving=0;
    Team=NoTeam;// More then often the team is neutral.
}


void SceneObject::Init(Room *room){// For some weird reason one can not let an virtual function be defined
    if(IsInit){
       std::cout<<"ERROR in SceneObject, Was already initialised"<<std::endl;
       return;
    }
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

QString SceneObject::Save(){
    QString savestring("");
    // Always first type.
    savestring.append("--");// "--" will be the separator between type and eventually the correct string.
    savestring.append(QString::number(type()));
    savestring.append("--");
    // Here comes really the important stuff! that saves the object.
    savestring.append("--\n");
    return savestring;
}

void SceneObject::Load(QString LoadString){
    std::cout<<"Warning SceneObject::Load was used instead of a derived load"<<std::endl;
}
