#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include "sceneobject.h"
#include "collisionclass.h"
#include <QString>
#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QColor>



class Projectile : public SceneObject, public CollisionClass
{
    Q_OBJECT

signals:
    void DeleteMe(SceneObject *);

public slots:


private:
    // Stats
    float speed;
    float Damage;

    // Appearence & Dynamics
    unsigned Mode;
    enum{Linear};// Allow for complexer modes.
    unsigned direction;//0=right, 1=left, 2=up, 3=down
    unsigned FramesLeft;
    QColor color;
    QPointF Velocity();

    // Flags
    bool IsSetup;// Use this later on. Maybe do a global type bool?


protected:
    void advance(int) override;

public:
    // Essential Functions
    explicit Projectile(QObject *parent = nullptr);
    void Init(Room *) override;

    // Drawing
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    // Typing
    enum{Type=UserType+100};// Let 100 be projectiles
    int type() const override {return Type;}

    // rest
    void SetProperties(float _speed, float _damage, unsigned _FrameLeft, unsigned _Team);// Temporarily do this better;
    void SetDirection(unsigned _direction);
    enum{TPlayer,TEnemies};

};

#endif // PROJECTILE_H
