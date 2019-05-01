#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <QObject>
#include <iostream>

class GameWindow;
class SceneManager;

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
    SceneManager *SManager;
public:
    explicit GameClass(QObject *parent = nullptr);
    ~GameClass();
    void Setup(GameWindow *gamewindow);

};

#endif // GAMECLASS_H
