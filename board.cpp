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
    curPiece = TetrisFactory::createPiece();
    nextPiece = TetrisFactory::createPiece();
    pWindow = new PieceWindow(parent, nextPiece);
    mScore = new int(0);

    connect(&mTimer,  &QTimer::timeout, [&] {
        if(!isOnPause && !isLost){
            if(!checkForCollisions(DROP))
                pieceDrop(curPiece);
            else
                nextMove();
            updateGL();
        }

    });

    mTimer.setInterval(1000);
    mTimer.start();

    initializeGrid();
}

Board::~Board()
{
    delete pWindow;
    delete mScore;
}

void Board::initializeGL()
{

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glEnable(GL_DEPTH_TEST);
}

void Board::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

void Board::paintGL()
{
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

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(70, (float)WIN_WIDTH/WIN_HEIGHT, 2, -1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 5, 0, 12, // position de la caméra
    5, 7, 0, // position du point que fixe la caméra
    0, 1, 0); // vecteur vertical

    while(checkForRowsComplete()){
        clearCompleteRow(row);
    }

    drawBlocks();
    curPiece.display();
    if(isLost){
        qglColor(QColor(255,0,0));
        renderText(2.0,10.0,0.0,QString("YOU LOSE"), QFont("Helvetica", 30));
        renderText(1.0,8.0,0.0,QString("Press R to retry"), QFont("Helvetica", 30));
    }

    pWindow->setPiece(nextPiece);
    pWindow->updateGL();
}

void Board::tetrisMove(int move){
    if(!isOnPause && !isLost){
        switch (move) {
        case LEFT:

            if(!checkForCollisionsBeforeMoving(LEFT))
                curPiece.onWebcamEvent(LEFT);
            break;
        case RIGHT:
            if(!checkForCollisionsBeforeMoving(RIGHT))
                curPiece.onWebcamEvent(RIGHT);
            break;
        case ROTATE:
            if(!checkForCollisionsBeforeMoving(ROTATE))
                curPiece.onWebcamEvent(ROTATE);
            break;
        case DROP:
            mTimer.stop();
            while(!checkForCollisions(DROP)){
                pieceDrop(curPiece);
                updateGL();
            }
            mTimer.start();

            break;
        case NOTHING:
            break;
        }
        updateGL();
    }
}

void Board::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        if(!isOnPause && !isLost)
            if(!checkForCollisionsBeforeMoving(LEFT))
                curPiece.onWebcamEvent(LEFT);
        break;
    case Qt::Key_Right:
        if(!isOnPause && !isLost)
            if(!checkForCollisionsBeforeMoving(RIGHT))
                curPiece.onWebcamEvent(RIGHT);
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
        if(!isOnPause && !isLost)
            if(!checkForCollisionsBeforeMoving(ROTATE))
                curPiece.onWebcamEvent(ROTATE);
        break;
    case Qt::Key_Space:
        if(!isOnPause && !isLost){
            mTimer.stop();
            while(!checkForCollisions(DROP)){
                pieceDrop(curPiece);
                updateGL();
            }
            mTimer.start();
        }
        break;

    case Qt::Key_R :
        isLost = false;
        isOnPause = false;
        reset();
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
            if(array[i][j] != nullptr){
                if(isLost)
                    array[i][j]->setColor(QColor("grey"));
                array[i][j]->displayBlock();
            }
        }
}

bool Board::checkForCollisions(int type){
    for(Block* block : curPiece.getBlocks()){
        switch (type) {
        case DROP:
            if(block->getCurrOrigin().y()-1 < LOWER_BORDER || checkArrayForCollisions(block, DROP))
                return true;
            break;

        case SPAWN:
            if(checkArrayForCollisions(block, SPAWN))
                return true;
        default:
            break;
        }
    }
    return false;
}

bool Board::checkForCollisionsBeforeMoving(int direction){

    switch (direction) {

    case RIGHT:
        for(Block* block : curPiece.getBlocks()){
            if (block->getCurrOrigin().x()+1 >= SIDE_BORDER_RIGHT || checkArrayForCollisions(block,RIGHT))
                return true;
        }
        break;

    case LEFT:
        for(Block* block : curPiece.getBlocks()){
            if (block->getCurrOrigin().x()-1 < SIDE_BORDER_LEFT || checkArrayForCollisions(block,LEFT))
                return true;
        }
        break;

    case ROTATE:
        for(Block* block : curPiece.getBlocks()){
            // Dublication du block courant avec une couleur "random" et toutes ses caractéristiques. On tourne le dupliqué
            // et on check si ses coordonnées touchent les bords de la grille ou les blocks existants.

            Block* blockTest = new Block(QColor("red"),block->getOrigin());
            blockTest->setXTranslate(block->getXTranslate());
            blockTest->setYTranslate(block->getYTranslate());
            blockTest->rotate();
            blockTest->updateOrigin();
            if (blockTest->getCurrOrigin().x() < SIDE_BORDER_LEFT || blockTest->getCurrOrigin().x() >= SIDE_BORDER_RIGHT || blockTest->getCurrOrigin().y() < LOWER_BORDER || checkArrayForCollisions(blockTest, ROTATE)){
                blockTest->~Block();
                return true;
            }
            blockTest->~Block();
        }
        break;

    default:
        break;
    }
    return false;
}

bool Board::checkArrayForCollisions(Block* block, int direction){
    QPoint coord = block->getCurrOrigin();

    if(coord.y() < GRID_ROWS && coord.y() >= LOWER_BORDER && coord.x() >= SIDE_BORDER_LEFT && coord.x() < SIDE_BORDER_RIGHT){
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
        case SPAWN:
            return(array[coord.y()][coord.x()] != nullptr);
            break;
        default:
            return false;
            break;
        }
    }
    return false;
}

bool Board::checkForRowsComplete(){
    for(int i = 0; i < GRID_ROWS; i++){
        row = i;
        for(Block* b : array[i]){
            if(b == nullptr){
                isComplete = false;
                break;
            }
            else
                isComplete = true;
        }
        if(isComplete) return isComplete;
    }
    return false;
}

void Board::clearCompleteRow(int i){
    for(Block* b : array[i])
            delete b;

    while(i < 19){
        for(Block* b : array[i+1])
            if(b != nullptr)
                b->drop();

        array[i] = array[i+1];
        i++;
    }

    // TODO : emit signal
    *mScore = *mScore+1;
}

void Board::nextMove(){
    if(!pieceOutOfBound(curPiece)){
        for(Block* block : curPiece.getBlocks())
            array[block->getCurrOrigin().y()][block->getCurrOrigin().x()] = block;

        curPiece = nextPiece;
        nextPiece = TetrisFactory::createPiece();

        if(checkForCollisions(SPAWN)){
            isLost = !isLost;
        }
    }
    else{
        isLost = !isLost;
    }
}

void Board::reset(){
    mTimer.stop();

    for(int i = 0; i < GRID_ROWS; i++)
        for(int j = 0; j < GRID_COLUMNS; j++){
            array[i][j] = nullptr;
        }

    curPiece = TetrisFactory::createPiece();
    nextPiece = TetrisFactory::createPiece();

    updateGL();

    mTimer.start();
}

bool Board::pieceOutOfBound(TetrisPiece piece){
    for(Block* block : piece.getBlocks())
        if(block->getCurrOrigin().y() >= 20)
            return true;
    return false;
}
