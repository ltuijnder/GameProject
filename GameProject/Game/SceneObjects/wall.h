#ifndef WALL_H
#define WALL_H

#include <QObject>
//#include "sceneobject.h"
#include "collisionclass.h"
#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QColor>

class Wall : public CollisionClass//public SceneObject, public CollisionClass
{
    Q_OBJECT

signals:


public slots:

private:
    QColor color;


public:
    // Essential Functions
    explicit Wall(QObject *parent = nullptr);
    void Init(Room *) override;

    // Drawing
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    // typing
    enum{Type=UserType+10};// Let 10 Be walls
    int type() const override {return Type;}

    // Saving
    QString Save() override;

};

#endif // WALL_H
