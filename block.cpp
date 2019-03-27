#include "block.h"

Block::Block(QColor color, QPoint origin)
{
    mColor = color;
    mOrigin = origin;
    translate = false;

    xTranslate = 0;
    yTranslate = 0;

}

Block::~Block(){
}

void Block::displayBlock(){

    // Dims : 1x1x1
    // Raw : glVertex3i(mOrigin.x(),mOrigin.y(),0);
    // /!\ 2D : (x,y) ---> 3D : (y,-z)
    glPushMatrix();
    if(translate){
        translate = !translate;
        yTranslate--;
        glTranslated(xTranslate,yTranslate,0);
    }

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
    translate = true;
}
