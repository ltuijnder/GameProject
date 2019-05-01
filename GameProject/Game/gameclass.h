#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <QObject>
#include <iostream>

class GameWindow;
class SceneManager;
class LabyrinthClass;

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

    explicit GameClass(QObject *parent = nullptr);
    ~GameClass();
    void Setup(GameWindow *gamewindow);

};

#endif // GAMECLASS_H
