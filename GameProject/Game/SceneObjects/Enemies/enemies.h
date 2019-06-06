#ifndef ENEMIES_H
#define ENEMIES_H

#include <QObject>
//#include "../sceneobject.h"
#include "../player.h"
//#include "../collisionclass.h"
#include <QRectF>
#include <QList>

class Enemies : public LivingClass//public SceneObject, public LivingClass, public CollisionClass
{
    Q_OBJECT

signals:
    void Died(SceneObject *);// We should be able to delete Enemies

public slots:

protected:
    Player *ThePlayer; // Every enemy should be aware of the player.
    bool PlayerIsSet; // Just a bool to see if ThePlayer Is set

    void CheckDied();// This is stupid but QT does not allow QObject to be multi inherented.

public:
    // Essential Functions
    explicit Enemies(QObject *parent = nullptr);
    void Init(Room *) override;

    // Drawing
    QRectF boundingRect() const override;// you should not reimplement this in subclasses further down.
    // Paint will be implemented by the subclass

    // typing
    enum{Type_Enemies=100};
    enum{Type=UserType+Type_Enemies,Type_EnemiesMAX=UserType+Type_Enemies+100};// let enemies be between 100 and 200
    int type() const override {return Type;}

    // Rest
    void SetPlayer(Player *_ThePlayer);
    void SetPlayerViaRoom();

 };

#endif // ENEMIES_H
