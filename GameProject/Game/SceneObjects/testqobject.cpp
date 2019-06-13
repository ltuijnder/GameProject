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
    QString savestring("");// the position of of information is extremely important and should be closely analogue to the function load.
    savestring.append(",");// Seperation in this string will be ","
    // First save the QGraphicsItem infromation
    savestring.append(QString::number(pos().rx())+","+QString::number(pos().ry())+",");// Save the position
    // Next SceneObject Information
    savestring.append(QString::number(IsCollisionClass)+",");// The rest is all default value so don't save those.
    // Next TestQobject information.
    savestring.append(QString::number(dx)+","+QString::number(w)+","+QString::number(h)+",");// Geomtery w and h can be made fromm x and y
    savestring.append(QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+",");// Save the color.

    return savestring;
}

void TestQobject::Load(QString str){
    if(!IsInit){
        std::cout<<"Error in TestQobject::Load, Object calls load while it was not Init first"<<std::endl;
        return;
    }
    QStringList strL=str.split(",");
    //First information QGraphcisItem
    int i=0;
    //std::cout<<strL[++i].toFloat()<<strL[++i].toFloat()<<std::endl;// for some reason this does not want to work in the thing below.
    setPos(strL[1].toFloat(),strL[2].toFloat());// at(0) is Before the first , which is garbage we don't want.

    // Next SceneObject
    IsCollisionClass=strL[3].toInt();// there is no coversion to bool.
    //Next TestQobject information.
    dx=strL[4].toDouble();
    w=strL[5].toInt();
    h=strL[6].toInt();
    x=w/2;
    y=h/2;
    color.setRgb(strL[7].toInt(),strL[8].toInt(),strL[9].toInt());
}


double TestQobject::TestGetParm() const{// const is part of the function name
    return dx;
}
