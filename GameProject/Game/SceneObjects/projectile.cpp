#include "projectile.h"
#include "player.h"
#include "wall.h"
#include "Enemies/enemies.h"


/******* Essential Functions *******/

Projectile::Projectile(QObject *parent) : CollisionClass(parent)//SceneObject(parent),CollisionClass()
{
    speed=0;
    Damage=0;
}

void Projectile::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;
    // Set Default Values
    // Collision
    SetPenetrability(1);// We allow other objects to go through bullets. Else you could stop people with bullets.
    InitCollision(15,15);

    //Dynamcis
    direction=Player::ShotRight;
    FramesLeft=0;
    color.setNamedColor("darkblue");// color list https://www.december.com/html/spec/colorsvg.html
    Mode=Projectile::Linear;// Do this nicer | 1=linear

    // Connections
    if(room!=nullptr){
        QObject::connect(this,SIGNAL(DeleteMe(SceneObject*)),CurrentRoom,SLOT(DeleteSceneObject(SceneObject*)));
    }

    IsSetup=1;// This is replaced latter with is written.
    IsInit=1;
}


/******* SLOTS *******/


/******* Functions *******/

QRectF Projectile::boundingRect() const{
    return QRectF(-w()/2,-h()/2,w(),h());
}

void Projectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawEllipse(-w()/2,-h()/2,w(),h());// Just for now draw a rect
}

void Projectile::SetProperties(float _speed, float _damage, unsigned _FramesLeft, unsigned _Team){
    speed=_speed;// Maybe directly in the constructor.
    Damage=_damage;
    FramesLeft=_FramesLeft;
    Team=_Team;
}

void Projectile::SetDirection(unsigned _direction){// Do this better
    direction=_direction;
}

// Dynamics

QPointF Projectile::Velocity(){
    if(Mode==Projectile::Linear){
        switch (direction) {
        case Player::ShotRight:
            return QPointF(speed,0);
        case Player::ShotLeft:
            return QPointF(-speed,0);
        case Player::ShotUp:
            return QPointF(0,-speed);// Y-axis is inverted in QT
        case Player::ShotDown:
            return QPointF(0,speed);
        default:
            std::cout<<"ERROR in Projectile class: No direction was set while calling Velocity()"<<std::endl;
            return QPointF(0,0);
        }
    }
    return QPointF(0,0);// Default return;
}

void Projectile::advance(int Phase){
    if(!Phase) return;// At Phase 0 we don't do anything
    if(!IsInit) return;

    QPointF vel=Velocity();
    setPos(pos()+vel);

    // Check Collision.
    std::vector<SceneObject *> ObjectList=CurrentRoom->collidingObjects(this);
    for(auto Object: ObjectList){
        if(!Object->IsCollisionClass) continue;// If not collision full, then we should not check anything.
        CollisionClass *Body=static_cast<CollisionClass *>(Object);
        if(!Body->IsPenetrable(Team)){
            emit DeleteMe(this);// Not penetrable so its dead.
        }
        // Now check if that what we hit was of living object of the opposing team.
        if(Body->IsLiving&&Body->GetTeam()!=Team){
            LivingClass *Being=static_cast<LivingClass*>(Body);
            Being->TakeDamage(Damage);
        }
    }

    if(!FramesLeft){// This sets a limiting life time on the bullet
        emit DeleteMe(this);
    }else{
        FramesLeft--;
    }
}

QString Projectile::Save(){
    QString savestring("");
    // Always first type.
    savestring.append("--");// "--" will be the separator between type and eventually the correct string.
    savestring.append(QString::number(type()));
    savestring.append("--");
    savestring.append(SaveProjectile());// Put here information for the wall.
    savestring.append("--\n");
    return savestring;
}

QString Projectile::SaveProjectile(){// Create a sperate save function since this will be extremely analogue to Load.
    QString savestring("%");// Seperation in this string will be "%"
    savestring.append(SaveSceneObject()+"%");
    savestring.append(SaveCollisionClass()+"%");
    // Projectile information.
    savestring.append(",");// always have a separator in front ! Else you also have garbage
    savestring.append(QString::number(speed)+","+QString::number(Damage)+",");// Variable that the player set
    savestring.append(QString::number(Mode)+",");
    savestring.append(QString::number(direction)+",");
    savestring.append(QString::number(FramesLeft)+",");
    savestring.append(QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+",");// Save the color.
    savestring.append("%");
    return savestring;
}

void Projectile::Load(QString str){
    if(!IsInit){
        std::cout<<"Error in Projectile::Load, Object calls load while it was not Init first"<<std::endl;
        return;
    }
    QStringList sL1=str.split("%");
    LoadSceneObject(sL1[1]);
    LoadCollisionClass(sL1[2]);
    // Projectile information.
    QStringList sL2=sL1[3].split(",");
    speed=sL2[1].toFloat();
    Damage=sL2[2].toFloat();
    Mode=sL2[3].toInt();
    direction=sL2[4].toInt();
    FramesLeft=sL2[5].toInt();
    color.setRgb(sL2[6].toInt(),sL2[7].toInt(),sL2[8].toInt());
}
