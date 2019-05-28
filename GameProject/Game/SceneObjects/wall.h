#ifndef WALL_H
#define WALL_H

#include <QObject>
#include "sceneobject.h"
#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QColor>

class Wall : public SceneObject
{
    Q_OBJECT

signals:


public slots:

private:
    float width;
    float height;
    QColor color;


public:
    // Essential Functions
    explicit Wall(QObject *parent = nullptr);
    void Init() override;

    // Drawing
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    // typing
    enum{Typpe=UserType+10};// Let 10 Be walls
    int type() const override {return Type;}

};

#endif // WALL_H
