#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include <QColor>
#include <vector>
#include "block.h"

using namespace std;

// GLOBAL CONSTANTS
int const PIECE_SIZE = 4;
enum TetrisMouvement { LEFT, RIGHT, ROTATE, DROP , SPAWN, NOTHING};
enum TetrisShape { NoShape, ZShape, SShape, LineShape, TShape, SquareShape,
                   LShape, MirroredLShape };

/*
 * Class TetrisPiece : Désigne un objet qui contiendra tous les blocks pour former un tetriminos.
 */

class TetrisPiece
{

public:
    TetrisPiece();
    TetrisPiece(TetrisShape shape, QColor color, vector<QPoint> origins);
    virtual ~TetrisPiece();

    //Method : Permet de créer une pièce
    void createPiece();
    //Method : Permet d'afficher chaque block de la pièce
    void display();
    //Method : Permet de modifier la position des blocks de la pièce en fonction du mouvement reçu
    void onWebcamEvent(int direction);
    vector<Block*> getBlocks(){return mPiece;}
    vector<QPoint> getOrigins(){return mOrigins;}

private:
    TetrisShape mShape;
    vector<Block*> mPiece;
    vector<QPoint> mOrigins;
    QColor mColor;
};

#endif // TETRISPIECE_H
