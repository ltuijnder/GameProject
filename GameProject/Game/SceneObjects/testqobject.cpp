#include "testqobject.h"

/******* Essential Functions *******/

TestQobject::TestQobject(QObject *parent) : SceneObject(parent)
{

}

/******* SLOTS *******/
void TestQobject::SomeTestSlot(){
    std::cout<<"SomeTestSlot"<<std::endl;
}


/******* Functions *******/

void TestQobject::Init(Room *room){

    SceneObject::Init(room);//Do the initialise of the base class (aka Set the basis parameters)
    // Set the parameters specific for this class
    if(IsInit) return; // Actually really nice place to do error handeling with throw and catch
    ObjectType=-1;// Does not matter, Delete
    // Set default values on its private variables;
    dx=5;
    w=200;
    h=100;
    x=w/2;
    y=h/2;
    color.setRgb(QRandomGenerator::global()->bounded(256),QRandomGenerator::global()->bounded(256),QRandomGenerator::global()->bounded(256));

    //setTransformOriginPoint(w,h);// This gives the correct behaviour
    // The reason why this is wrong is because bounding rect is starts at +x and +y while
    // the coördinate system is positif to right under. while the first coordinates are the top left corner
    // So top left should be negatif. hence We need to move our transformation origin now twice in the other direction

    IsInit=1;
}

QRectF TestQobject::boundingRect() const {
    return QRectF(-x,-y,w,h);
}

void TestQobject::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawEllipse(-x,-y,w,h);
}


void TestQobject::advance(int Phase){
    //std::cout<<"Rotatate!"<<std::endl;
    if(!Phase) return;// At Phase 0 we don't do anything
    // Now Phase 1 and we do really the advance step
    //std::cout<<"Rotatate!"<<std::endl;
    setRotation(rotation()+dx);
}


double TestQobject::TestGetParm() const{// const is part of the function name
    return dx;
}
