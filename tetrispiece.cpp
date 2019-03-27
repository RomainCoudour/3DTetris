#include "tetrispiece.h"
#include "block.h"

TetrisPiece::TetrisPiece(){}

TetrisPiece::TetrisPiece(QColor color, vector<QPoint> origins)
{
    mColor = color;
    mPiece.reserve(PIECE_SIZE);
    mOrigins = origins;
}

TetrisPiece::~TetrisPiece(){
}

void TetrisPiece::createPiece(){
    for(QPoint origin : mOrigins){
        mPiece.push_back(new Block(mColor, origin));
    }
}

void TetrisPiece::onWebcamEvent(int direction){
    switch (direction) {
    case LEFT:
        //
        break;
    case RIGHT:
        //
        break;
    case ROTATE:
        //
        break;

    default:
        break;
    }
}
