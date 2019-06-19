#ifndef ROOMINF_H
#define ROOMINF_H

#include <iostream>
#include <QString>
#include <QStringList>

class Layoutelement
{

private:
    bool isRoom;
    int Floorindex;
    int Layoutindex;
    int DoorType;// Read it as bits!! bits from right to left are= up,right,down,left.

public:
    Layoutelement();

    bool IsRoom(){return isRoom;}
    int FIndex(){return Floorindex;}
    int LIndex(){return Layoutindex;}
    int doorType(){return DoorType;}

    int Row(unsigned sidelength);
    int Col(unsigned sidelength);

    void setRoom(bool boolian);
    void setFIndex(int Findex);
    void setLIndex(int Lindex);
    void setDoorType(int type);

    // Save
    QString Save();
    void Load(QString str);

};

#endif // ROOMINF_H
