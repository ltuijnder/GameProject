#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <QObject>
#include <iostream>

#include <QFile>
#include <QTextStream>
#include <fstream>
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
    // Objects


public:
    // For now make them public But They actually have to be private, but when they make connection they need to be linked
    SceneManager *SManager;
    LabyrinthClass *Labyrinth;
    Player *Lennart;
    //DummyEllipse *Ellli;
    //TestQobject *plswork;


    explicit GameClass(QObject *parent = nullptr);
    ~GameClass();
    void Setup(GameWindow *gamewindow);

    void Save(std::string NameSafeFile);



};

#endif // GAMECLASS_H
