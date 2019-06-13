#include "wall.h"

/******* Essential Functions *******/

Wall::Wall(QObject *parent) : CollisionClass(parent)
{

}


void Wall::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    Team=SceneObject::NoTeam;
    InitCollision(200,200);
    color.setNamedColor("Grey");

    IsInit=1;
}


/******* SLOTS *******/


/******* Functions *******/

QRectF Wall::boundingRect() const{
    return QRectF(-w()/2,-h()/2,w(),h());
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-w()/2,-h()/2,w(),h());
}

QString Wall::Save(){
    QString savestring("");
    // Always first type.
    savestring.append("--");// "--" will be the separator between type and eventually the correct string.
    savestring.append(QString::number(type()));
    savestring.append("--");
    savestring.append(SaveWall());// Put here information for the wall.
    savestring.append("--\n");
    return savestring;
}

QString Wall::SaveWall(){// Create a sperate save function since this will be extremely analogue to Load.
    QString savestring("%");// Seperation in this string will be "%"
    savestring.append(SaveSceneObject()+"%");
    savestring.append(SaveCollisionClass()+"%");
    // Wall information.
    savestring.append(",");// always have a separator in front ! Else you also have garbage
    savestring.append(QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+",");// Save the color.
    savestring.append("%");
    return savestring;
}

void Wall::Load(QString str){
    if(!IsInit){
        std::cout<<"Error in Wall::Load, Object calls load while it was not Init first"<<std::endl;
        return;
    }
    // Next Wall information.
    QStringList sL1=str.split("%");
    LoadSceneObject(sL1[1]);
    LoadCollisionClass(sL1[2]);
    // Wall information.
    QStringList sL2=sL1[3].split(",");
    color.setRgb(sL2[1].toInt(),sL2[2].toInt(),sL2[3].toInt());
}
