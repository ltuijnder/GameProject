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
    setFocusPolicy(Qt::StrongFocus);// Important the GameWindow get's focus. Such that it can receive input from key and mouse

    //QObject::connect(this,SIGNAL(Advance()),Test->CurrentScene,SLOT(advance()));// Use current scene!! such that if you switch scenes the scene that we see at the moment evolves.
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

void GameWindow::ChangeScene(QGraphicsScene *Scene){
    ui->graphicsView->setScene(Scene);// Or atleast the correct path to it.
}

// Remove TEST later
void GameWindow::TESTChangeto1(){
    Test->ChangeSceneTo(1);
}
void GameWindow::TESTChangeto2(){
    Test->ChangeSceneTo(2);
}
void GameWindow::TESTAdvance(){
    std::cout<<"signal emmited"<<std::endl;
    emit Advance();
}
