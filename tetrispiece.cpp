#include "tetrispiece.h"
#include "block.h"
#include <QDebug>

TetrisPiece::TetrisPiece(){}

TetrisPiece::TetrisPiece(TetrisShape shape, QColor color, vector<QPoint> origins)
{
    mShape = shape;
    mColor = color;
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
    vector<QPoint> resOrigins;
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
        if(mShape != SquareShape){
            for (int i = 0; i < this->mOrigins.size(); i++){
                mPiece.at(i)->setOrigine(QPoint(-this->mOrigins.at(i).y(),this->mOrigins.at(i).x()));
                resOrigins.push_back(QPoint(-this->mOrigins.at(i).y(),this->mOrigins.at(i).x()));
            }
            this->mOrigins = resOrigins;
        }
        break;

    default:
        break;
    }
}
