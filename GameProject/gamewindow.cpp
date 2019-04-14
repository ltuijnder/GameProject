#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow){
    ui->setupUi(this);// So the Ui is a reference to its self.
}


GameWindow::~GameWindow(){
    delete ui;
}


void GameWindow::FirstPage(){
    ui->stackedWidget->setCurrentIndex(0);
}

void GameWindow::SecondPage(){
    ui->stackedWidget->setCurrentIndex(1);
}
