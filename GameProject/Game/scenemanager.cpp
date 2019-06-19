#include "scenemanager.h"
#include "gameclass.h"
#include "Game/SceneObjects/player.h"// since we transfer players
#include "Game/room.h"

/******* Essential Functions *******/
SceneManager::SceneManager(QObject *parent) : QObject(parent){
    // Nothing
}

SceneManager::~SceneManager(){
    delete GameClock;
}

void SceneManager::Setup(GameClass *Game){
    // Create Variables
    Fps=30;
    GameClock=new QTimer;
    CurrentScene=nullptr;// Set the Start up Scene to null pointer, for if something would go wrong we don't acces random memory.
    PointerToGame=Game;

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

void SceneManager::ChangeCurrentScene(Room *NewRoom){// We need to have a room since we want to setRoom in player.
    if(ClockIsRunning) StopClock();// These firsts checks are done in the case that a scene was not set at all.
    if(SceneIsConnected) BreakConnection();
    TransferPlayer(NewRoom);// Transfer Player to the new:
    SetCurrentScene(NewRoom);// Here upcast Room to QGraphicsScene
    if(SceneIsSet==0) SceneIsSet=1;// Now we can say for sure that the scene is set.
    CreateConnection();// Connect the new Scene to the clock
    emit CurrentSceneChanged(NewRoom); // Update the GraphicsView in UI::GameWindow to the new Scene:
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


void SceneManager::TransferPlayer(Room *NewRoom){
    float posx=PointerToGame->Lennart->x();
    float posy=PointerToGame->Lennart->y();
    // Now we test where lennart is. !! This is Coordinate dependend which is not been figured out correctly yet.
    if(posx>850){//Aka the right door  At the moment the ratios of the screen are totally off so for now do it this way.
        QPointF diff(-1645,0);// 870+775 is the current horizontal difference between the doors. Coordinate dependend !
        PointerToGame->Lennart->setPos(PointerToGame->Lennart->pos()+diff);
    }else if(posx<-750){// Aka the left door
        QPointF diff(1645,0);
        PointerToGame->Lennart->setPos(PointerToGame->Lennart->pos()+diff);
    }else if(posy>350){// aka the down door
        QPointF diff(0,-710);// 375+335 is the current vertical difference.
        PointerToGame->Lennart->setPos(PointerToGame->Lennart->pos()+diff);
    }else if(posy<-300){
        QPointF diff(0,710);
        PointerToGame->Lennart->setPos(PointerToGame->Lennart->pos()+diff);
    }
    // For now just add it.
    NewRoom->addItem(PointerToGame->Lennart); // Actually we don't need to worry that To first remove it from another scene since this is done
    PointerToGame->Lennart->SetRoom(NewRoom);
}

bool SceneManager::SetCurrentScene(QGraphicsScene *NewScene){
    if(SceneIsConnected){
        std::cout<<"ERROR: Cannot set CurrentScene, while the old one is still connected"<<std::endl;
        return 0;
    }
    CurrentScene=NewScene;
    return 1;
}
