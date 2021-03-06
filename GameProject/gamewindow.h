#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

// For some weird reason we can not include our own projects file here in the header file...
// This creates a whole lot of problems in the linking phase: it could not find the implentation of functions and all that kind of stuff...
// For that reason we take the same approach as the QT Wizard: Include the header file of the code we want to use in the .cpp file,
// But still declare in this .h file that that class exist such that we can use it.
#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QRectF>
#include <iostream>
#include <string>
#include <QDir>


// Declare that the following classes exist with there respectif name space and such. Only include the .h file in the .cpp file (see explanation above)
namespace Ui {
class GameWindow; // UI::GameWindow contains all the graphical elements/widgets, edit this in the .ui file. This class is not to be confused with "GameWindow" which is declared below.
}
//class TestClass; // With this class we just first test out some ideas, before really implementing its own class.
class EventHandeler; // We want events to be handled by a seperate class
class GameClass; // This is where the reall magic happens.

class GameWindow : public QMainWindow{
    Q_OBJECT// Declares it to be a QObject. which we want it to be, since now we can use signals and slots. Want this on ANY Class in this project.

signals:
    void SignalStartGame();
    void SignalPauzeGame();
    void SignalUnPauzeGame();

public slots:
    // Change Page Slots.
    void GoToStartPage();
    void GoToGameSelectPage();
    void GoToGamePage();
    void GoToPauzePage();
    void GoToGameOverPage();
    void PauzeGame();// And Unpauze!
    void SlotStartGame();
    void ChangeCurrentScene(QGraphicsScene* NewScene);
    void SaveGame();
    void LoadGame();
    void ResetGame();

private:
    Ui::GameWindow *ui;
    //TestClass *Test;
    EventHandeler *EventH;
    QRectF SceneRect;// Dimensions of the Scene that will be vieuwed.
    std::string SafeFileName;


public:
    // For now make them public But They actually have to be private, but when they make connection they need to be linked
    GameClass *Game;

    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void keyPressEvent(QKeyEvent *event);// Only QMainWindow can directly receive QEvents. So imediatly pass these events towards EventHandler.
    void keyReleaseEvent(QKeyEvent *event);
    QRectF GetSceneRect() const;

};

#endif // GAMEWINDOW_H
