#include "gamewindow.h"
#include "ui_gamewindow.h"
//#include "testclass.h"
#include "eventhandeler.h"
#include "Game/gameclass.h"
#include "Game/scenemanager.h"

#include <QDataStream>


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    //Test(new TestClass),
    EventH(new EventHandeler),
    Game(new GameClass){

    ui->setupUi(this);// initiate all the graphical elements. !!
    Game->Setup(this);
    SceneRect.setRect(0,0,100,100);// Its unclear what happens when I change this , I do not understand it. But it fixes the vieuw, which is what I wanted.
    SafeFileName="SafeFile.txt";
    ui->graphicsView->setSceneRect(SceneRect);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);// We don't want the graphicsview to gain input. This may result in no reaction of some buttons (arrow keys)
    setFocusPolicy(Qt::StrongFocus);// Important the GameWindow get's focus. Such that it can receive input from key and mouse

    // LINKS
    // Do this as last operatorion once everything is defind.
    EventH->Link(this,0);// Give bool zero since this is not a reset and a first time start
    QObject::connect(Game->SManager,SIGNAL(CurrentSceneChanged(QGraphicsScene *)),this,SLOT(ChangeCurrentScene(QGraphicsScene*)));
}

GameWindow::~GameWindow(){
    delete ui;
    //delete Test;
    delete EventH;
    delete Game;
}

void GameWindow::keyPressEvent(QKeyEvent *event){
    EventH->PressInput(event);
}

void GameWindow::keyReleaseEvent(QKeyEvent *event){
    EventH->ReleaseInput(event);
}

/*** GoTo SLOTS ***/

void GameWindow::GoToStartPage(){ui->stackedWidget->setCurrentWidget(ui->StartPage);}
void GameWindow::GoToGamePage(){ui->stackedWidget->setCurrentWidget(ui->GamePage);}
void GameWindow::GoToGameSelectPage(){ui->stackedWidget->setCurrentWidget(ui->GameSelectPage);}
void GameWindow::GoToPauzePage(){ui->stackedWidget->setCurrentWidget(ui->PauzePage);}
void GameWindow::GoToGameOverPage(){ui->stackedWidget->setCurrentWidget(ui->GameOver);}

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

void GameWindow::SaveGame(){
    Game->Save(SafeFileName);
}

void GameWindow::LoadGame(){
    Game->LoadFile(SafeFileName);
    // For now also emit signalStartGame Because the Load button will straight takes us to the game thingy.
    emit SignalStartGame();

}

void GameWindow::ResetGame(){
    Game->ResetGame();
    //Now we we need to relink everything
    EventH->Link(this,1);
    QObject::connect(Game->SManager, SIGNAL(CurrentSceneChanged(QGraphicsScene*)),this,SLOT(ChangeCurrentScene(QGraphicsScene*)));
}
