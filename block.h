#ifndef BLOCK_H
#define BLOCK_H

#include <GL/glu.h>
#include <QColor>
#include <QPoint>

/*
 * Class Block : Définie l'object block formant un tetriminos, sa position et ses déplacement
 */

class Block
{
public:
    Block(QColor color, QPoint origin);
    virtual ~Block();

    // Method : Dessin du block en fonction de sa position
    void displayBlock();
    // Method : Modifie la position du block selon l'axe y
    void drop();
    // Method : Modifie la position du block selon l'axe x (négatif)
    void goingLeft();
    // Method : Modifie la position du block selon l'axe x (positif)
    void goingRight();
    // Method : Modifie les coordonnées du block pour la rotation (appelle setOrigin)
    void rotate();
    // Method : Modifie le point d'origine pour avoir la rotation
    void setOrigin(QPoint p);
    // Method : Met à jour les coordonnées de la pièce (currOrigin)
    void updateOrigin();

    QPoint getOrigin() { return mOrigin; }
    int getXTranslate() { return xTranslate; }
    void setXTranslate(int X) { xTranslate = X; }
    int getYTranslate() { return yTranslate; }
    void setYTranslate(int Y) { yTranslate = Y; }
    QPoint getCurrOrigin() { return currOrigin; }
    void setColor(QColor color) { mColor = color; }


private:
    // Constante : Taille d'un block
    int const BLOCK_DIM = 1;
    // Constante : Point d'apparition du block
    const QPoint SPAWN = QPoint(5,20);

    // Couleur
    QColor mColor;
    // Point d'origine de la création du block
    QPoint mOrigin;
    // Position actuelle
    QPoint currOrigin;
    // Déplacement vertical & horizontal
    int xTranslate, yTranslate;
};

#endif // BLOCK_H
