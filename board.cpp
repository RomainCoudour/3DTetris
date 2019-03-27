#include "board.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float MAX_DIMENSION     = 50.0f;

Board::Board(QWidget *parent)
    : QGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    curPiece = TetrisFactory::createPiece();

    connect(&mTimer,  &QTimer::timeout, [&] {
        pieceDrop();
        updateGL();
    });

    mTimer.setInterval(10);
    mTimer.start();
}

Board::~Board()
{

}


// Fonction d'initialisation
void Board::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
}


// Fonction de redimensionnement
void Board::resizeGL(int width, int height)
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
void Board::paintGL()
{

    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Affichage grille jeu
    glBegin(GL_LINES);
    for(int i=0;i<=10;i++) {
        glColor3f(1,1,1);
        glVertex3f(i,0,0);
        glVertex3f(i,20,0);
    };
    glEnd();

    glBegin(GL_LINES);
    for(int i=0;i<=20;i++) {
        glColor3f(1,1,1);
        glVertex3f(0,i,0);
        glVertex3f(10,i,0);
    };
    glEnd();


    curPiece.display();
}


// Fonction de gestion d'interactions clavier
void Board::keyPressEvent(QKeyEvent * event)
{
   switch(event->key())
    {
        // Cas par defaut
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}

void Board::pieceDrop(){
    for(Block* block : curPiece.getBlocks())
        block->drop();
}
