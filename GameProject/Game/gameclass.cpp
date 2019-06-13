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
    //plswork= new TestQobject;
    SManager->Setup(this);
    Labyrinth->Setup(this);
    Lennart->Init(nullptr);// For now just null pointer
    //plswork->Init();
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

void GameClass::Save(std::string NameSafeFile){
    // First see if the directory exist and if not create it.
    QDir dir=QDir::home();// Start from home folder.
    if(!dir.cd(".GameProject")) dir.mkdir(".GameProject");
    dir.cd(".GameProject");
    if(!dir.cd("SaveFiles")) dir.mkdir("SaveFiles");
    dir.cd("SaveFiles");
    std::string Path=dir.path().toStdString();

    // Create save file.
    std::string filename(Path+"/"+NameSafeFile);
    std::ofstream file(filename.c_str());
    if(!file){
        std::cout<<"Warning couldn't open file"<<filename<<std::endl;
        return;
    }
    // First the Header is created.
    QString Header("");
    Header.append("*Header*\n");
    Header.append("**Names**\n");
    // Add The naming and stuff. FileName, GameName, PlayerName,...
    QString FileName = QString::fromUtf8(NameSafeFile.c_str());
    Header.append(","+FileName+",");// information is always between commas
    Header.append("**Names**\n");
    Header.append("**Stats**\n");
    // Do the stats stuff. Kills,
    Header.append("**Stats**\n");
    Header.append("**Labirinth**\n");
    //Header.append(Labyrinth->SafeLab());// Add information for labirtn Level, seed.
    Header.append("**Labirinth**\n");
    Header.append("**Player**\n");
    Header.append(Lennart->SavePlayer());// All the information of the player class.
    Header.append("**Player**\n");
    Header.append("*Header*\n");
    // Next we create the string that holds all the information of the rooms in labyrinth.
    QString Lab("");// Lab=Labyrinth
    Lab.append("*Labyrinth*\n");
    Lab.append(Labyrinth->SaveRooms());
    Lab.append("*Labyrinth*\n");

    QString ToSafe=Header+Lab;
    file<<ToSafe.toStdString();

    file.close();

}

/******* Functions *******/
