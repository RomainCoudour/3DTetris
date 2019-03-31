#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QTimer>

#include "board.h"
#include "webcam.h"

class MainWindow : public QWidget
{
public:
    MainWindow();
    ~MainWindow();

private:
    Board* mBoard;
    PieceWindow* mPWindow;
    QLabel* score;
    WebCam* cam;
    QTimer mTimer;

protected:
    void keyPressEvent(QKeyEvent * event);

};



#endif // MAINWINDOW_H
