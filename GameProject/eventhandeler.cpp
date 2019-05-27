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
    case Qt::Key_Up:
        emit UpKeyPressed();
        break;
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
    }
}

void EventHandeler::Link(GameWindow *gamewindow){
    // Here we place all the connections of key input to the different slots of objects in gamewindow;
    // this the objects don't need to think about the event handeling and focus and so on...
    QObject::connect(this,SIGNAL(PKeyPressed()),gamewindow,SLOT(PauzeGame()));
    QObject::connect(this,SIGNAL(CKeyPressed()),gamewindow->Game->Labyrinth,SLOT(TESTPressedC()));

    // Movement player

    //DummyEllipse *EliPointer=gamewindow->Game->Ellli;

    QObject::connect(this,SIGNAL(ZKeyPressed()),gamewindow->Game->Lennart,SLOT(UpKeyPressed()));
    QObject::connect(this,SIGNAL(SKeyPressed()),gamewindow->Game->Lennart,SLOT(DownKeyPressed()));
    QObject::connect(this,SIGNAL(QKeyPressed()),gamewindow->Game->Lennart,SLOT(LeftKeyPressed()));
    QObject::connect(this,SIGNAL(DKeyPressed()),gamewindow->Game->Lennart,SLOT(RightKeyPressed()));
    QObject::connect(this,SIGNAL(ZKeyReleased()),gamewindow->Game->Lennart,SLOT(UpKeyReleased()));
    QObject::connect(this,SIGNAL(SKeyReleased()),gamewindow->Game->Lennart,SLOT(DownKeyReleased()));
    QObject::connect(this,SIGNAL(QKeyReleased()),gamewindow->Game->Lennart,SLOT(LeftKeyReleased()));
    QObject::connect(this,SIGNAL(DKeyReleased()),gamewindow->Game->Lennart,SLOT(RightKeyReleased()));
}
