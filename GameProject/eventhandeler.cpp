#include "eventhandeler.h"
#include "gamewindow.h"
#include "Game/gameclass.h"
#include "Game/labyrinthclass.h"
EventHandeler::EventHandeler(){QWidget(0);

}

void EventHandeler::KeyInput(QKeyEvent *event){
    //if(!listen) return;
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
    }

}

void EventHandeler::Link(GameWindow *gamewindow){
    // Here we place all the connections of key input to the different slots of objects in gamewindow;
    // this the objects don't need to think about the event handeling and focus and so on...
    QObject::connect(this,SIGNAL(PKeyPressed()),gamewindow,SLOT(PauzeGame()));
    QObject::connect(this,SIGNAL(CKeyPressed()),gamewindow->Game->Labyrinth,SLOT(TESTPressedC()));
}
