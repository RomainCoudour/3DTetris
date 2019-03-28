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
    void pieceDrop();
    void initializeGrid();
    void drawBlocks();
    bool checkForCollisions();
    bool checkForCollisionsBeforeMoving(int direction);
    void checkForRowsComplete();
    void fillTempArray(int currRow, int rowToAdd);


private:
    int GRID_COLUMNS = 10;
    int GRID_ROWS = 20;
    int LOWER_BORDER = -21; // Coord y de la dernière ligneH
    int SIDE_BORDER = 5; // Coord x de la première/dernière ligneV
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
