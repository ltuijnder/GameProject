#include "testclass.h"
#include "gamewindow.h" // Do not place this in the HEADERFILE since then you get loop headerfiles!! But still we need the definitions of gamewindow.
#include "graphicsitems.h"

TestClass::TestClass(){
    QWidget(0);
}

void TestClass::Setup(GameWindow *game,int numb){
    number=numb;
    //Fill up scenes
    Scene1=new QGraphicsScene;
    Scene2=new QGraphicsScene;
    CurrentScene=Scene2;// We cannot use signals to set CurrentScene since the signals still need to be defined !But we have to allocate currentscene else Segmentation fault in connect.
    //Ellipse *Elli=new Ellipse;

}

TestClass::~TestClass(){
    delete Scene1;
    delete Scene2;
    //delete Elli; Not necessary see: https://doc.qt.io/archives/qt-4.8/qgraphicsscene.html QGraphicsScene::~QGraphicsScene()
}

void TestClass::SetCurrentScene(QGraphicsScene *NewScene){
    if(NewScene==CurrentScene) return;// NewScene is the same scene so do nothing
    CurrentScene=NewScene;
    emit SceneHasChanged(CurrentScene);// Emit signal, Which the main GameWindow should receive.
}

void TestClass::ChangeSceneTo(int i){
    switch (i) {
    case 1:
        SetCurrentScene(Scene1);
        break;
    case 2:
        SetCurrentScene(Scene2);
        break;
    }
}
void TestClass::Print(){
    std::cout<<"PRINT"<<std::endl;
}
