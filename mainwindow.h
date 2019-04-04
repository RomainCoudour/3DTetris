#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QTimer>

#include "board.h"
#include "webcam.h"

/*
 * Class MainWindow : Groupe tous les élements graphiques, gère la connection des signaux
 */
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

    // Method : Transmet input clavier à la grille jeu
    void keyPressEvent(QKeyEvent * event);
    // Method : Affichage du score après réception et traitement d'un signal
    void displayScore();

private:
    // Grille de jeu
    Board* mBoard;
    // Affichage de la pièce suivante
    PieceWindow* mPWindow;
    // Affichage du score
    QLabel* score;
    // Sauvegarde du score
    int mScore;
    // Webcam
    WebCam* cam;

public slots:
    void increaseScore();
    void resetScore();

};



#endif // MAINWINDOW_H
