#include "gamewindow.h"
#include "ui_gamewindow.h"
//#include "testclass.h"
#include "eventhandeler.h"
#include "Game/gameclass.h"
#include "Game/scenemanager.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    //Test(new TestClass),
    EventH(new EventHandeler),
    Game(new GameClass){

    ui->setupUi(this);// initiate all the graphical elements. !!
    Game->Setup(this);
    //Test->Setup(this);
    setFocusPolicy(Qt::StrongFocus);// Important the GameWindow get's focus. Such that it can receive input from key and mouse

    // LINKS
    // Do this as last operatorion once everything is defind.
    EventH->Link(this);
    QObject::connect(Game->SManager,SIGNAL(CurrentSceneChanged(QGraphicsScene *)),this,SLOT(ChangeCurrentScene(QGraphicsScene*)));
}

GameWindow::~GameWindow(){
    delete ui;
    //delete Test;
    delete EventH;
    delete Game;
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
    if(ui->stackedWidget->currentWidget()==ui->GamePage){// Check if we are first on the correct Page, since "P" should not be called from everywhere.
        GameWindow::GoToPauzePage();
        emit SignalPauzeGame();
    }else if(ui->stackedWidget->currentWidget()==ui->PauzePage){
        GameWindow::GoToGamePage();
        emit SignalUnPauzeGame();
    }

}

void GameWindow::SlotStartGame(){
    emit SignalStartGame();// Why this complication? A QButton can only link to slots.
}

void GameWindow::ChangeCurrentScene(QGraphicsScene *NewScene){
    ui->graphicsView->setScene(NewScene);
}
