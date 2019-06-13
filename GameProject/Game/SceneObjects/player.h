#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "livingclass.h"
#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <math.h>
#include <QList>

class Player : public LivingClass//public SceneObject, public LivingClass, public CollisionClass
{
    Q_OBJECT

signals:
    //void Died();

public slots:
    void UpKeyPressed();
    void UpKeyReleased();
    void DownKeyPressed();
    void DownKeyReleased();
    void LeftKeyPressed();
    void LeftKeyReleased();
    void RightKeyPressed();
    void RightKeyReleased();

    void ShotRightPressed();
    void ShotRightReleased();
    void ShotLeftPressed();
    void ShotLeftReleased();
    void ShotUpPressed();
    void ShotUpReleased();
    void ShotDownPressed();
    void ShotDownReleased();


private:
    // Associated to player
    //unsigned health;// We will have integer amount of heath no float.
    //unsigned BreathingRoom;// Amount of frames we allow the player to be unvernable after taking damage.
    //unsigned DamageCooldown;
    float speed;
    //float size;
    QColor color;

    // Associated to shooting
    float strength;
    float ShotSpeed;
    float RelatifStartingPos;
    unsigned FlightFrame; // Not FPS general.
    unsigned FireRate;// Firerate is frames per shot.
    unsigned Cooldown;// Howmany frames left before you can shoot again.
    // Reason why I work with cooldown per frame rate instead of a timer, Well you can only shoot per frame, since thats when the update happens.
    // I could put the firing on a different time clock. But if your frame rate goes lower, then the game should also go slower (including shots)
    int ShotDirection;// This reflects that you can only shoot in 1 Direction!
    unsigned IsShooting;// the reason why not a bool, since we should keep track of how many buttons are pushed down before we can set it to zero.

    // Flags
    // Movement
    int up;// let it be an intiger (easy for calculation and allows to be flexible, for accelaration and stuff like that)
    int down;
    int left;
    int right;

    bool RoomIsSet;



protected:
    void advance(int) override;

public:
    // Essential Functions
    explicit Player(QObject *parent = nullptr);
    void Init(Room *) override;

    // Drawing
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    // typing
    enum{Type=UserType+2};// Let 2 be Players
    int type() const override {return Type;}

    // The rest
    void SetRoom(Room *NewRoom);
    enum{ShotRight,ShotLeft,ShotUp,ShotDown}; // Create these variables to create readable code

    // Saving
    QString Save() override;
    QString SavePlayer();
    void Load(QString str);

};

#endif // PLAYER_H
