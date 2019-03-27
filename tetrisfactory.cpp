#include "tetrisfactory.h"
#include <QRandomGenerator>

TetrisFactory::TetrisFactory() {}

TetrisFactory::~TetrisFactory(){}

TetrisPiece TetrisFactory::createPiece(){
    TetrisShape shape = setShape();
    if(shape != NoShape)
        return(new setColor(shape), getOrigins(shape));
    return NULL;
}

TetrisShape TetrisPiece::setShape(){
   return(TetrisShape(QRandomGenerator::global()->bounded(7) + 1));
}

QColor TetrisPiece::setColor(TetrisShape shape){
    switch (shape) {
    case ZShape:
        return(QColor(Qt::GlobalColor(red)));
        break;
    case SShape:
        return(QColor(Qt::GlobalColor(green)));
        break;
    case LineShape:
        return(QColor(Qt::GlobalColor(cyan)));
        break;
    case TShape:
        return(QColor(Qt::GlobalColor(purple)));
        break;
    case SquareShape:
        return(QColor(Qt::GlobalColor(yellow)));
        break;
    case LShape:
        return(QColor(Qt::GlobalColor(blue)));
        break;
    case MirroredLShape:
        return(QColor(Qt::GlobalColor(orange)));
        break;
    case NoShape:
        return(QColor(Qt::GlobalColor(white)));
        break;
    default:
        break;
    }
}

vector<QPoint> getOrigins(TetrisShape shape){
    QPoint point;
    vector<QPoint> origins(PIECE_SIZE, 0);

    switch (shape) {
    case ZShape:
        break;
    case SShape:
        return(QColor(Qt::GlobalColor(green)));
        break;
    case LineShape:
        return(QColor(Qt::GlobalColor(cyan)));
        break;
    case TShape:
        return(QColor(Qt::GlobalColor(purple)));
        break;
    case SquareShape:
        return(QColor(Qt::GlobalColor(yellow)));
        break;
    case LShape:
        return(QColor(Qt::GlobalColor(blue)));
        break;
    case MirroredLShape:
        return(QColor(Qt::GlobalColor(orange)));
        break;
    default:
        break;
    }
    return origins;
}
