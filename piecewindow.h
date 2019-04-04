#ifndef PIECEWINDOW_H
#define PIECEWINDOW_H

#include "tetrispiece.h"
#include <GL/glu.h>
#include <QGLWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>

/*
 * Class PieceWindow : Désigne le GL widget qui gerera l'affichage de la pièce suivante
 */

class PieceWindow : public QGLWidget
{

public:
    PieceWindow(QWidget *parent, TetrisPiece piece);
    ~PieceWindow();
    void setPiece(TetrisPiece p) { mPiece = p; }

private:
    // GL METHODS
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    TetrisPiece mPiece;
};

#endif // PIECEWINDOW_H
