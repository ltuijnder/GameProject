#include "door.h"

// *** Essential Functions *** //

Door::Door(QObject *parent) : CollisionClass(parent)
{

}

void Door::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    Team=SceneObject::NoTeam;
    InitCollision(200,100);
    color.setNamedColor("Brown");

    if(room!=nullptr){
        QObject::connect(CurrentRoom,SIGNAL(RoomIsCleared()),this,SLOT(OpenDoors()));
    }

    IsInit=1;
}


// *** Slots *** //

void Door::OpenDoors(){
    SetPenetrability(1);
}

// *** Functions *** //

QRectF Door::boundingRect() const{
    return QRectF(-w()/2,-h()/2,w(),h());
}

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-w()/2,-h()/2,w(),h());
}

QString Door::Save(){
    QString savestring("");
    // Always first type.
    savestring.append("--");// "--" will be the separator between type and eventually the correct string.
    savestring.append(QString::number(type()));
    savestring.append("--");
    savestring.append(SaveDoor());// Put here information for the wall.
    savestring.append("--\n");
    return savestring;
}

QString Door::SaveDoor(){// Create a sperate save function since this will be extremely analogue to Load.
    QString savestring("");// the position of of information is extremely important and should be closely analogue to the function load.
    savestring.append(",");// Seperation in this string will be ","
    // First save the QGraphicsItem infromation
    savestring.append(QString::number(pos().rx())+","+QString::number(pos().ry())+",");// Save the position
    // Next SceneObject Information
    savestring.append(QString::number(Team)+",");// The rest is all default value so don't save those.
    // Next CollisionClass
    savestring.append(QString::number(w())+","+QString::number(h())+",");// Geometry
    savestring.append(QString::number(IsPenetrable(0))+",");// Important Doors can be set to penetrable!!
    // Next Wall information.
    savestring.append(QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+",");// Save the color.

    return savestring;
}

void Door::Load(QString str){
    if(!IsInit){
        std::cout<<"Error in Door::Load, Object calls load while it was not Init first"<<std::endl;
        return;
    }
    QStringList strL=str.split(",");
    // First QGraphicsItem Information
    setPos(strL[1].toFloat(),strL[2].toFloat());// at(0) is Before the first , which is garbage we don't want.
    // Next SceneObject Information
    Team=strL[3].toInt();// there is no coversion to bool.
    //Next CollisionCLass information.
    SetGeometry(strL[4].toFloat(),strL[5].toFloat());// Set Geometery
    SetPenetrability(strL[6].toInt());// Set Penetrablility.
    // Next Wall information.
    color.setRgb(strL[7].toInt(),strL[8].toInt(),strL[9].toInt());
}
