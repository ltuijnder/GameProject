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
    //delete Lennart; We do not delete lennart since items in a scene automaticlly get deleted.
}

void GameClass::Setup(GameWindow *gamewindow){
    // Create variables:
    SManager=new SceneManager;
    Labyrinth=new LabyrinthClass;
    Lennart=new Player;
    SManager->Setup(this);
    Labyrinth->Setup(this);
    Lennart->Init(nullptr);// For now just null pointer

    IsRunning=0;// The Game is not running, It has just been Setup, Nothing more.
    IsLoaded=0;
    // Create the needed links towards the gamewindow (always let the object that is last created make the link)
    QObject::connect(gamewindow,SIGNAL(SignalStartGame()),this,SLOT(StartGame()));
    QObject::connect(gamewindow,SIGNAL(SignalPauzeGame()),this,SLOT(PauzeGame()));
    QObject::connect(gamewindow,SIGNAL(SignalUnPauzeGame()),this,SLOT(ResumeGame()));

    IsSetup=1;
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
    Header.append(Labyrinth->SaveHeader());// Add information for labirtn Level, seed. The Layout !! important.
    Header.append("**Labirinth**\n");
    Header.append("**Player**\n");
    Header.append(Lennart->SavePlayer());// All the information of the player class.
    Header.append("**Player**\n");
    Header.append("*Header*\n");
    // Next we create the string that holds all the information of the rooms in labyrinth.
    QString Lab("");// Lab=Labyrinth
    Lab.append("*Floor*\n");
    Lab.append(Labyrinth->SaveRooms());
    Lab.append("*Floor*\n");

    QString ToSafe=Header+Lab;
    file<<ToSafe.toStdString();
    file.close();
}

void GameClass::LoadFile(std::string NameFile){
    if(!IsSetup){// If NOT setup then not peruist
        std::cout<<"Error GameClass::loadfile was not setup so can not load file"<<std::endl;
        return;
    }if(IsLoaded){// If IS loaded then not persuit
        std::cout<<"Error GameClass::loadfile GameClass was already loaded"<<std::endl;
        return;
    }if(IsRunning){// if IS running then not persuit
        std::cout<<"Error GameClass::loadfile GameClass was already running"<<std::endl;
        return;
    }
    QDir dir=QDir::home();// Start from home folder.
    if(!dir.cd(".GameProject")) return;
    dir.cd(".GameProject");
    if(!dir.cd("SaveFiles")) return;
    dir.cd("SaveFiles");
    std::string Path=dir.path().toStdString();

    std::string filename(Path+"/"+NameFile);
    std::ifstream file(filename.c_str());
    if(!file){
        std::cout<<"Warning couldn't open file "<<filename<<std::endl;
        return;
    }
    std::stringstream buffer;// The reason for this very complicated conversion thing can be motivated by the following
    buffer<< file.rdbuf();// https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring second answer
    std::string stdstring=buffer.str();// https://stackoverflow.com/questions/662976/how-do-i-convert-from-stringstream-to-string-in-c
    QString FileContent=QString::fromUtf8(stdstring.data(),stdstring.size());// https://stackoverflow.com/questions/4338067/convert-stdstring-to-qstring with comment
    QString Names=FileContent.section("**Names**",1,1);
    // I don't know what exactly to do with it but we have it.
    QString Stats=FileContent.section("**Stats**",1,1);
    // If we have a stats class load it.
    QString Labirinth=FileContent.section("**Labirinth**",1,1);
    // Do stuff with load labyrinth Important ! because it needs to load the layout.
    Labyrinth->LoadHeader(Labirinth);
    QString player=FileContent.section("**Player**",1,1);
    Lennart->Load(player);
    QString Floor=FileContent.section("*Floor*",1,1);
    Labyrinth->LoadFloor(Floor);

    IsLoaded=1;
}

