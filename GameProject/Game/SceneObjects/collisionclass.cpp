#include "collisionclass.h"

// **** Essential **** //

CollisionClass::CollisionClass(QObject *parent) : SceneObject(parent)
{
    Penetrable=0;// More then often not penetrable
    IsCollisionClass=1;
}

void CollisionClass::InitCollision(float w, float h){
    width=w;
    height=h;
}

// **** Slots **** //

// **** Functions **** //

float CollisionClass::w() const{
    return width;
}

float CollisionClass::h() const{
    return height;
}

void CollisionClass::SetGeometry(float NewWidth,float NewHeight){
    width=NewWidth;
    height=NewHeight;
}

void CollisionClass::SetPenetrability(bool Pen){
    Penetrable=Pen;
}

bool CollisionClass::IsPenetrable(int TeamOther) const{
    if(Team==SceneObject::TeamPlayer&&TeamOther==SceneObject::TeamPlayer){
        // If both colliding objects are of team Player, they are allowed to pass through each other;
        return 1;
    }else{
        return Penetrable;
    }
}
QPointF CollisionClass::DiffPoint(CollisionClass *Object) const{
    float Errorx=(Object->w()+w())/2-abs(Object->pos().x()-pos().x());
    float Errory=(Object->h()+w())/2-abs(Object->pos().y()-pos().y());
    if(Errory>Errorx){
        return QPointF((Object->pos().x()<pos().x())?Errorx:-1*Errorx,0);
    }else{
        return QPointF(0,(Object->pos().y()<pos().y())?Errory:-1*Errory);
    }
}
