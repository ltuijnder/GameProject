#include "dummyellipse.h"


/******* Essential Functions *******/


DummyEllipse::DummyEllipse()
{

}


void DummyEllipse::Init(){

    SceneObject::Init();//Do the initialise of the base class (aka Set the basis parameters)
    // Set the parameters specific for this class
    if(IsInit) return; // Actually really nice place to do error handeling with throw and catch
    ObjectType=-1;// Let the dummies be negatif
    // Set default values on its private variables;
    dx=5;
    w=200;
    h=100;
    x=w/2;
    y=h/2;
    color.setRgb(QRandomGenerator::global()->bounded(256),QRandomGenerator::global()->bounded(256),QRandomGenerator::global()->bounded(256));

    setTransformOriginPoint(w,h);// This gives the correct behaviour
}

QRectF DummyEllipse::boundingRect() const {
    return QRectF(x,y,w,h);
}

void DummyEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawEllipse(x,y,w,h);
}

void DummyEllipse::advance(int Phase){
    std::cout<<"Rotatate!"<<std::endl;
    if(!Phase) return;// At Phase 0 we don't do anything
    // Now Phase 1 and we do really the advance step
    std::cout<<"Rotatate!"<<std::endl;
    setRotation(rotation()+dx);
}

/******* SLOTS *******/



/******* Functions *******/
