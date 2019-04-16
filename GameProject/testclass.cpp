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
    Ellipse *Elli=new Ellipse;


    Scene1->addItem(Elli);
    Scene2->addRect(0,0,100,100);

    // Place connection declarations as the first thing. since you might already use the connection in the setup
    // Statement above is wrong. Still place as last Becauses connection might use objects that were still not setup. (here CurrentScene)
    QObject::connect(this,SIGNAL(SceneHasChanged(QGraphicsScene*)),game,SLOT(ChangeScene(QGraphicsScene*)));

    SetCurrentScene(Scene1);// Now we can properely setup scene1 from the get go

    // Important if make the connection !! The connection is object bounded. So if you click advance you will advance the scene but only that same scene. It will not reconnect to the "Current scene"

    QObject::connect(game,SIGNAL(Advance()),CurrentScene,SLOT(advance()));// Use current scene!! such that if you switch scenes the scene that we see at the moment evolves.

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
