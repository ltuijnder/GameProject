#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsScene>
#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <vector>
#include <algorithm>
#include <QList>

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


public slots:
    void FillUp();
    void DeleteSceneObject(SceneObject *);

private:
    //Flags
    bool IsSetup=0;
    bool IsFilled;
    bool RoomTypeIsSet;

    //Variables
    int RoomType;
    int Position;
    // We now have one vector of the Scene Objects, But it would be perfectly possible to be more specific
    // For instance make vector of Enemies/ Temporarily/ Wall
    std::vector<SceneObject *> *Objects;

    //Functions
    void SetRoomType(int Type);
    void SetRoomPosition(int Pos);// Let the type be what it needs to be.

public:
    // Essential
    explicit Room(QObject *parent = nullptr);
    ~Room();
    void Setup();

    // Functions
    void addSceneObject(SceneObject *);

};

#endif // ROOM_H
