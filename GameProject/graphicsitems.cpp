#include "graphicsitems.h"

/*
Ellipse::Ellipse():x(0),y(0),w(200),h(100)
{

}*/
Ellipse::Ellipse():dx(5),w(200),h(100),x(w/2),y(h/2),
    color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256))
{
    std::cout<<"YEP"<<std::endl;
    setTransformOriginPoint(w,h);// This gives the correct behaviour but is still weird.... find out what's up with the coordinates.
}



void Ellipse::advance(int Phase){
    std::cout<<"Rotatate!"<<std::endl;
    if(!Phase) return;// At Phase 0 we don't do anything
    // Now Phase 1 and we do really the advance step
    std::cout<<"Rotatate!"<<std::endl;
    setRotation(rotation()+dx);
}

QRectF Ellipse::boundingRect() const{
    return QRectF(x,y,w,h);
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawEllipse(x,y,w,h);
}
