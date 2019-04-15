#ifndef TESTCLASS_H
#define TESTCLASS_H

//#include <QObject>
#include <iostream>
#include <QKeyEvent>
#include <QEvent>
#include <QWidget>


class GameWindow;

class TestClass:public QWidget{
    Q_OBJECT
private:
    int number;

public:
    //TestClass(QWidget *parent=Q_NULLPTR):QWidget(parent){std::cout<<"I Was Called"<<std::endl;}
    TestClass();// We can't do the above since TestClass will be called with new, where you cannot give constructer parameters with it.
    void Setup(GameWindow *game, int numb=0);
};

#endif // TESTCLASS_H
