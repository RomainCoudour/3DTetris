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
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    Board* mBoard;
    PieceWindow* mPWindow;
    QLabel* score;
    int mScore;
    WebCam* cam;
    QTimer mTimer;

protected:
    void keyPressEvent(QKeyEvent * event);
    void displayScore();

public slots:
    void increaseScore();
    void resetScore();

};



#endif // MAINWINDOW_H
