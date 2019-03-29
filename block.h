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
    void setOrigine(QPoint p);
    void updateOrigin();
    QPoint getOrigine() { return mOrigin; }
    int getXTranslate() { return xTranslate; }
    int getYTranslate() { return yTranslate; }
    QPoint getCurrOrigin() { return currOrigin; }


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
