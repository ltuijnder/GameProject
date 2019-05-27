#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "sceneobject.h"
#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <math.h>

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
    double health;
    double speed;
    double size;
    double strength;
    QColor color;

    // Flags
    // Movement
    bool up;
    bool down;
    bool left;
    bool right;

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
};

#endif // PLAYER_H
