#include "player.h"
#include "wall.h"

/******* Essential Functions *******/

Player::Player(QObject *parent) : SceneObject(parent)
{

}

void Player::Init(){
    SceneObject::Init();
    if(IsInit) return;

    // Set Default Values
    speed=10; // Let 1 By normal
    size=50;
    //setRect(-size/2,-size/2,size,size);
    health=5;
    strength=1.5;
    color.setNamedColor("blue");

    // Flags
    up=0;
    down=0;
    left=0;
    right=0;
    RoomIsSet=0;
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
    //return *this;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(color);
    painter->drawRect(-size/2,-size/2,size,size);
    //painter->drawRect(*this);

}

// Dynamics

void Player::advance(int Phase){
    if(!Phase) return;// At Phase 0 we don't do anything
    if(!RoomIsSet) return; //In case an error was made, and the pointer was not set.
    // Calculate movement
    // We should also watch out for the fps!
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
    QList<QGraphicsItem *> CollideList=CurrentScene->collidingItems(this);
    for(auto CollidingItem: CollideList){
        if(CollidingItem->type()==Wall::Type){
            // Look for the smallest error.
            Wall *wall=qgraphicsitem_cast<Wall *>(CollidingItem);
            double Errorx=(wall->Width()+size)/2-abs(wall->pos().x()-pos().x());
            double Errory=(wall->Height()+size)/2-abs(wall->pos().y()-pos().y());
            if(Errory>Errorx){
                QPointF DiffPoint((wall->pos().x()<pos().x())?Errorx:-1*Errorx,0);
                setPos(pos()+DiffPoint);
            }else{
                QPointF DiffPoint(0,(wall->pos().y()<pos().y())?Errory:-1*Errory);
                setPos(pos()+DiffPoint);
            }

        }
    }
}


void Player::SetRoom(QGraphicsScene *NewCurrentScene){
    CurrentScene=NewCurrentScene;
    RoomIsSet=1;
}
