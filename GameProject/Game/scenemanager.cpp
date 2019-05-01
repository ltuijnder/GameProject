#include "scenemanager.h"
#include "gameclass.h"

/******* Essential Functions *******/
SceneManager::SceneManager(QObject *parent) : QObject(parent){
    // Nothing
}

SceneManager::~SceneManager(){
    delete GameClock;
}

void SceneManager::Setup(GameClass *Game){
    // Create Variables
    Fps=1;
    GameClock=new QTimer;
    CurrentPrint=1;

    // Flags
    ClockIsRunning=0;
    SceneIsConnected=0;
    IsStarted=0;
    // Create links

    QObject::connect(Game,SIGNAL(GameHasStarted()),this,SLOT(StartSceneManager()));
}

/******* SLOTS *******/

void SceneManager::StartSceneManager(){
    // Establish Connection
    SceneManager::CreateConnection();
    // Start Clock
    SceneManager::StartClock();
    IsStarted=1;
}

void SceneManager::StartClock(){
    GameClock->start(1000/Fps);
    ClockIsRunning=1;
}

void SceneManager::StopClock(){
    GameClock->stop();
    ClockIsRunning=0;
    SceneManager::ChangePrint();// Every time we stop the timer we change scenes.
}

void SceneManager::ChangeCurrentScene(QGraphicsScene *NewScene){
    // Stop the clock (Maybe not needed): StopClock();
    // Break Current Connection: BreakConnection();
    // Transfer Player to the new: TransferPlayer(NewScene);
    // Replace The Scene: SetCurrentScene(NewScene);
    // Connect the new Scene to the clock: CreateConnection();
    // Update the GraphicsView in UI::GameWindow to the new Scene: emit CurrentSceneChanged(NewScene)
    // Start the clock again: StartClock();
}

void SceneManager::TestPrint(){
    std::cout<<"TestPrint is called"<<std::endl;
}

void SceneManager::TestPrint2(){
    std::cout<<"TestPrint2 is called"<<std::endl;
}

void SceneManager::ChangePrint(){
    if(CurrentPrint==1){
        BreakConnection();
        CreateConnection2();
        CurrentPrint=2;
    }else{
        BreakConnection();
        CreateConnection();
        CurrentPrint=1;
    }
}

/******* Functions *******/

void SceneManager::CreateConnection(){
    if(SceneIsConnected){// Create a better Error handeling
        std::cout<<"Error: a connection is already established, Clear the connection first to reconnect"<<std::endl;
        return;
    }
    connection=QObject::connect(GameClock,SIGNAL(timeout()),this,SLOT(TestPrint()));// Put here CurrentScene!!
    SceneIsConnected=1;
}

void SceneManager::BreakConnection(){
    if(!SceneIsConnected){
        std::cout<<"Warning: there was already no connection"<<std::endl;
        return;
    }
    QObject::disconnect(connection);
    SceneIsConnected=0;
}

void SceneManager::CreateConnection2(){// DELETE ME THIS IS JUST A TEST FOR PRINT
    if(SceneIsConnected){// Create a better Error handeling
        std::cout<<"Error: a connection is already established, Clear the connection first to reconnect"<<std::endl;
        return;
    }
    connection=QObject::connect(GameClock,SIGNAL(timeout()),this,SLOT(TestPrint2()));// Put here CurrentScene!!
    SceneIsConnected=1;
}

void SceneManager::TransferPlayer(QGraphicsScene *NewScene){
    // Get position of player.
    // Do something like, Remove QgraphicsItem from scene. (Player QgraphicsItem is hold by GameClass)
    // Then add in to then new scene
    // Change it position. Depending on it's original position.
}

bool SceneManager::SetCurrentScene(QGraphicsScene *NewScene){
    if(SceneIsConnected){
        std::cout<<"ERROR: Cannot set CurrentScene, while the old one is still connected"<<std::endl;
        return 0;
    }
    CurrentScene=NewScene;
    return 1;
}
