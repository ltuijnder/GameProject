#include "player.h"
#include "wall.h"
#include "door.h"
#include "projectile.h"

/******* Essential Functions *******/

Player::Player(QObject *parent) : LivingClass(parent)//SceneObject(parent),LivingClass(),CollisionClass()
{

}

void Player::Init(Room *room){
    SceneObject::Init(room);
    if(IsInit) return;

    // Set Default Values
    // Associated to Living
    Team=SceneObject::TeamPlayer;
    InitLiving(5);
    BreathingRoom=2*30;// Give 2 seconds of breathing room

    // Asosciated to Collision
    InitCollision(50,50);

    // Associated to player.
    speed=10; // Let 1 By normal
    //size=50;
    color.setNamedColor("blue");

    //Associated to shooting
    strength=50;
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
        CollisionClass *Body=static_cast<CollisionClass *>(Object);
        if(!Body->IsPenetrable(Team)){
            setPos(pos()+DiffPoint(Body));
        }
        if(Body->type()==Door::Type){
            Door *deur=static_cast<Door *>(Body);
            deur->Trespas();// We trespas the door so let the door know that such that it can take action.
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

QString Player::Save(){
    QString savestring("");
    // Always first type.
    savestring.append("--");// "--" will be the separator between type and eventually the correct string.
    savestring.append(QString::number(type()));
    savestring.append("--");
    savestring.append(SavePlayer());// Put here information for the wall.
    savestring.append("--\n");
    return savestring;
}

QString Player::SavePlayer(){// Create a sperate save function since this will be extremely analogue to Load.
    QString savestring("%");// Seperation in this string will be "%"
    savestring.append(SaveSceneObject()+"%");
    savestring.append(SaveCollisionClass()+"%");
    savestring.append(SaveLivingClass()+"%");
    // Player information.
    savestring.append(",");// always have a separator in front ! Else you also have garbage
    savestring.append(QString::number(speed)+",");// Variable that the player set
    savestring.append(QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+",");// Save the color.
    // Associated to schooting;
    savestring.append(QString::number(strength)+","+QString::number(ShotSpeed)+",");
    savestring.append(QString::number(FlightFrame)+","+QString::number(FireRate)+","+QString::number(Cooldown)+",");
    // Don't save the rest since it is either extremly default or has to do with instant button presses which ofcourse don't need to be safed.
    savestring.append("%");
    return savestring;
}

void Player::Load(QString str){
    if(!IsInit){
        std::cout<<"Error in Player::Load, Object calls load while it was not Init first"<<std::endl;
        return;
    }
    QStringList sL1=str.split("%");
    LoadSceneObject(sL1[1]);
    LoadCollisionClass(sL1[2]);
    LoadLivingClass(sL1[3]);
    // Player information.
    QStringList sL2=sL1[4].split(",");
    speed=sL2[1].toFloat();
    color.setRgb(sL2[2].toInt(),sL2[3].toInt(),sL2[4].toInt());
    // Next Associated to schooting
    strength=sL2[5].toFloat();
    ShotSpeed=sL2[6].toFloat();
    FlightFrame=sL2[7].toInt();
    FireRate=sL2[8].toInt();
    Cooldown=sL2[9].toInt();
}
