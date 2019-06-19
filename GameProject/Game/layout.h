#ifndef LAYOUT_H
#define LAYOUT_H


#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <QDir>
#include <QString>
#include <QStringList>
#include <fstream>
#include <sstream>// Is needed for the std::stringstream. which we use for the buffer in FillFloor

#include "layoutelement.h"

class Room;// Just declare that there is a class room in the the .cpp we include the header
class LabyrinthClass;

class Layout
{

private:
    // Flags
    bool LayoutIsGenerated;// Here really the room layout is generated
    bool LayoutIsAllocated;// Here we mean that the vector Layout is really allocated and not just a dangling pointer. And we are safe to work with it.
    bool IsSetup=0;

    // Variables
    int floor_Index;
    int layoutIndex;
    int SideLength;
    LabyrinthClass *PointerToLaby;// We need this since we connect the room with labyrinthclass in order to change rooms.
    std::vector<Layoutelement *> *layout;// This is representation of the 2D Floorlayer, However we represent it here in 1D vector. since nested vectors are ineffecient.


    // Functions
    int to1D(unsigned row, unsigned column);// think Matrix notation.
    void printLayout();// Just to see if everything works.
    bool createEmptyLayout();
    void setElementIndex();
    void setDoorType();
    void CdTemplateType(QDir &dir,int DoorType);

    // associated to random generation.
    int dist(int refLindex, int othLindex);
    //void FurtherThen(int d ,Layoutelement *ref,std::vector<Layoutelement *> &Solution);
    void FurtherThen(int d,int refLindex, std::vector<int> &Solution);
    void ConnectTwoPoints(int Lindex1, int Lindex2,bool b);// With this we mean fill the inbetween with room.
    void FurtherThenFromLayout(int d, std::vector<int> &Solution);// Does not work needs to be fixed.
    void ClosestRooms(int Lindex,std::vector<int> &Solution);

    // Save
    QString SaveLayout();
    void LoadLayout(QString str);

public:
    // essential
    Layout();
    ~Layout();
    void SetUp(LabyrinthClass *ptoLaby);

    // Public Functions
    bool ValidDirection(unsigned Direction);// To check that we are not at the edge or something.
    unsigned NextRoomIndex(unsigned Direction);

    void setSideLength(int level);
    bool generateLayout();
    void FillFloor(std::vector<Room *> *Floor);
    bool IsLayoutGenerated();
    int FloorIndex();

    // save
    QString Save();
    void Load(QString str);

};

#endif // LAYOUT_H
