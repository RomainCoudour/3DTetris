#include "tetrisfactory.h"
#include "tetrispiece.h"
#include <QRandomGenerator>

TetrisFactory::TetrisFactory() {}

TetrisFactory::~TetrisFactory(){}

TetrisPiece TetrisFactory::createPiece(){
    TetrisShape shape = setShape();
    return(TetrisPiece(setColor(shape), getOrigins(shape)));
}

TetrisShape TetrisFactory::setShape(){
   return(TetrisShape(QRandomGenerator::global()->bounded(7) + 1));
}

QColor TetrisFactory::setColor(TetrisShape shape){
    switch (shape) {
    case ZShape:
        return(QColor("red"));
        break;
    case SShape:
        return(QColor("green"));
        break;
    case LineShape:
        return(QColor("cyan"));
        break;
    case TShape:
        return(QColor("purple"));
        break;
    case SquareShape:
        return(QColor("yellow"));
        break;
    case LShape:
        return(QColor("blue"));
        break;
    case MirroredLShape:
        return(QColor("orange"));
        break;
    case NoShape:
        return(QColor("white"));
        break;
    default:
        return(QColor("white"));
        break;
    }
}

vector<QPoint> TetrisFactory::getOrigins(TetrisShape shape){
    vector<QPoint> origins(PIECE_SIZE);

    switch (shape) {
    case ZShape:
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(-1,0));
        origins.push_back(QPoint(0,1));
        origins.push_back(QPoint(1,1));
        break;
    case SShape:
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(1,0));
        origins.push_back(QPoint(0,1));
        origins.push_back(QPoint(-1,1));
        break;
    case LineShape:
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(0,1));
        origins.push_back(QPoint(0,2));
        origins.push_back(QPoint(0,3));
        break;
    case TShape:
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(0,1));
        origins.push_back(QPoint(1,1));
        origins.push_back(QPoint(-1,1));
        break;
    case SquareShape:
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(2,0));
        origins.push_back(QPoint(2,2));
        origins.push_back(QPoint(0,2));
        break;
    case LShape:
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(0,-1));
        origins.push_back(QPoint(0,1));
        origins.push_back(QPoint(0,2));
        break;
    case MirroredLShape:
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(0,-1));
        origins.push_back(QPoint(0,-1));
        origins.push_back(QPoint(0,-2));
        break;
    default:
        break;
    }
    return origins;
}
