#ifndef WEBCAM_H
#define WEBCAM_H

#include "opencv2/opencv.hpp"
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "tetrispiece.h"

using namespace cv;

//enum MOVE { LEFT, RIGHT, ROTATE, DROP, NOTHING };

class WebCam : public QWidget
{
    Q_OBJECT

public:
    explicit WebCam(QWidget *parent);//, int width, int height);
    ~WebCam();
    int getMove() { return mMove; }

private:
    //Ui::WebCam *ui;
    VideoCapture * webCam_;
    // Timer d'animation
    QTimer m_AnimationTimer;
    CascadeClassifier face_cascade_;
    QLabel *mLabel;
    int mMove;

signals:
    void signalMove();//{ return mMove; }
};

#endif // WEBCAM_H
