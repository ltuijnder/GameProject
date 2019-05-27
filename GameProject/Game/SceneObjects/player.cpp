#include "player.h"


/******* Essential Functions *******/

Player::Player(QObject *parent) : SceneObject(parent)
{

}

void Player::Init(){
    SceneObject::Init();
    if(IsInit) return;
    speed=1; // Let 1 By normal
    size=50;
    health=5;
    strength=1.5;
    color.setNamedColor("blue");

    // Flags
    up=0;
    down=0;
    left=0;
    right=0;
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


/******* Functions *******/


// drawings
QRectF Player::boundingRect() const{
    return QRectF(-size/2,-size/2,size,size);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-size/2,-size/2,size,size);
}

// Dynamics

void Player::advance(int Phase){
    if(!Phase) return;// At Phase 0 we don't do anything
    // Calculate movement
    // We should also watch out for the fps!
    double dx=1*left-1*right;
    double dy=1*up-1*down;
    double modulo=sqrt(dx*dx-dy*dy);
    std::cout<<modulo<<std::endl;
    if(modulo!=0){// We don't want devision by zero
        dx=speed/modulo;
        dy=speed/modulo;
        QPointF DiffPoint(dx,dy);
        setPos(pos()+DiffPoint);// Get position alter is by Diffpoint and then set it equal to that.
    }
}
