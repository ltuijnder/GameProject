#include "livingclass.h"

// **** Essential Functions **** //

//LivingClass::LivingClass(QObject *parent) : QObject(parent)
//{

//}
LivingClass::LivingClass(QObject *parent): CollisionClass(parent)
{
    Health=0;
    DamageCooldown=0;// Set these equal to zero.
    BreathingRoom=0; // Be specific in the subclass. Most often BreathingRoom =0;
    IsLiving=1;// Aka it inherents from the class;
    IsAlive=0;
}

void LivingClass::InitLiving(int health){

    //TeamBeing=Team;
    //std::cout<<"Team"<<TeamBeing<<std::endl;
    SetHealth(health);
}

// *** Slots *** //

// *** Funcions *** /

void LivingClass::TakeDamage(int Damage){
    if(DamageCooldown) return;
    if(!IsAlive) return;// If it is dead taking damage is uncessary.
    if(Team==SceneObject::TeamPlayer){
        Health--;// Player has int value health
    }else{
        Health-=Damage;
    }
    if(Health<=0){
        Health=0;// If we overshot the health set it to zero.
        IsAlive=0;// also it is dead.
    }
    DamageCooldown=BreathingRoom;
}

//int LivingClass::GetTeamBeing() const{
//    return TeamBeing;
//}

int LivingClass::GetHealt() const{
    return Health;
}

void LivingClass::SetHealth(int health){
    if(health<=0){
        Health=0;
        IsAlive=0;
    }else{
        Health=health;
        IsAlive=1;
    }
}

bool LivingClass::FlagIsAlive() const{
    return IsAlive;
}
