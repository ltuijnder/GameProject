#ifndef EVENTHANDELER_H
#define EVENTHANDELER_H

#include <QObject>
#include <QKeyEvent>
#include <iostream>


class GameWindow;

class EventHandeler:public QObject{
    Q_OBJECT

signals:
    void UpKeyPressed();
    void PKeyPressed();

public:
    EventHandeler();
    void KeyInput(QKeyEvent *event);
    void Link(GameWindow *gamewindow);

private:
    bool listen=1;

};

#endif // EVENTHANDELER_H
