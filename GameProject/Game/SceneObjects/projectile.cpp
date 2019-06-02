#include "projectile.h"
#include "player.h"
#include "wall.h"


/******* Essential Functions *******/

Projectile::Projectile(QObject *parent) : SceneObject(parent)
{

}

void Projectile::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    size=15;
    speed=0;
    Damage=0;
    direction=Player::ShotRight;
    FramesLeft=0;
    color.setNamedColor("darkblue");// color list https://www.december.com/html/spec/colorsvg.html
    Mode=Projectile::Linear;// Do this nicer | 1=linear

    if(room!=nullptr){
        QObject::connect(this,SIGNAL(DeleteMe(SceneObject*)),CurrentRoom,SLOT(DeleteSceneObject(SceneObject*)));
    }

    IsSetup=1;// For now just set on 1
}


/******* SLOTS *******/


/******* Functions *******/

QRectF Projectile::boundingRect() const{
    return QRectF(-size/2,-size/2,size,size);
}

void Projectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawEllipse(-size/2,-size/2,size,size);// Just for now draw a rect
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
    if(!IsSetup) return;// If no direction is set we cannot go forward

    QPointF vel=Velocity();
    setPos(pos()+vel);

    // Check Collision.
    QList<QGraphicsItem *> CollideList=CurrentRoom->collidingItems(this);
    for(auto collidingItem: CollideList){
        if(collidingItem->type()==Wall::Type){
            emit DeleteMe(this);// Delete this when it comes into contact of a wall.
        }
    }

    if(!FramesLeft){// This sets a limiting life time on the bullet
        emit DeleteMe(this);
    }else{
        FramesLeft--;
    }
}
