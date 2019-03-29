#include "block.h"

Block::Block(QColor color, QPoint origin)
{
    mColor = color;
    mOrigin = origin;

    xTranslate = 0;
    yTranslate = 0;
    angle = 0;

}

Block::~Block(){
}

void Block::displayBlock(){

    // Dims : 1x1x1
    // Raw : glVertex3i(mOrigin.x(),mOrigin.y(),0);
    // /!\ 2D : (x,y) ---> 3D : (y,-z)
    glPushMatrix();
    glTranslated(xTranslate,yTranslate,0);

    glBegin(GL_QUADS);
    glColor3f((float)mColor.redF(), (float)mColor.greenF(), (float)mColor.blueF());

    glVertex3i(mOrigin.x(),mOrigin.y(),0);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y(),0);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y()+BLOCK_DIM,0);
    glVertex3i(mOrigin.x(),mOrigin.y()+BLOCK_DIM,0);

    glVertex3i(mOrigin.x(),mOrigin.y(),1);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y(),1);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y()+BLOCK_DIM,1);
    glVertex3i(mOrigin.x(),mOrigin.y()+BLOCK_DIM,1);

    glVertex3i(mOrigin.x(),mOrigin.y(),1);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y(),1);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y(),0);
    glVertex3i(mOrigin.x(),mOrigin.y(),0);

    glVertex3i(mOrigin.x(),mOrigin.y()+BLOCK_DIM,0);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y()+BLOCK_DIM,0);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y()+BLOCK_DIM,1);
    glVertex3i(mOrigin.x(),mOrigin.y()+BLOCK_DIM,1);

    glVertex3i(mOrigin.x(),mOrigin.y(),1);
    glVertex3i(mOrigin.x(),mOrigin.y(),0);
    glVertex3i(mOrigin.x(),mOrigin.y()+BLOCK_DIM,1);
    glVertex3i(mOrigin.x(),mOrigin.y()+BLOCK_DIM,0);

    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y(),0);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y(),1);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y()+BLOCK_DIM,0);
    glVertex3i(mOrigin.x()+BLOCK_DIM,mOrigin.y()+BLOCK_DIM,1);


    glEnd();
    glPopMatrix();
}

void Block::drop(){
    yTranslate--;
}

void Block::goingLeft(){
    xTranslate--;
}

void Block::goingRight(){
    xTranslate++;
}

void Block::setOrigine(QPoint p){
    mOrigin = p;
}
