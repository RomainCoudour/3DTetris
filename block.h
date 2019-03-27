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

private:
    int const BLOCK_DIM = 1;

    QColor mColor;
    QPoint mOrigin;
    int xTranslate, yTranslate;
    int angle;
};

#endif // BLOCK_H
