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
    IsCollisionClass=0;
    // Set default values on its private variables;
    dx=5;
    w=200;
    h=100;
    x=w/2;
    y=h/2;
    color.setRgb(QRandomGenerator::global()->bounded(256),QRandomGenerator::global()->bounded(256),QRandomGenerator::global()->bounded(256));
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

QString TestQobject::Save(){
    QString savestring("");
    // Always first type.
    savestring.append("--");// "--" will be the separator between type and eventually the correct string.
    savestring.append(QString::number(type()));// number= QString::number -> so it converts to numbers to QString
    savestring.append("--");
    savestring.append(SaveTestQobject());
    savestring.append("--\n");
    return savestring;
}

QString TestQobject::SaveTestQobject(){// Create a sperate save function since this will be extremely analogue to Load.
    QString savestring("%");// Seperation in this string will be "%"
    savestring.append(SaveSceneObject()+"%");
    // TestQobject information
    savestring.append(",");// always have a separator in front ! Else you also have garbage
    savestring.append(QString::number(dx)+","+QString::number(w)+","+QString::number(h)+",");// Geomtery w and h can be made fromm x and y
    savestring.append(QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+",");// Save the color.
    savestring.append("%");
    return savestring;
}

void TestQobject::Load(QString str){
    if(!IsInit){
        std::cout<<"Error in TestQobject::Load, Object calls load while it was not Init first"<<std::endl;
        return;
    }
    QStringList sL1=str.split("%");
    LoadSceneObject(sL1[1]);
    // Player information.
    QStringList sL2=sL1[2].split(",");
    dx=sL2[1].toDouble();
    w=sL2[2].toInt();
    h=sL2[3].toInt();
    x=w/2;
    y=h/2;
    color.setRgb(sL2[4].toInt(),sL2[5].toInt(),sL2[6].toInt());
}


double TestQobject::TestGetParm() const{// const is part of the function name
    return dx;
}
