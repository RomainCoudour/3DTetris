#ifndef PIECEWINDOW_H
#define PIECEWINDOW_H

#include "tetrispiece.h"
#include <GL/glu.h>
#include <QGLWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>

class PieceWindow : public QGLWidget
{
protected:
    // GL METHODS
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

public:
    PieceWindow(TetrisPiece piece);
    void setPiece(TetrisPiece p) { mPiece = p; }
    void keyPressEvent(QKeyEvent * event);

private:
    TetrisPiece mPiece;
    float zoom;
};

#endif // PIECEWINDOW_H
