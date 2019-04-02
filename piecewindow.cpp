#include "piecewindow.h"

const unsigned int WIN_WIDTH  = 600;
const unsigned int WIN_HEIGHT = 600;
const float MAX_DIMENSION     = 50.0f;

PieceWindow::PieceWindow(QWidget *parent, TetrisPiece piece)
    : QGLWidget(parent)
{
    mPiece = piece;
}

PieceWindow::~PieceWindow(){}

void PieceWindow::initializeGL()
{
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    glEnable(GL_DEPTH_TEST);
}

void PieceWindow::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void PieceWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(70, (float)WIN_HEIGHT/WIN_WIDTH, -1., 2.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 5.5, 21, 4, // position de la caméra
    5.5, 21, 0, // position du point que fixe la caméra
    0, 1, 0); // vecteur vertical

    mPiece.display();
}

void PieceWindow::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
        case Qt::Key_Z:
            break;
    default:
        event->ignore();
        break;
    }
    event->accept();
    updateGL();
}
