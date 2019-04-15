#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "testclass.h"
#include "eventhandeler.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    Test(new TestClass),
    EventH(new EventHandeler){

    ui->setupUi(this);// So the Ui is a reference to its self.
    Test->Setup(this);
    setFocusPolicy(Qt::StrongFocus);// Important the GameWindow get's focus.


    // Do this as last operatorion once everything is defind.
    EventH->Link(this);
}

GameWindow::~GameWindow(){
    delete ui;
    delete Test;
    delete EventH;
}

void GameWindow::keyPressEvent(QKeyEvent *event){
    EventH->KeyInput(event);
}
