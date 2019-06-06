#ifndef LIVINGCLASS_H
#define LIVINGCLASS_H

#include <QObject>
#include "collisionclass.h"

class LivingClass: public CollisionClass
{
    Q_OBJECT

//signals:
//    void Died();

//public slots:

private:
    int Health;// Derived Classes should not acces Health Directly But should instead use SetHealth.
    bool IsAlive;// Same for IsAlive.

protected:
    // Settings
    //int TeamBeing;
    unsigned BreathingRoom;// Amount of frames we allow the being to be unvernable after taking damage.
    unsigned DamageCooldown;

    void InitLiving(int health);
public:
    explicit LivingClass(QObject *parent = nullptr);
    //LivingClass();
    void TakeDamage(int Damage);
    void SetHealth(int health);
    int GetHealt()const;
    bool FlagIsAlive() const;
    int GetTeamBeing() const;
};

#endif // LIVINGCLASS_H
