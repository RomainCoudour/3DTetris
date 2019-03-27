#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include <QColor>
#include <vector>
#include "block.h"

using namespace std;

int const PIECE_SIZE = 4;
enum TetrisMouvement { LEFT, RIGHT, ROTATE };

class TetrisPiece
{

public:
    TetrisPiece();
    TetrisPiece(QColor color, vector<QPoint> origins);
    virtual ~TetrisPiece();

    //Methods
    void createPiece();
    void display();
    void onWebcamEvent(int direction);
    vector<Block*> getBlocks(){return mPiece;}

private:
    vector<Block*> mPiece;

    QColor mColor;
    vector<QPoint> mOrigins;
};

#endif // TETRISPIECE_H
