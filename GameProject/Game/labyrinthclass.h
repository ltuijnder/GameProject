#ifndef LABYRINTHCLASS_H
#define LABYRINTHCLASS_H

#include <QObject>
#include <vector>
#include <QGraphicsScene>// Not needed this is just for the demo right now
#include <QRectF>
#include <QString>

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
    void RoomTransfer(char Direction);

private:
    // Flags
    bool LayoutIsGenerated;
    bool FloorIsGenerated;
    bool IsStarted;
    bool IsSetup=0;
    bool IsLoaded;

    // Variables
    unsigned NextLevel;// Level keep track of the difficulty.
    std::vector<Room *> *Floor;//A pointer to a Vector of pointers!!.
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
