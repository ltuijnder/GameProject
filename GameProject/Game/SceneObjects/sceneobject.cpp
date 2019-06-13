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

QString SceneObject::SaveSceneObject(){
    QString savestring(",");
    // In SceneObject we save the position also direct
    savestring.append(QString::number(pos().rx())+","+QString::number(pos().ry())+",");// Save the position
    // Next SceneObject Information
    savestring.append(QString::number(Team)+",");// The rest is all default value so don't save those.
    savestring.append(QString::number(IsCollisionClass)+","+QString::number(IsLiving)+",");

    return savestring;
}

void SceneObject::LoadSceneObject(QString str){
    QStringList strL=str.split(",");
    // First QQGraphicsItem
    setPos(strL[1].toFloat(),strL[2].toFloat());// at(0) is Before the first , which is garbage we don't want.
    // Next SceneObject Information
    Team=strL[3].toInt();// there is no coversion to bool.
    IsCollisionClass=strL[4].toInt();
    IsLiving=strL[5].toInt();
}
