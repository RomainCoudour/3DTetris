#ifndef BOARD_H
#define BOARD_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>
#include <vector>
#include "tetrisfactory.h"
#include "tetrispiece.h"
#include "block.h"
#include "piecewindow.h"

using namespace std;

/*
 * Class Board : Définie le plateau de jeu, les interactions avec les élements extérieurs (Webcam, Clavier, Score..).
 * Elle gère les collisions, le déroulement d'une partie et sa fin.
 */

class Board : public QGLWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = 0);
    ~Board();

    // Methods
    TetrisPiece getNextPiece() { return nextPiece; }
    PieceWindow* getPieceWindow() { return pWindow; }
    void setPieceWindow(PieceWindow* pw) { pWindow = pw; }

    // GL Methods
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    // Method : Transmet les mouvements webcam à la pièce
    void tetrisMove(int move);
    // Method : Transmet les mouvements clavier à la pièce
    void keyPressEvent(QKeyEvent * event);
    // Method : Instant drop de la pièce
    void pieceDrop(TetrisPiece piece);
    // Method : Initialise la grille (matrice contenant les blocks)
    void initializeGrid();
    // Method : Dessine les blocks contenu dans la grille
    void drawBlocks();
    // Method : Vérifie les collisions sur DROP (Timer) et SPAWN
    bool checkForCollisions(int type);
    // Method : Vérifie les collisions avec l'exécution d'un mouvement
    bool checkForCollisionsBeforeMoving(int direction);
    // Method : Vérifie les collisions entre les blocks
    bool checkArrayForCollisions(Block* block, int direction);
    // Method : Vérifie si une ligne est complète
    bool checkForRowsComplete();
    // Method : Nettoie une ligne complète et met à jour la grille de jeu
    void clearCompleteRow(int i);
    // Method : Donne le contrôle à une nouvelle pièce courante et crée une pièce suivante
    void nextMove();
    // Method : Reset la grille, jeu et score
    void reset();
    // Metod : Vérifie si la pièce est au dessus de la grille et définie la fin du jeu
    bool pieceOutOfBound(TetrisPiece piece);

signals:
    // Emit : ligne réalisée, incremente score
    void rowCleared();
    // Emit : partie reset, reset score
    void resetScore();

public slots:
    // Gèrent les signaux webcam pour commander le mouvement
    void moveDrop();
    void moveRight();
    void moveLeft();
    void moveRotate();
    void stopMove();


private:
    // Constants (settings de la grille)
    int GRID_COLUMNS = 10;
    int GRID_ROWS = 20;
    int LOWER_BORDER = 0;
    int SIDE_BORDER_LEFT = 0;
    int SIDE_BORDER_RIGHT = 10;

    // Indice de la ligne a nettoyé
    int row;
    // Pour une ligne complète
    bool isComplete = false;
    // Pour la fin du  jeu
    bool isLost = false;
    // Pour la détection de la pause
    bool isOnPause = false;

    QTimer mTimer;
    TetrisPiece curPiece;
    TetrisPiece nextPiece;
    // Grille de jeu (matrice des blocks)
    vector<vector<Block*>> array;
    PieceWindow* pWindow;
};

#endif // BOARD_H
