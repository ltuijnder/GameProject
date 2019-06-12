#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include "collisionclass.h"
#include <QPainter>
#include <QColor>

class Door : public CollisionClass
{
    Q_OBJECT

signals:

public slots:
    void OpenDoors();

private:
    QColor color;

public:
    explicit Door(QObject *parent = nullptr);
    void Init(Room *) override;

    // Drawing
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    // typing
    enum{Type=UserType+11};// let 11 be doors (just after wall)
    int type() const override {return Type;}

    // Save
    QString Save() override;

};

#endif // DOOR_H
