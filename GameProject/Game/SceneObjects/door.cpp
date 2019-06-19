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
    Direction=Right;// Just set default right.
    IsOpen=0;
    color.setNamedColor("Brown");

    if(room!=nullptr){
        QObject::connect(CurrentRoom,SIGNAL(RoomIsCleared()),this,SLOT(OpenDoors()));
        QObject::connect(this,SIGNAL(IsTrespassed(uint)),CurrentRoom,SLOT(DoorWasEntered(uint)));
    }

    IsInit=1;
}


// *** Slots *** //

void Door::OpenDoors(){
    SetPenetrability(1);
    IsOpen=1;
}

void Door::Trespas(){
    std::cout<<"trespas"<<std::endl;
    if(IsOpen){// if not open. don't do anything
        emit IsTrespassed(Direction);
    }
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
    QString savestring("%");// Seperation in this string will be "%"
    savestring.append(SaveSceneObject()+"%");
    savestring.append(SaveCollisionClass()+"%");
    // Door information.
    savestring.append(",");// always have a separator in front ! Else you also have garbage
    savestring.append(QString::number(Direction)+",");
    savestring.append(QString::number(IsOpen)+",");
    savestring.append(QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+",");// Save the color.
    savestring.append("%");
    return savestring;
}

void Door::Load(QString str){
    if(!IsInit){
        std::cout<<"Error in Door::Load, Object calls load while it was not Init first"<<std::endl;
        return;
    }
    QStringList sL1=str.split("%");
    LoadSceneObject(sL1[1]);
    LoadCollisionClass(sL1[2]);
    // Player information.
    QStringList sL2=sL1[3].split(",");
    Direction=sL2[1].toInt();
    IsOpen=sL2[2].toInt();
    color.setRgb(sL2[3].toInt(),sL2[4].toInt(),sL2[5].toInt());
}


void Door::setDirection(unsigned dir){
    Direction=dir;
}
