#include "testclass.h"
#include "gamewindow.h" // Do not place this in the HEADERFILE since then you get loop headerfiles!! But still we need the definitions of gamewindow.


TestClass::TestClass(){
    QWidget(0);
}

void TestClass::Setup(GameWindow *game,int numb){
    number=numb;
}

