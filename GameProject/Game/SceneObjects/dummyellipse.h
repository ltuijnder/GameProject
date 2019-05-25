#ifndef DUMMYELLIPSE_H
#define DUMMYELLIPSE_H

#include "sceneobject.h"
#include <QRectF>
#include <QPainter>
#include <QColor>
#include <QRandomGenerator>

class DummyEllipse: public SceneObject
{

signals:

public slots:

private:
    double dx;
    int w;
    int h;
    int x;
    int y;
    QColor color;

protected:
    void advance(int Phase) override;


public:
    // Essential Functions
    DummyEllipse();
    void Init();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;


};

#endif // DUMMYELLIPSE_H
