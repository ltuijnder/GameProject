#ifndef TESTQOBJECT_H
#define TESTQOBJECT_H

#include <QObject>
#include "sceneobject.h"
#include <QRectF>
#include <QPainter>
#include <QColor>
#include <QRandomGenerator>
#include <QString>
#include <QStringList>

class TestQobject : public SceneObject
{
    Q_OBJECT

signals:

private:
    double dx;
    int w;
    int h;
    int x;
    int y;
    QColor color;

protected:
    void advance(int) override;

public slots:
    void SomeTestSlot();

public:
    explicit TestQobject(QObject *parent = nullptr);
    void Init(Room *) override;// We want it to be again virtual
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    enum {Type=UserType+1};// Let 1 by the dummy class
    int type() const override { return Type;}
    QString Save() override;
    void Load(QString str) override;

    QString SaveTestQobject();


    double TestGetParm() const;


};

#endif // TESTQOBJECT_H
