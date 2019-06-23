#include "eventhandeler.h"
#include "gamewindow.h"
#include "Game/gameclass.h"
#include "Game/labyrinthclass.h"
#include "Game/SceneObjects/testqobject.h"
#include <typeinfo>

EventHandeler::EventHandeler(){QWidget(0);

}

void EventHandeler::PressInput(QKeyEvent *event){
    if(event->isAutoRepeat()) return;// We don't want the auto repeat events!!!
    switch (event->key()) {
    case Qt::Key_P:
        emit PKeyPressed();
        break;
    case Qt::Key_C:
        emit CKeyPressed();
        break;
    case Qt::Key_Z:
        emit ZKeyPressed();
        break;
    case Qt::Key_S:
        emit SKeyPressed();
        break;
    case Qt::Key_Q:
        emit QKeyPressed();
        break;
    case Qt::Key_D:
        emit DKeyPressed();
        break;
    case Qt::Key_Right:
        emit RAKeyPressed();
        break;
    case Qt::Key_Left:
        emit LAKeyPressed();
        break;
    case Qt::Key_Up:
        emit UAKeyPressed();
        break;
    case Qt::Key_Down:
        emit DAKeyPressed();
        break;
    }

}

void EventHandeler::ReleaseInput(QKeyEvent *event){
    if(event->isAutoRepeat()) return;// We don't want the auto repeat events!!!
    switch (event->key()) {
    case Qt::Key_Z:
        emit ZKeyReleased();
        break;
    case Qt::Key_S:
        emit SKeyReleased();
        break;
    case Qt::Key_Q:
        emit QKeyReleased();
        break;
    case Qt::Key_D:
        emit DKeyReleased();
        break;
    case Qt::Key_Right:
        emit RAKeyReleased();
        break;
    case Qt::Key_Left:
        emit LAKeyReleased();
        break;
    case Qt::Key_Up:
        emit UAKeyReleased();
        break;
    case Qt::Key_Down:
        emit DAKeyReleased();
        break;
    }
}

void EventHandeler::Link(GameWindow *gamewindow,bool IsReset){
    // Here we place all the connections of key input to the different slots of objects in gamewindow;
    // this the objects don't need to think about the event handeling and focus and so on...
    if(!IsReset) QObject::connect(this,SIGNAL(PKeyPressed()),gamewindow,SLOT(PauzeGame()));// Only connect this once
    QObject::connect(this,SIGNAL(CKeyPressed()),gamewindow->Game->Labyrinth,SLOT(TESTPressedC()));

    // Movement player
    QObject::connect(this,SIGNAL(ZKeyPressed()),gamewindow->Game->Lennart,SLOT(UpKeyPressed()));
    QObject::connect(this,SIGNAL(SKeyPressed()),gamewindow->Game->Lennart,SLOT(DownKeyPressed()));
    QObject::connect(this,SIGNAL(QKeyPressed()),gamewindow->Game->Lennart,SLOT(LeftKeyPressed()));
    QObject::connect(this,SIGNAL(DKeyPressed()),gamewindow->Game->Lennart,SLOT(RightKeyPressed()));
    QObject::connect(this,SIGNAL(ZKeyReleased()),gamewindow->Game->Lennart,SLOT(UpKeyReleased()));
    QObject::connect(this,SIGNAL(SKeyReleased()),gamewindow->Game->Lennart,SLOT(DownKeyReleased()));
    QObject::connect(this,SIGNAL(QKeyReleased()),gamewindow->Game->Lennart,SLOT(LeftKeyReleased()));
    QObject::connect(this,SIGNAL(DKeyReleased()),gamewindow->Game->Lennart,SLOT(RightKeyReleased()));

    // Shooting
    QObject::connect(this,SIGNAL(RAKeyPressed()),gamewindow->Game->Lennart,SLOT(ShotRightPressed()));
    QObject::connect(this,SIGNAL(LAKeyPressed()),gamewindow->Game->Lennart,SLOT(ShotLeftPressed()));
    QObject::connect(this,SIGNAL(UAKeyPressed()),gamewindow->Game->Lennart,SLOT(ShotUpPressed()));
    QObject::connect(this,SIGNAL(DAKeyPressed()),gamewindow->Game->Lennart,SLOT(ShotDownPressed()));
    QObject::connect(this,SIGNAL(RAKeyReleased()),gamewindow->Game->Lennart,SLOT(ShotRightReleased()));
    QObject::connect(this,SIGNAL(LAKeyReleased()),gamewindow->Game->Lennart,SLOT(ShotLeftReleased()));
    QObject::connect(this,SIGNAL(UAKeyReleased()),gamewindow->Game->Lennart,SLOT(ShotUpReleased()));
    QObject::connect(this,SIGNAL(DAKeyReleased()),gamewindow->Game->Lennart,SLOT(ShotDownReleased()));

}
