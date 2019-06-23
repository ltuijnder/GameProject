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
    void PKeyPressed();
    void CKeyPressed();

    void ZKeyPressed();// Forward
    void SKeyPressed();// Backward
    void QKeyPressed();// Left
    void DKeyPressed();// Right

    void RAKeyPressed();// Right Arrow Key
    void LAKeyPressed();// Left Arrow
    void UAKeyPressed();// Up Arrow
    void DAKeyPressed();// down Arrow

    // Release events
    void ZKeyReleased();
    void SKeyReleased();
    void QKeyReleased();
    void DKeyReleased();

    void RAKeyReleased();
    void LAKeyReleased();
    void UAKeyReleased();
    void DAKeyReleased();

public:
    EventHandeler();
    void PressInput(QKeyEvent *event);
    void ReleaseInput(QKeyEvent *event);
    void Link(GameWindow *gamewindow,bool IsReset);

private:
    ///bool listen=1;// At the moment not needed.
};

#endif // EVENTHANDELER_H
