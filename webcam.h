#ifndef WEBCAM_H
#define WEBCAM_H

#include "opencv2/opencv.hpp"
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include "tetrispiece.h"

using namespace cv;

/*
 * Class WebCam : Désigne un objet de type QWidget qui gèrera la webcam via un label.
 * WebCam émettra également des signaux pour donner les mouvements aux tetriminos.
 */

class WebCam : public QWidget
{
    Q_OBJECT

public:
    explicit WebCam(QWidget *parent);
    ~WebCam();

private:
    VideoCapture * webCam_;
    QTimer m_AnimationTimer; //timer de rafraichissement de la webcam
    CascadeClassifier face_cascade_;
    QLabel *mLabel; //Label qui contiendra la webcam

signals:
    // Signaux commandant les mouvements des pièces en fonction de la position des mains
    void moveDrop();
    void moveRight();
    void moveLeft();
    void moveRotate();
    void stopMove();
};

#endif // WEBCAM_H
