#include "block.h"

Block::Block(QColor color, QPoint origin)
{
    mColor = color;
    mOrigin = origin;

    xTranslate = 0;
    yTranslate = 0;
    updateOrigin();
}

Block::~Block(){
}

void Block::displayBlock(){

    glPushMatrix();

    // Use currOrigin ?
    glTranslated(xTranslate,yTranslate,0);

    glBegin(GL_QUADS);
    glColor3f((float)mColor.redF(), (float)mColor.greenF(), (float)mColor.blueF());

    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y(),0);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y(),0);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y()+BLOCK_DIM,0);
    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y()+BLOCK_DIM,0);

    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y(),1);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y(),1);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y()+BLOCK_DIM,1);
    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y()+BLOCK_DIM,1);

    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y(),1);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y(),1);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y(),0);
    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y(),0);

    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y()+BLOCK_DIM,0);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y()+BLOCK_DIM,0);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y()+BLOCK_DIM,1);
    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y()+BLOCK_DIM,1);

    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y(),1);
    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y(),0);
    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y()+BLOCK_DIM,1);
    glVertex3i(SPAWN.x()+mOrigin.x(),SPAWN.y()+mOrigin.y()+BLOCK_DIM,0);

    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y(),0);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y(),1);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y()+BLOCK_DIM,0);
    glVertex3i(SPAWN.x()+mOrigin.x()+BLOCK_DIM,SPAWN.y()+mOrigin.y()+BLOCK_DIM,1);


    glEnd();
    glPopMatrix();
    updateOrigin();
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

void Block::rotate(){
    setOrigin(QPoint(-mOrigin.y(), mOrigin.x()));
}

void Block::setOrigin(QPoint p){
    mOrigin = p;
}

void Block::updateOrigin(){
    currOrigin = QPoint(SPAWN.x()+mOrigin.x()+xTranslate, SPAWN.y()+mOrigin.y()+yTranslate);
}
