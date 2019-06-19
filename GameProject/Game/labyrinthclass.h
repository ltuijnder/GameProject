#ifndef LABYRINTHCLASS_H
#define LABYRINTHCLASS_H

#include <QObject>
#include <vector>
#include <QGraphicsScene>// Not needed this is just for the demo right now
#include <QRectF>
#include <QString>
#include "layout.h"

class GameClass;// Declare that these classes exist, since the header is contained in the .cpp file
class Room;

class LabyrinthClass : public QObject
{
    Q_OBJECT

signals:
    void ChangeScene(Room * NewScene);
    void GenerateRooms(); //Let all the Rooms generate/Fill up

public slots:
    void StartLayout();
    void TESTPressedC();// This is a TEST Remove Later
    void ChangeRoom(unsigned Direction);

private:
    // Flags
    bool LayoutIsGenerated;// Here really the room layout is generated
    bool FloorIsGenerated;// For this we really look at that the vector "Floor" is filled up with rooms that are ready for use.
    bool IsStarted;// Aka the game has started
    bool IsSetup=0;// Fairly important
    bool IsLoaded;// To see if the vector layout and floor have been filled by loading a safe file, such that we know we don't need to generate a new one.

    // Variables
    unsigned Level;// Level keep track of the difficulty.
    std::vector<Room *> *Floor;//A pointer to a Vector of pointers!!.
    Layout *Floorplan;// Layout

    // Add a variable layout? Maybe handy if we need to find next room?
    int TESTCurrentNumber;// Don't remove yet is being used for changescene at the moment!

    // Functions
    void GenerateLayout();
    void ClearFloor();// If we go to the next floor we should be able to delete the previous.
    void GenerateNewFloor();

    QString SaveLayout();// Saves the layout
    void LoadLayout(QString str);

public:
    explicit LabyrinthClass(QObject *parent = nullptr);
    ~LabyrinthClass();
    void Setup(GameClass *Game);

    bool isloaded(){return IsLoaded;}

    QString SaveHeader();
    void LoadHeader(QString str);

    QString SaveRooms();
    void LoadFloor(QString str);
};

#endif // LABYRINTHCLASS_H
