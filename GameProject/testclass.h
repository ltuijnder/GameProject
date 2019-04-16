#ifndef TESTCLASS_H
#define TESTCLASS_H

//#include <QObject>
#include <iostream>
#include <QWidget>
#include <QGraphicsScene>


class GameWindow;

class TestClass:public QWidget{
    Q_OBJECT

private:
    int number;
    QGraphicsScene *Scene1,*Scene2;

protected:
    void SetCurrentScene(QGraphicsScene *NewScene);

signals:
    void SceneHasChanged(QGraphicsScene *NewCurrentScene);

public slots:
    void Print();

public:
    QGraphicsScene *CurrentScene;

    //TestClass(QWidget *parent=Q_NULLPTR):QWidget(parent){std::cout<<"I Was Called"<<std::endl;}
    TestClass();// We can't do the above since TestClass will be called with new, where you cannot give constructer parameters with it.
    ~TestClass();
    void Setup(GameWindow *game, int numb=0);
    void ChangeSceneTo(int i=1);
};

#endif // TESTCLASS_H
