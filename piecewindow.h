#ifndef PIECEWINDOW_H
#define PIECEWINDOW_H

#include "tetrispiece.h"
#include <GL/glu.h>
#include <QGLWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>

class PieceWindow : public QGLWidget
{
protected:
    // GL METHODS
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

public:
    PieceWindow(QWidget *parent, TetrisPiece piece);
    ~PieceWindow();
    void setPiece(TetrisPiece p) { mPiece = p; }

private:
    TetrisPiece mPiece;
};

#endif // PIECEWINDOW_H
