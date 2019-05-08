#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QMetaObject>
#include <QGraphicsScene>

class GameClass;

class SceneManager : public QObject
{
    Q_OBJECT
signals:
    void CurrentSceneChanged(QGraphicsScene *NewScene);

public slots:
    void StartSceneManager();
    void StartClock();
    void StopClock();
    void ChangeCurrentScene(QGraphicsScene *NewScene);
private:
    //Flags
    bool IsStarted;
    bool ClockIsRunning;
    bool SceneIsConnected;
    bool SceneIsSet;

    // Variables
    QTimer *GameClock;
    float Fps;
    QMetaObject::Connection connection;
    QGraphicsScene *CurrentScene;
    int CurrentPrint;// represent current scene

    // Functions
    void CreateConnection();
    //void CreateConnection2();// This is just for printing sake.
    void BreakConnection();
    void TransferPlayer(QGraphicsScene *NewScene);// Player should be transferd. To the new scene
    bool SetCurrentScene(QGraphicsScene *NewScene);// Have a bool to tell if it was succesful.
public:
    explicit SceneManager(QObject *parent = nullptr);
    ~SceneManager();
    void Setup(GameClass *Game);
};

#endif // SCENEMANAGER_H
