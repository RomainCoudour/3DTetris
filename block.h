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

private:
    int const BLOCK_DIM = 1;

    bool translate;
    QColor mColor;
    QPoint mOrigin;
    int xTranslate, yTranslate;
};

#endif // BLOCK_H
