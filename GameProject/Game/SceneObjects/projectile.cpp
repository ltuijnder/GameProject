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
