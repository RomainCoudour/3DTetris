#include "tetrisfactory.h"
#include "tetrispiece.h"
#include <QRandomGenerator>

TetrisFactory::TetrisFactory() {}

TetrisFactory::~TetrisFactory(){}

TetrisPiece TetrisFactory::createPiece(){
    TetrisShape shape = setShape();
    return(TetrisPiece(shape, setColor(shape), getOrigins(shape)));
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
    vector<QPoint> origins;

    switch (shape) {
    case ZShape:
        //{ 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 }
        origins.push_back(QPoint(0,-1));
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(-1,0));
        origins.push_back(QPoint(-1,1));
        break;
    case SShape:
        //{ 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 }
        origins.push_back(QPoint(0,-1));
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(1,0));
        origins.push_back(QPoint(1,1));
        break;
    case LineShape:
        //{ 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 }
        origins.push_back(QPoint(0,-1));
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(0,1));
        origins.push_back(QPoint(0,2));
        break;
    case TShape:
        //{ -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 }
        origins.push_back(QPoint(-1,0));
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(1,0));
        origins.push_back(QPoint(0,1));
        break;
    case SquareShape:
        //{ 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 }
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(1,0));
        origins.push_back(QPoint(0,1));
        origins.push_back(QPoint(1,1));
        break;
    case LShape:
        //{ 0, -1 }, { 0, 0 },  { 1, 0 },   { 2, 0 }
        origins.push_back(QPoint(0,-1));
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(1,0));
        origins.push_back(QPoint(2,0));
        break;
    case MirroredLShape:
        //{ 0, 0 },  { 1, 0 },  { 2, 0 },   { 2, -1 }
        origins.push_back(QPoint(0,0));
        origins.push_back(QPoint(1,0));
        origins.push_back(QPoint(2,0));
        origins.push_back(QPoint(2,-1));
        break;
    default:
        break;
    }
    return origins;
}
