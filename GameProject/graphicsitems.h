#ifndef GRAPHICSITEMS_H
#define GRAPHICSITEMS_H

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QColor>
#include <QRandomGenerator>
#include <iostream>

class Ellipse: public QGraphicsItem{
public:
    Ellipse();// Don't make the constructer here in the .h file. This created a lot of weird bugs.
    QRectF boundingRect() const override;// This is a pure virtual function Which NEEEDS to be over written
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;// This is a pure virtual function Which NEEEDS to be over written

protected:
    void advance(int Phase) override;

private:
    double dx;
    int w;
    int h;
    int x;
    int y;
    QColor color;
};


#endif // GRAPHICSITEMS_H
