#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsScene>
#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <vector>
#include <algorithm>
#include <QList>
#include <QString>

#include "labyrinthclass.h" //This is needed to declare friendships!

class SceneObject;

class Room : public QGraphicsScene // QGraphics.. already inherents QObject, so need to do it again.
{
    Q_OBJECT

friend class LabyrinthClass;// Only LabyringhtClass should be allowed to fidle with ROOM
// actually I only want GenerateLayout to be able to fiddle with Room.
// But GenerateLayout is private in the scope of Room so "friend" has no acces to GenerateLayout
// one could solve this by letting generateLayout be public in Labyrinthclass, which is a no no.

signals:
    void RoomIsCleared();
    //void DoorWasEntered(unsigned Direction);


public slots:
    void FillUp();
    void DeleteSceneObject(SceneObject *);
    void CheckClear();
    void DoorWasEntered(unsigned Direction);

private:
    //Flags
    bool IsSetup=0;
    bool IsFilled;
    bool RoomTypeIsSet;

    //Variables
    bool IsCleared;// Just check how many enemies there are
    int RoomType;
    int Position;
    LabyrinthClass *PointerToLaby;

public:
    // Essential
    explicit Room(QObject *parent = nullptr);
    ~Room();
    void Setup(LabyrinthClass *ptoLaby);

    // Functions

    int NumberOfEnemies();
    std::vector<SceneObject *> collidingObjects(SceneObject *);

    void SetRoomType(int Type);
    void SetRoomPosition(int Pos);// Let the type be what it needs to be.

    QString SaveHeader();
    void LoadHeader(QString str);

    QString SaveObjects();
    void LoadObjects(QString str);

};

#endif // ROOM_H
