#include "mainwindow.h"
#include <QApplication>

const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;

MainWindow::MainWindow()
{
    setFixedSize(WIN_WIDTH,WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    mBoard = new Board(this);
    mPWindow = mBoard->getPieceWindow();
    cam = new WebCam(this);//, 400, 500);

    cam->move(0,520);

    mBoard->setFixedSize(1200,900);
    mBoard->move(600,0);
    mPWindow->setFixedSize(350,350);
    mPWindow->move(25,25);

    score = new QLabel(this);
    score->setText("Score : " + QString::number(0));
    score->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QFont font = score->font();
    font.setPointSize(40);
    score->setFont(font);
    score->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
    score->move(25,400);
    score->setFixedSize(350,100);

    connect(&mTimer,  &QTimer::timeout, [&] {
        mBoard->tetrisMove(cam->getMove());
        score->setText("Score : " + QString::number(*(mBoard->getScore())));
    });

    mTimer.setInterval(500);
    mTimer.start();

}

MainWindow::~MainWindow(){}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Escape)
        QApplication::closeAllWindows();
    mBoard->keyPressEvent(event);
    event->accept();
}
