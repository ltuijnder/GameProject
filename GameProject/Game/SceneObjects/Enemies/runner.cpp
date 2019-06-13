#include "runner.h"

/******* Essential Functions *******/

Runner::Runner(QObject *parent) : Enemies(parent)
{

}

void Runner::Init(Room *room){
    Enemies::Init(room);
    if(IsInit) return;

    SetHealth(50);// Set health to 50.
    SetGeometry(50,50);// Sets its size.
    // Default Values
    speed=8;
    color.setNamedColor("red");

    IsInit=1;
}

/******* SLOTS *******/

/******* Functions *******/

void Runner::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-w()/2,-h()/2,w(),h());
}

void Runner::advance(int Phase){
    // Checks Before we can go any further
    if(!Phase){// At Phase zero do all the checks to see if we can go further.
        CheckDied();// check if the class should further exist.
        if(!IsInit) throw "Is not initialised" ;
        if(!PlayerIsSet) SetPlayerViaRoom();// This will run if the player enters the room for the first time.
        if(!PlayerIsSet) return; // Meaning the SetPlayerViaRoom has failed.
        return;// All the checks are done, now exist because we should only evaluate the rest at phase 1;
    }

    // Calculate Movement based on player
    QPointF dPoint=ThePlayer->pos()-pos();
    float Angle=std::atan2(dPoint.ry(),dPoint.rx());
    QPointF Diff(std::cos(Angle)*speed,std::sin(Angle)*speed);
    setPos(pos()+Diff);

    // See if collision happend
    std::vector<SceneObject *> ObjectList=CurrentRoom->collidingObjects(this);
    for(auto Object: ObjectList){// Collision should be done better
        if(!Object->IsCollisionClass) continue;// If not collision full, then we should not check anything.
        CollisionClass *Body=static_cast<CollisionClass *>(Object);
        if(!Body->IsPenetrable(Team)){
            setPos(pos()+DiffPoint(Body));
        }
        if(Body->IsLiving&&Body->GetTeam()==SceneObject::TeamPlayer){
            LivingClass *badguys=static_cast<LivingClass*>(Body);
            badguys->TakeDamage(1);
        }
    }

}


QString Runner::Save(){
    QString savestring("");
    // Always first type.
    savestring.append("--");// "--" will be the separator between type and eventually the correct string.
    savestring.append(QString::number(type()));
    savestring.append("--");
    savestring.append(SaveRunner());// Put here information for the wall.
    savestring.append("--\n");
    return savestring;
}

QString Runner::SaveRunner(){// Create a sperate save function since this will be extremely analogue to Load.
    QString savestring("%");// Seperation between the inherentace classes will be "%"
    savestring.append(SaveSceneObject()+"%");
    savestring.append(SaveCollisionClass()+"%");
    savestring.append(SaveLivingClass()+"%");
    // Runner information.
    savestring.append(",");// always have a separator in front ! Else you also have garbage
    savestring.append(QString::number(speed)+",");// Variable that the player set
    savestring.append(QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+",");// Save the color.
    savestring.append("%");
    return savestring;
}

void Runner::Load(QString str){
    if(!IsInit){
        std::cout<<"Error in Runner::Load, Object calls load while it was not Init first"<<std::endl;
        return;
    }
    QStringList sL1=str.split("%");
    LoadSceneObject(sL1[1]);
    LoadCollisionClass(sL1[2]);
    LoadLivingClass(sL1[3]);
    // Runner information.
    QStringList sL2=sL1[4].split(",");
    speed=sL2[1].toFloat();
    color.setRgb(sL2[2].toInt(),sL2[3].toInt(),sL2[4].toInt());
}
