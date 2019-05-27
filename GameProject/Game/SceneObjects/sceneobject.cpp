#include "sceneobject.h"

/******* Essential Functions *******/
SceneObject::SceneObject(QObject *parent) : QObject(parent)
{

}


void SceneObject::Init(){// For some weird reason one can not let an virtual function be defined
    if(IsInit){
       std::cout<<"ERROR in SceneObject, Was already initialised"<<std::endl;
       return;
    }
    ObjectType=0; // type =0 means that Its the base class. SceneObject (aka its nothing)
    IsWritten=0;

    // Don't set IsInit, this is done in the derivived classes
}

/******* SLOTS *******/

//void SceneObject::TestSlot(){
//    std::cout<<"TestSlot from sceneobject"<<std::endl;
//}


/******* Functions *******/


void SceneObject::TestFunc(){
    std::cout<<"SceneObject::TestFunc()"<<std::endl;
}
