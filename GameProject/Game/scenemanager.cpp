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
    CurrentScene=nullptr;// Set the Start up Scene to null pointer, for if something would go wrong we don't acces random memory.

    // Flags
    ClockIsRunning=0;
    SceneIsConnected=0;
    IsStarted=0;
    SceneIsSet=0;
    // Create links

    QObject::connect(Game,SIGNAL(GameHasStarted()),this,SLOT(StartSceneManager()));// important else nothing works
}

/******* SLOTS *******/

void SceneManager::StartSceneManager(){
    if(SceneIsSet){// It could be that StartSceneManger is called BEFORE the scene is set by Layout.
        // Establish Connection
        if(SceneIsConnected==0){
            SceneManager::CreateConnection();// If Scene was not Set. Then Qt
        }
        // Start Clock
        if(ClockIsRunning==0){
            SceneManager::StartClock();
        }
    }
    IsStarted=1;
}

void SceneManager::StartClock(){
    GameClock->start(1000/Fps);// value is in ms, while Fps= frame per second.
    ClockIsRunning=1;
}

void SceneManager::StopClock(){
    GameClock->stop();
    ClockIsRunning=0;
}

void SceneManager::ChangeCurrentScene(QGraphicsScene *NewScene){
    if(ClockIsRunning) StopClock();// These firsts checks are done in the case that a scene was not set at all.
    if(SceneIsConnected) BreakConnection();
    // Transfer Player to the new: TransferPlayer(NewScene);
    SetCurrentScene(NewScene);// Set the scene
    if(SceneIsSet==0) SceneIsSet=1;// Now we can say for sure that the scene is set.
    CreateConnection();// Connect the new Scene to the clock
    emit CurrentSceneChanged(NewScene); // Update the GraphicsView in UI::GameWindow to the new Scene:
    if(IsStarted) StartClock();// Only start the clock if the game has started. StartSceneManager will automaticly call startclock.
}


/******* Functions *******/

void SceneManager::CreateConnection(){
    if(SceneIsConnected){// Create a better Error handeling
        std::cout<<"Error: a connection is already established, Clear the connection first to reconnect"<<std::endl;
        return;
    }
    connection=QObject::connect(GameClock,SIGNAL(timeout()),CurrentScene,SLOT(advance()));
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
