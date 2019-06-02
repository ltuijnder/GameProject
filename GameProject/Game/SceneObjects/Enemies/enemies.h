#ifndef ENEMIES_H
#define ENEMIES_H

#include <QObject>
#include "../sceneobject.h"
#include "../player.h"
#include <QRectF>

class Enemies : public SceneObject
{
    Q_OBJECT

signals:
    void DeleteMe(SceneObject *);// We should be able to delete Enemies

public slots:

protected:
    float width;// EVERY enemey will have a width and height
    float height; // Creating square you just put width and height equal
    float health; // EVERY enemy will have health

    Player *ThePlayer; // Every enemy should be aware of the player.

public:
    // Essential Functions
    explicit Enemies(QObject *parent = nullptr);
    void Init(Room *) override;

    // Drawing
    QRectF boundingRect() const override;// you should not reimplement this in subclasses further down.
    // Paint will be implemented by the subclass

    // typing
    enum{Type_Enemies=100};
    enum{Type=UserType+Type_Enemies};// let enemies be between 100 and 200
    int type() const override {return Type;}

    // Rest
    void TakeDamage(float Damage);// Every enemy should be able to take damage.
    void SetPlayer(Player *_ThePlayer);

    // Flags
    bool IsSpecial;// Have a Is Special flag to let other classes now they should go more precise then just base enemy class (for instance costum damage taking)
};

#endif // ENEMIES_H
