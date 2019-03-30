#ifndef BLOCK_H
#define BLOCK_H

#include <GL/glu.h>
#include <QColor>
#include <QPoint>


class Block
{
public:
    Block(QColor color, QPoint origin);
    virtual ~Block();

    //Methods
    void displayBlock();
    void drop();
    void goingLeft();
    void goingRight();
    void rotate();
    void updateOrigin();

    QPoint getOrigine() { return mOrigin; }
    void setOrigine(QPoint p);
    int getXTranslate() { return xTranslate; }
    void setXTranslate(int X) { xTranslate = X; }
    int getYTranslate() { return yTranslate; }
    void setYTranslate(int Y) { yTranslate = Y; }
    QPoint getCurrOrigin() { return currOrigin; }
    QPoint getSPAWN() { return SPAWN; }


private:
    int const BLOCK_DIM = 1;
    const QPoint SPAWN = QPoint(5,20);

    QColor mColor;
    QPoint mOrigin;
    QPoint currOrigin;
    int xTranslate, yTranslate;
    int angle;
};

#endif // BLOCK_H
