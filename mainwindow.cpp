#include "mainwindow.h"
#include <QApplication>

const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;

MainWindow::MainWindow()
{
    setFixedSize(WIN_WIDTH,WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    mScore = 0;
    mBoard = new Board(this);
    mPWindow = mBoard->getPieceWindow();
    cam = new WebCam(this);

    cam->move(0,520);

    mBoard->setFixedSize(1200,900);
    mBoard->move(600,0);
    mPWindow->setFixedSize(350,350);
    mPWindow->move(25,25);

    score = new QLabel(this);
    score->setText("Score : " + QString::number(mScore));
    score->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QFont font = score->font();
    font.setPointSize(40);
    score->setFont(font);
    score->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
    score->move(25,400);
    score->setFixedSize(350,100);

    connect(mBoard, SIGNAL(resetScore()), this, SLOT(resetScore()));
    connect(mBoard, SIGNAL(rowCleared()), this, SLOT(increaseScore()));

    connect(cam, SIGNAL(moveDrop()), mBoard, SLOT(moveDrop()));
    connect(cam, SIGNAL(moveLeft()), mBoard, SLOT(moveLeft()));
    connect(cam, SIGNAL(moveRight()), mBoard, SLOT(moveRight()));
    connect(cam, SIGNAL(moveRotate()), mBoard, SLOT(moveRotate()));
    connect(cam, SIGNAL(stopMove()), mBoard, SLOT(stopMove()));

    mTimer.setInterval(500);
    mTimer.start();

}

MainWindow::~MainWindow(){
    delete mBoard;
    delete mPWindow;
    delete score;
    delete cam;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Escape)
        QApplication::closeAllWindows();
    mBoard->keyPressEvent(event);
    event->accept();
}


void MainWindow::increaseScore(){
    mScore++;
    displayScore();
}

void MainWindow::displayScore(){
    score->setText("Score : " + QString::number(mScore));
}

void MainWindow::resetScore(){
    mScore = 0;
    displayScore();
}
