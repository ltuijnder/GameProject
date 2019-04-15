#include "eventhandeler.h"
#include "gamewindow.h"

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
    }
}

void EventHandeler::Link(GameWindow *gamewindow){
    // Here we place all the connections of key input to the different slots of objects in gamewindow;
    // this the objects don't need to think about the event handeling and focus and so on...
}
