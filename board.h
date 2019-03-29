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

using namespace std;

class Board : public QGLWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = 0);
    ~Board();

protected:
    // GL METHODS
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    // METHODS
    void keyPressEvent(QKeyEvent * event);
    void pieceDrop(TetrisPiece piece);
    void initializeGrid();
    void drawBlocks();
    bool checkForCollisions();
    bool checkForCollisionsBeforeMoving(int direction);
    bool checkArrayForCollisions(Block* block, int direction);
    void checkForRowsComplete();
    void fillTempArray(int currRow, int rowToAdd);
    void nextMove();


private:
    int GRID_COLUMNS = 10;
    int GRID_ROWS = 20;
    int LOWER_BORDER = 0; // Coord y de la dernière ligneH
    int SIDE_BORDER_LEFT = 0;
    int SIDE_BORDER_RIGHT = 10;
    bool isRowComplete = false;
    bool isLost = false;
    bool isOnPause = false;

    QTimer mTimer;
    TetrisPiece curPiece;
    TetrisPiece nextPiece;
    vector<vector<Block*>> array;
    vector<vector<Block*>> tempArray;

};

#endif // BOARD_H
