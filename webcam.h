#ifndef WEBCAM_H
#define WEBCAM_H

#include "opencv2/opencv.hpp"
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "tetrispiece.h"

using namespace cv;

class WebCam : public QWidget
{
    Q_OBJECT

public:
    explicit WebCam(QWidget *parent);
    ~WebCam();

    int getMove() { return mMove; }

private:
    VideoCapture * webCam_;
    QTimer m_AnimationTimer;
    CascadeClassifier face_cascade_;
    QLabel *mLabel;
    int mMove;

signals:
    void signalMove();
};

#endif // WEBCAM_H
