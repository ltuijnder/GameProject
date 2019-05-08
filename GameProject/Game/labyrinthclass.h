#ifndef LABYRINTHCLASS_H
#define LABYRINTHCLASS_H

#include <QObject>
#include <vector>
#include <QGraphicsScene>// Not needed this is just for the demo right now

class GameClass;

class LabyrinthClass : public QObject
{
    Q_OBJECT

signals:
    void ChangeScene(QGraphicsScene * NewScene);

public slots:
    void StartLayout();
    void TESTPressedC();// This is a TEST Remove Later

private:
    // Flags
    bool LayoutIsGenerated;
    bool RoomsAreFilled;
    bool IsStarted;

    // Variables
    unsigned Level;// Level keep track of the difficulty.
    std::vector<QGraphicsScene *> *VRooms;//VRooms=Vector of Rooms, A pointer to a Vector of pointers!!.
    int TESTCurrentNumber;

    // Functions
    void GenerateLayout();


public:
    explicit LabyrinthClass(QObject *parent = nullptr);
    ~LabyrinthClass();
    void Setup(GameClass *Game);
};

#endif // LABYRINTHCLASS_H
