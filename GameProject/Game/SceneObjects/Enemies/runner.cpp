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
        if(Object->IsLiving){// This is badly done :(
            if(Object->GetTeam()==SceneObject::TeamPlayer){
                Player *player=static_cast<Player *>(Object);
                player->TakeDamage(1);
                setPos(pos()+DiffPoint(this,this,player,player));
                continue;
            }
            Enemies *goodguy=static_cast<Enemies *>(Object);
            setPos(pos()+DiffPoint(this,this,goodguy,goodguy));
        }else if(Object->type()==Wall::Type){
            Wall *wall=static_cast<Wall *>(Object);
            setPos(pos()+DiffPoint(this,this,wall,wall));
        }
    }

}
