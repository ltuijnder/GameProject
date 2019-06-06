#include "player.h"
#include "wall.h"
#include "projectile.h"

/******* Essential Functions *******/

Player::Player(QObject *parent) : SceneObject(parent),LivingClass(),CollisionClass()
{

}

void Player::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    // Associated to Living
    IsLiving=1;
    Team=SceneObject::TeamPlayer;
    InitLiving(Team,5);
    BreathingRoom=2*30;// Give 2 seconds of breathing room

    // Asosciated to Collision
    IsCollisionClass=1;
    InitCollision(50,50,Team);

    // Associated to player.
    speed=10; // Let 1 By normal
    //size=50;
    color.setNamedColor("blue");

    //Associated to shooting
    strength=10;
    ShotSpeed=15;
    RelatifStartingPos=w()+5;// Should be in function of size;
    FlightFrame=2*30;// Not fps General!
    FireRate=14;// Default value for default framerate (30 fps)
    Cooldown=0;
    IsShooting=0;// We don't set ShotDirection since it should always be checked with this flag.

    // Flags
    up=0;
    down=0;
    left=0;
    right=0;
    RoomIsSet=0;

    IsInit=1;
}


/******* SLOTS *******/

// Movement
void Player::UpKeyPressed(){up=1;}
void Player::DownKeyPressed(){down=1;}
void Player::LeftKeyPressed(){left=1;}
void Player::RightKeyPressed(){right=1;}
void Player::UpKeyReleased(){up=0;}
void Player::DownKeyReleased(){down=0;}
void Player::LeftKeyReleased(){left=0;}
void Player::RightKeyReleased(){right=0;}

// Shooting
void Player::ShotRightPressed(){ShotDirection=Player::ShotRight;IsShooting++;}
void Player::ShotLeftPressed(){ShotDirection=Player::ShotLeft;IsShooting++;}
void Player::ShotUpPressed(){ShotDirection=Player::ShotUp;IsShooting++;}
void Player::ShotDownPressed(){ShotDirection=Player::ShotDown;IsShooting++;}
void Player::ShotRightReleased(){IsShooting--;}
void Player::ShotLeftReleased(){IsShooting--;}
void Player::ShotUpReleased(){IsShooting--;}
void Player::ShotDownReleased(){IsShooting--;}

/******* Functions *******/


// drawings
QRectF Player::boundingRect() const{
    return QRectF(-w()/2,-h()/2,w(),h());
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-w()/2,-h()/2,w(),h());

}

// Dynamics

void Player::advance(int Phase){
    if(!Phase) return;// At Phase 0 we don't do anything
    if(!RoomIsSet) return; //In case an error was made, and the pointer was not set.
    // Calculate movement
    // We should also watch out for the fps! -> We keep it 30 fps fixed
    float dx=1*right-1*left;
    float dy=1*down-1*up;
    float modulo=sqrt(dx*dx+dy*dy);

    if(modulo!=0){// The player does not stand still so we are going to move
        dx*=speed/modulo;// Normalise it
        dy*=speed/modulo;
        QPointF DiffPoint(dx,dy);
        setPos(pos()+DiffPoint);// Get position alter is by Diffpoint and then set it equal to that.
    }

    // Now check if collisions are happening
    std::vector<SceneObject *> ObjectList=CurrentRoom->collidingObjects(this);
    for(auto Object: ObjectList){
        if(!Object->IsCollisionClass) continue;
        if(Object->IsLiving&&Object->GetTeam()==SceneObject::TeamEnemy)continue; // We don't move arround enemies, else THEY can push us around. which we don't want
        if(Object->type()==Wall::Type){// this is STUPID I can not go directly to. I am not going to change it now... the cost is just a few extra lines
            Wall *wall=static_cast<Wall *>(Object);
            setPos(pos()+DiffPoint(this,this,wall,wall));
        }
    }
    // Now we check the shooting.

    if(!Cooldown){// Zero cooldown -> Allowed to shoot.
        if(IsShooting){
            Projectile *Bullet=new Projectile;
            Bullet->Init(CurrentRoom);
            Bullet->SetProperties(ShotSpeed,strength,FlightFrame,Projectile::TPlayer);// Do this with string.
            QPointF RelPos(0,0);
            switch (ShotDirection) {
            case Player::ShotRight:
                RelPos.setX(RelatifStartingPos);
                Bullet->SetDirection(Player::ShotRight);
                break;
            case Player::ShotLeft:
                RelPos.setX(-RelatifStartingPos);
                Bullet->SetDirection(Player::ShotLeft);
                break;
            case Player::ShotUp:
                RelPos.setY(-RelatifStartingPos);
                Bullet->SetDirection(Player::ShotUp);
                break;
            case Player::ShotDown:
                RelPos.setY(RelatifStartingPos);
                Bullet->SetDirection(Player::ShotDown);
                break;
            }
            Bullet->setPos(pos()+RelPos);
            CurrentRoom->addItem(Bullet);
            Cooldown=FireRate;
        }
    }else{
        Cooldown--;// Lower the cooldown time. by 1 frame.
    }

    // Next we update the damage cooldown, if any.
    if(DamageCooldown>0) DamageCooldown--;
}


void Player::SetRoom(Room *NewRoom){
    CurrentRoom=NewRoom;
    RoomIsSet=1;
}
