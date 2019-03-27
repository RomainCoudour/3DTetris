#include "tetrispiece.h"
#include "block.h"

TetrisPiece::TetrisPiece(){}

TetrisPiece::TetrisPiece(QColor color, vector<QPoint> origins)
{
    mColor = color;
    mPiece.reserve(PIECE_SIZE);
    mOrigins = origins;
    createPiece();
}

TetrisPiece::~TetrisPiece(){
}

void TetrisPiece::createPiece(){
    for(QPoint origin : mOrigins){
        mPiece.push_back(new Block(mColor, origin));
    }
}

void TetrisPiece::display(){
    for(Block* block : mPiece)
        block->displayBlock();
}


void TetrisPiece::onWebcamEvent(int direction){
    switch (direction) {
    case LEFT:
        for(Block* block : mPiece)
            block->goingLeft();
        break;
    case RIGHT:
        for(Block* block : mPiece)
            block->goingRight();
        break;
    case ROTATE:
        for(Block* block : mPiece)
            block->rotate();
        break;

    default:
        break;
    }
}
