#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

public slots:
    void FirstPage();
    void SecondPage();

private:
    Ui::GameWindow *ui;

    // We also inherent class the CentralWidget, since the class "GameWindow" get the public members of UI_gamewindow.h Class.
    // Weirdly enough the class GameWindow has an GameWindow object. So this GameWindow object should be able to reference it self. via ui->ui But this not seem possible.

};

#endif // GAMEWINDOW_H
