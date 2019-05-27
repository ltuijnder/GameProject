#include "gameclass.h"
#include "gamewindow.h"
#include "scenemanager.h"
#include "labyrinthclass.h"
//#include "Game/SceneObjects/player.h"

/******* Essential Functions *******/
GameClass::GameClass(QObject *parent) : QObject(parent){
    // Nothing should happen here. Do all the set up in SetUp Function.
    // We have no controll on when this function is called, while with SetUp we are really explicit.
}

GameClass::~GameClass(){
    delete SManager;
    delete Labyrinth;
    //delete Lennart; We do not delete lennart since items in a scena automaticlly get deleted.
}

void GameClass::Setup(GameWindow *gamewindow){
    // Create variables:
    SManager=new SceneManager;
    Labyrinth=new LabyrinthClass;
    Lennart=new Player;
    //Ellli= new DummyEllipse;
    plswork= new TestQobject;
    SManager->Setup(this);
    Labyrinth->Setup(this);
    Lennart->Init();
    plswork->Init();
    //Ellli->Init();

    IsRunning=0;// The Game is not running, It has just been Setup, Nothing more.
    // Create the needed links towards the gamewindow (always let the object that is last created make the link)
    QObject::connect(gamewindow,SIGNAL(SignalStartGame()),this,SLOT(StartGame()));
    QObject::connect(gamewindow,SIGNAL(SignalPauzeGame()),this,SLOT(PauzeGame()));
    QObject::connect(gamewindow,SIGNAL(SignalUnPauzeGame()),this,SLOT(ResumeGame()));
}

/******* SLOTS *******/
void GameClass::StartGame(){
    IsRunning=1;
    emit GameHasStarted();
}

void GameClass::PauzeGame(){
    SManager->StopClock();
}

void GameClass::ResumeGame(){
    SManager->StartClock();
}
/******* Functions *******/
