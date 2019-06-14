#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <QObject>
#include <iostream>

#include <QFile>
#include <QTextStream>
#include <fstream>
#include <sstream>
#include <QDir>

class GameWindow;
class SceneManager;
class LabyrinthClass;
#include "Game/SceneObjects/player.h"
#include "Game/SceneObjects/testqobject.h"

class GameClass : public QObject
{
    Q_OBJECT

signals:
    void GameHasStarted();
public slots:
    void StartGame();
    void PauzeGame();
    void ResumeGame();

private:
    // Flags
    bool IsRunning;// The game can be in an idle state, (when we are still in the menus)
    bool IsSetup=0;
    bool IsLoaded;// Use this to check wetter it should "generate"
    // Objects


public:
    // For now make them public But They actually have to be private, but when they make connection they need to be linked
    SceneManager *SManager;
    LabyrinthClass *Labyrinth;
    Player *Lennart;


    explicit GameClass(QObject *parent = nullptr);
    ~GameClass();
    void Setup(GameWindow *gamewindow);

    void Save(std::string NameSafeFile);
    void LoadFile(std::string NameFile);



};

#endif // GAMECLASS_H
