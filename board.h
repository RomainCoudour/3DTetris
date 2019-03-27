#ifndef BOARD_H
#define BOARD_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <vector>
#include "tetrisfactory.h"

using namespace std;


class Board : public QGLWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = 0);
    ~Board();

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

private:
    // Liste des pièces
    vector<TetrisPiece*> mPieces;


};

#endif // BOARD_H
