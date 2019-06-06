#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QObject>
#include <QGraphicsItem>
#include <iostream>
#include "../room.h"

class SceneObject : public QObject, public QGraphicsItem
{
    Q_OBJECT

signals:

public slots:

protected:
    //Flags
    bool IsWritten;
    bool IsInit=0;// Important That is default value 0!! Else its possible that Init() gets not triggerd
    int Team;// equal SceneObject::NoTeam,SceneObject::TeamPlayer, SceneObject::TeamEnemy

    Room *CurrentRoom;

public:
    // essential
    explicit SceneObject(QObject *parent = nullptr);
    virtual void Init(Room *);// can't be constant since we change variables
    enum {Type= UserType+0};// Define number 0 as the SceneObject
    int type() const override { return Type;} // Use override to tell that the function Type() is still virtual, use const sine thats the signature of the function



    // Variables
    int ObjectType;// Unnecesary delete it

    // Functions
    virtual void TestFunc();
    int GetTeam();
    // Write also virtual
    // Read also virtual

    // Flags
    bool IsCollisionClass;// It inherents from the Collision class.
    bool IsLiving;// It inherents from the LivingClass.

    enum{NoTeam,TeamPlayer,TeamEnemy};

};

#endif // SCENEOBJECT_H
