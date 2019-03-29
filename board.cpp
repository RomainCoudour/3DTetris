#include "board.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

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
    nextPiece = TetrisFactory::createPiece();

    connect(&mTimer,  &QTimer::timeout, [&] {
        if(!isOnPause && !isLost){
            if(!checkForCollisions())
                pieceDrop(curPiece);
            else
                nextMove();
            updateGL();
        }
    });

    mTimer.setInterval(100);
    mTimer.start();

    // Grid as array
    initializeGrid();
}

Board::~Board()
{
    // TODO : NoMemoryLeak
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
        glVertex3f(i,GRID_ROWS,0);
    };
    glEnd();

    glBegin(GL_LINES);
    for(int i=0;i<=20;i++) {
        glColor3f(1,1,1);
        glVertex3f(0,i,0);
        glVertex3f(GRID_COLUMNS,i,0);
    };
    glEnd();

    checkForRowsComplete();
    drawBlocks();
    curPiece.display();
}


// Fonction de gestion d'interactions clavier
void Board::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    if(!isOnPause && !isLost)
    case Qt::Key_Left:
        if(!checkForCollisionsBeforeMoving(LEFT))
            curPiece.onWebcamEvent(LEFT);
        break;
    case Qt::Key_Right:
        if(!checkForCollisionsBeforeMoving(RIGHT))
            curPiece.onWebcamEvent(RIGHT);
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
        if(!checkForCollisionsBeforeMoving(ROTATE))
            curPiece.onWebcamEvent(ROTATE);
        break;
    case Qt::Key_P:
        isOnPause = !isOnPause;
        if(isOnPause)
            mTimer.stop();
        else
            mTimer.start();
        break;
    default:
        event->ignore();
        break;
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}

void Board::pieceDrop(TetrisPiece piece){
    for(Block* block : piece.getBlocks())
        block->drop();
}

void Board::initializeGrid(){
    array.resize(GRID_ROWS, vector<Block*>(GRID_COLUMNS,nullptr));
}

void Board::drawBlocks(){
    for(int i = 0; i < GRID_ROWS; i++)
        for(int j = 0; j < GRID_COLUMNS; j++){
            if(array[i][j] != nullptr)
                array[i][j]->displayBlock();
        }
}

bool Board::checkForCollisions(){
    for(Block* block : curPiece.getBlocks()){
        if(block->getCurrOrigin().y()-1 < LOWER_BORDER || checkArrayForCollisions(block, DROP)){
            return true;
        }
    }
    return false;
}

bool Board::checkForCollisionsBeforeMoving(int direction){
    // TODO : if piece might hit a border or a block, return true;
    // Créer une pièce fictive, la tourner et checker si elle touche les bords

    QPoint points [4];

    switch (direction) {

    case RIGHT:
        for(Block* block : curPiece.getBlocks()){
            if (block->getCurrOrigin().x()+1 >= SIDE_BORDER_RIGHT)
                return true;
        }
        break;

    case LEFT:
        for(Block* block : curPiece.getBlocks()){
            if (block->getCurrOrigin().x()-1 < SIDE_BORDER_LEFT)
                return true;
        }
        break;

    case ROTATE:
        for (int i = 0; i < curPiece.getOrigins().size(); i++) {
            points[i] = QPoint(-curPiece.getBlocks().at(i)->getOrigine().y(),curPiece.getBlocks().at(i)->getOrigine().x());
            if (points[i].x()+curPiece.getBlocks().at(i)->getXTranslate() < -5 || points[i].x() + curPiece.getBlocks().at(i)->getXTranslate()>4 || points[i].y() + curPiece.getBlocks().at(i)->getYTranslate()<-20)
                return true;
        }
        break;

    default:
        break;
    }
    return false;
}

bool Board::checkArrayForCollisions(Block* block, int direction){
    QPoint coord = block->getCurrOrigin();
    if(coord.y() < GRID_ROWS && coord.y() > LOWER_BORDER && coord.x() > SIDE_BORDER_LEFT && coord.x() < SIDE_BORDER_RIGHT){
        switch (direction) {
        case LEFT:
            return(array[coord.y()][coord.x()-1] != nullptr);
            break;
        case RIGHT:
            return(array[coord.y()][coord.x()+1] != nullptr);
            break;
        case DROP:
            return(array[coord.y()-1][coord.x()] != nullptr);
            break;
        case ROTATE:
            return(array[coord.y()][coord.x()] != nullptr);
            break;
        default:
            return false;
            break;
        }
    }
    return false;
}

void Board::checkForRowsComplete(){
    int currRow = 0;
    tempArray.resize(GRID_ROWS, vector<Block*>(GRID_COLUMNS,nullptr));

    for(int i = 0; i < GRID_ROWS; i++){
        isRowComplete = true;
        for(int j = 0; j < GRID_COLUMNS; j++){
            if(array[i][j] == nullptr){
                isRowComplete = false;
                fillTempArray(currRow, i);
                currRow++;
                break;
            }
        }
        if(isRowComplete){
            for(Block* block : array[i]){
                delete[] block;
                block = nullptr;
            }
        }
    }

    array = tempArray;
}

void Board::fillTempArray(int currRow, int rowToAdd){
    for(int j = 0; j < GRID_COLUMNS; j++){
        tempArray[currRow][j] = array[rowToAdd][j];
    }
}

void Board::nextMove(){
    for(Block* block : curPiece.getBlocks())
        array[block->getCurrOrigin().y()][block->getCurrOrigin().x()] = block;

    curPiece = nextPiece;
    nextPiece = TetrisFactory::createPiece();
}
