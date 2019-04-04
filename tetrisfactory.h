#ifndef TETRISFACTORY_H
#define TETRISFACTORY_H

#include "tetrispiece.h"
#include <QColor>

/*
 * Class TetrisFactory : Classe statique qui créera les tetriminos en leur attribuant des couleurs, des formes et des origines.
 * Les origines correspondent aux origines des 4 blocs constituant le tétriminos.
 */

class TetrisFactory
{
public:
    //Method : Permet de créer le tétriminos en lui attribuant une forme et une couleur
    static TetrisPiece createPiece();

private:
    TetrisFactory();
    virtual ~TetrisFactory();

    //Method : Permet de générer aléatoirement une forme
    static TetrisShape setShape();
    //Method : Permet de générer une couleur en fonction de la forme du tetriminos
    static QColor setColor(TetrisShape shape);
    static vector<QPoint> getOrigins(TetrisShape shape);
};

#endif // TETRISFACTORY_H
