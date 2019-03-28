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
    //Uncommment and implement when collisions are set
    //nextPiece = TetrisFactory::createPiece();

    connect(&mTimer,  &QTimer::timeout, [&] {
        pieceDrop();
        updateGL();
    });

    mTimer.setInterval(1000);
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
        glVertex3f(i-5,0,0);
        glVertex3f(i-5,-20,0);
    };
    glEnd();

    glBegin(GL_LINES);
    for(int i=0;i<=20;i++) {
        glColor3f(1,1,1);
        glVertex3f(-5,-i,0);
        glVertex3f(5,-i,0);
    };
    glEnd();

    // Affichage éléments
    drawBlocks(); // Dessiner les blocks après le checkForCollisions pour éviter opérations inutiles non ?
    // checkForCollisions(); // ... a vérifier lors d'un déplacement plutôt ? Et donc renverrait un boolean.
    //Attention, prendre en compte le déplacement vertical TIMER !
    checkForRowsComplete();

    curPiece.display();
}


// Fonction de gestion d'interactions clavier
void Board::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
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
    default:
        event->ignore();
        break;
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}

void Board::pieceDrop(){
    for(Block* block : curPiece.getBlocks())
        block->drop();
}

void Board::initializeGrid(){
    array.resize(GRID_ROWS, vector<Block*>(GRID_COLUMNS,nullptr));
}

void Board::drawBlocks(){
    for(int i = 0; i < GRID_ROWS; i++)
        for(Block* block : array[i]){
            if(block != nullptr)
                block->displayBlock();
        }
}

bool Board::checkForCollisions(){
    // TODO : if piece.x hits x = +-5 = side border
    // return true

    // TODO : if piece.y hits y = -21 = lower border
    // TODO : if piece hits blocks
    //Transfert les pointeurs vers array, transfert nextPiece, retrun true

    return false;
}

bool Board::checkForCollisionsBeforeMoving(int direction){
    // TODO : if piece might hit a border or a block, return true;
    return false;
}

void Board::checkForRowsComplete(){

    //TODO : Reste à baisser les lignes pour combler les trous, attention a ne pas changer dynamiquement array dans un for
    // Possible idée : créer un tableau temporaire et y ajouter les rangs non complets
    int currRow = 0;

    // A mettre dans le constructeur pour appel une fois seulement ? Ou la méthode clear, défonce tout ?
    tempArray.resize(GRID_ROWS, vector<Block*>(GRID_COLUMNS,nullptr));

    for(int i = 0; i < GRID_ROWS; i++){
        isRowComplete = true;
        for(Block* block : array[i]){
            if(block == nullptr){
                isRowComplete = false;
                fillTempArray(curRow, i);
                curRow++;
                break;
            }
        }
        if(isRawComplete){
            for(Block* block : array[i]){
                delete[] block;
                block = nullptr;
            }
        }
    }

    array = tempArray;
    tempArray.clear();
}

// TODO : Regarder la cohérence
void Board::fillTempArray(int currRow, int rowToAdd){
    for(int j = 0; j < GRID_COLUMNS; j++){
        tempArray[currRow][j] = array[rowToAdd][j];
    }
}
