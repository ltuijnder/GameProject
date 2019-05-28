#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "sceneobject.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <math.h>
#include <QList>

class Player : public SceneObject
{
    Q_OBJECT

signals:

public slots:
    void UpKeyPressed();
    void UpKeyReleased();
    void DownKeyPressed();
    void DownKeyReleased();
    void LeftKeyPressed();
    void LeftKeyReleased();
    void RightKeyPressed();
    void RightKeyReleased();

private:
    float health;
    float speed;
    float size;
    float strength;
    QColor color;
    QGraphicsScene *CurrentScene;

    // Flags
    // Movement
    int up;// let it be an intiger (easy for calculation and allows to be flexible)
    int down;
    int left;
    int right;

    bool RoomIsSet;



protected:
    void advance(int) override;

public:
    // Essential Functions
    explicit Player(QObject *parent = nullptr);
    void Init() override;

    // Drawing
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    // typing
    enum{Type=UserType+2};// Let 2 be Players
    int type() const override {return Type;}

    // The rest
    void SetRoom(QGraphicsScene *NewCurrentScene);
};

#endif // PLAYER_H
