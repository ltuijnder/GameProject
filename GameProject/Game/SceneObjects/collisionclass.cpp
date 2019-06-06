#include "collisionclass.h"

// **** Essential **** //

CollisionClass::CollisionClass()
{
    Penetrable=0;
    TeamCollision=SceneObject::NoTeam;
}

void CollisionClass::InitCollision(float w, float h, int team){
    width=w;
    height=h;
    TeamCollision=team;
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

void CollisionClass::SetTeamCollision(int Team){
    TeamCollision=Team;
}

bool CollisionClass::IsPenetrable(int Team) const{
    if(TeamCollision==SceneObject::TeamPlayer&&Team==SceneObject::TeamPlayer){
        // If both colliding objects are of team Player, they are allowed to pass through each other;
        return 1;
    }else{
        return Penetrable;
    }
}

// The function DiffPoint is a bit of a pickle since you need the position information.
// I went for the sollution where we upcast 2 times. since others seemed more complex.
QPointF CollisionClass::DiffPoint(SceneObject *This,CollisionClass *ThisCol, SceneObject *Other,CollisionClass *OtherCol) const{
    float Errorx=(OtherCol->w()+ThisCol->w())/2-abs(Other->pos().x()-This->pos().x());
    float Errory=(OtherCol->h()+ThisCol->w())/2-abs(Other->pos().y()-This->pos().y());
    if(Errory>Errorx){
        return QPointF((Other->pos().x()<This->pos().x())?Errorx:-1*Errorx,0);
    }else{
        return QPointF(0,(Other->pos().y()<This->pos().y())?Errory:-1*Errory);
    }
}
