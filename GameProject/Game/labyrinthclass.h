#ifndef LABYRINTHCLASS_H
#define LABYRINTHCLASS_H

#include <QObject>
#include <vector>
#include <QGraphicsScene>// Not needed this is just for the demo right now

class GameClass;// Declare that these classes exist, since the header is contained in the .cpp file
class Room;

class LabyrinthClass : public QObject
{
    Q_OBJECT

signals:
    void ChangeScene(QGraphicsScene * NewScene);
    void GenerateRooms(); //Let all the Rooms generate/Fill up

public slots:
    void StartLayout();
    void TESTPressedC();// This is a TEST Remove Later
    void RoomTransfer(char Direction);

private:
    // Flags
    bool LayoutIsGenerated;
    bool FloorIsGenerated;
    bool IsStarted;

    // Variables
    unsigned NextLevel;// Level keep track of the difficulty.
    std::vector<Room *> *Floor;//A pointer to a Vector of pointers!!.
    // Add a variable layout? Maybe handy if we need to find next room?
    int TESTCurrentNumber;// REMOVE

    // Functions
    void GenerateLayout();
    void BuildFloor();
    void ClearFloor();// If we go to the next floor we should be able to delete the previous.


public:
    explicit LabyrinthClass(QObject *parent = nullptr);
    ~LabyrinthClass();
    void Setup(GameClass *Game);
};

#endif // LABYRINTHCLASS_H
