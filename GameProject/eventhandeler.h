#ifndef EVENTHANDELER_H
#define EVENTHANDELER_H

#include <QObject>
#include <QKeyEvent>
#include <iostream>


class GameWindow;

class EventHandeler:public QObject{
    Q_OBJECT

signals:
    // Press events
    void UpKeyPressed();
    void PKeyPressed();
    void CKeyPressed();

    void ZKeyPressed();// Forward
    void SKeyPressed();// Backward
    void QKeyPressed();// Left
    void DKeyPressed();// Right

    // Release events
    void ZKeyReleased();
    void SKeyReleased();
    void QKeyReleased();
    void DKeyReleased();

public:
    EventHandeler();
    void PressInput(QKeyEvent *event);
    void ReleaseInput(QKeyEvent *event);
    void Link(GameWindow *gamewindow);

private:
    ///bool listen=1;// At the moment not needed.
};

#endif // EVENTHANDELER_H
