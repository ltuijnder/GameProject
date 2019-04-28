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
    //this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

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

/*** GoTo SLOTS ***/

void GameWindow::GoToStartPage(){ui->stackedWidget->setCurrentWidget(ui->StartPage);}
void GameWindow::GoToGamePage(){ui->stackedWidget->setCurrentWidget(ui->GamePage);}
void GameWindow::GoToGameSelectPage(){ui->stackedWidget->setCurrentWidget(ui->GameSelectPage);}
void GameWindow::GoToPauzePage(){ui->stackedWidget->setCurrentWidget(ui->PauzePage);}

void GameWindow::PauzeGame(){
    std::cout<<"P Key Pressed"<<std::endl;
    if(ui->stackedWidget->currentWidget()==ui->GamePage){
        GameWindow::GoToPauzePage();
        // emit PauzeGame ( to let game pauze)
    }else if(ui->stackedWidget->currentWidget()==ui->PauzePage){
        GameWindow::GoToGamePage();
        // emit UnPauzeGame ( to let te game play again)
    }

}
