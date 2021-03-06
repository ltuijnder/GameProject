#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QMetaObject>
#include <QGraphicsScene>
#include <QPointF>

class GameClass;
class Room;

class SceneManager : public QObject
{
    Q_OBJECT
signals:
    void CurrentSceneChanged(QGraphicsScene *NewScene);

public slots:
    void StartSceneManager();
    void StartClock();
    void StopClock();
    void ChangeCurrentScene(Room *NewRoom);
private:
    //Flags
    bool IsStarted;
    bool ClockIsRunning;
    bool SceneIsConnected;
    bool SceneIsSet;

    // Variables
    QTimer *GameClock;
    float Fps;
    QMetaObject::Connection connection;// We need to have a hold of the connection if we want to specificly disconnect it again.
    QGraphicsScene *CurrentScene;
    GameClass *PointerToGame;// Because we need to acces Player.

    // Functions
    void CreateConnection();
    void BreakConnection();
    void TransferPlayer(Room *NewRoom);// Player should be transferd. To the new scene
    bool SetCurrentScene(QGraphicsScene *NewScene);// Have a bool to tell if it was succesful.
public:
    explicit SceneManager(QObject *parent = nullptr);
    ~SceneManager();
    void Setup(GameClass *Game);
};

#endif // SCENEMANAGER_H
