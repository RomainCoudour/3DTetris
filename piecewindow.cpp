#include "piecewindow.h"

const unsigned int WIN_WIDTH  = 600;
const unsigned int WIN_HEIGHT = 600;
const float MAX_DIMENSION     = 50.0f;

PieceWindow::PieceWindow(QWidget *parent, TetrisPiece piece)
    : QGLWidget(parent)
{
    mPiece = piece;
    //setFixedSize(WIN_WIDTH,WIN_HEIGHT);
    //move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

PieceWindow::~PieceWindow(){}

void PieceWindow::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
}


// Fonction de redimensionnement
void PieceWindow::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Fonction d'affichage
void PieceWindow::paintGL()
{

    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION ); // Bien veiller à sélectionner la matrice GL_PROJECTION
    glLoadIdentity( ); // La reinitialiser, on ne sait jamais
    gluPerspective(70, (float)WIN_HEIGHT/WIN_WIDTH, -1., 2.); // Définir les paramètres pour notre projection orthographique

    // Definition de la matrice modelview
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

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}
