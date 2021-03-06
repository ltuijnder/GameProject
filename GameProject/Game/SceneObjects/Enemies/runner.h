#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include "enemies.h"
#include <QColor>
#include <cmath>
#include "../wall.h"

class Runner : public Enemies
{
    Q_OBJECT

signals:

public slots:

private:
    float speed;
    QColor color;

protected:
    void advance(int) override;

public:
    // Essential Functions
    explicit Runner(QObject *parent = nullptr);
    void Init(Room *) override;

    // Drawing
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    // Typing
    enum{Type=UserType+Type_Enemies+1};// Let the runner be 101
    int type() const override {return Type;}

    // Save
    QString Save() override;
    QString SaveRunner();
    void Load(QString str);

};

#endif // RUNNER_H
