#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>

namespace Ui {
class GameWindow;
}
class TestClass;
class EventHandeler;

class GameWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void keyPressEvent(QKeyEvent *event);// I Can't seem to get the KeyPressEvent focus not to work the other, So we will imidiatily send it off to an eventhandler class we wrote our self.

public slots:
    void ChangeScene(QGraphicsScene *Scene);
    void TESTChangeto1();// these are all just TEST slots, who need to be removed later.
    void TESTChangeto2();
    void TESTAdvance();

signals:
    void Advance();//Put this is a seperate class ownd not by the GameWindow but by some game class. (needs to be created)


private:
    Ui::GameWindow *ui;
    TestClass *Test;
    EventHandeler *EventH;
    // We also inherent class the CentralWidget, since the class "GameWindow" get the public members of UI_gamewindow.h Class.
    // Weirdly enough the class GameWindow has an GameWindow object. So this GameWindow object should be able to reference it self. via ui->ui But this not seem possible.
    // AAAH The reason for this is becaus it are two different Classes!! You have the Ui::GameWindow and the GameWindow class. the GameWindow class contains an Ui::GameWindow


};

#endif // GAMEWINDOW_H
