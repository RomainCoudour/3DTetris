#ifndef TETRISFACTORY_H
#define TETRISFACTORY_H

#include "tetrispiece.h"
#include <QColor>

enum TetrisShape { NoShape, ZShape, SShape, LineShape, TShape, SquareShape,
                   LShape, MirroredLShape };

class TetrisFactory
{
public:
    static TetrisPiece createPiece();

private:
    TetrisFactory();
    virtual ~TetrisFactory();

    TetrisShape setShape();
    QColor setColor(TetrisShape shape);
    vector<QPoint> getOrigins(TetrisShape shape);
};

#endif // TETRISFACTORY_H
