#include "webcam.h"
#include <QDebug>

using namespace cv;
using namespace std;

WebCam::WebCam(QWidget *parent)//, int width, int height)
    : QWidget(parent)
{
    //this->setFixedSize(width, height);
    this->setFixedSize(600,400);
    mLabel = new QLabel(this);
    mLabel->move(0,0);
    webCam_=new VideoCapture(0);
    webCam_->set(CV_CAP_PROP_FRAME_WIDTH,600);
    webCam_->set(CV_CAP_PROP_FRAME_HEIGHT,425);
    mLabel->setFixedSize(webCam_->get(CV_CAP_PROP_FRAME_WIDTH), webCam_->get(CV_CAP_PROP_FRAME_HEIGHT));
    face_cascade_.load( "../TestWebCamQt - Copie/haarcascade/fist_v3.xml" );
    mMove = NOTHING;

    // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        if (webCam_->isOpened()) {
            Mat image, frame, frame_gray;
            std::vector<Rect> faces;
            // Get frame
            webCam_->operator >>(frame);
            if (webCam_->read(image)) {   // Capture a frame
                // Flip to get a mirror effect
                flip(image,image,1);
                flip(frame,frame,1);
                // Invert Blue and Red color channels
                cvtColor(image,image,CV_BGR2RGB);
                // Convert to gray
                cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
                //-- Detect faces
                face_cascade_.detectMultiScale( frame_gray, faces, 1.1, 4, 0|CV_HAAR_SCALE_IMAGE, Size(60, 60) );
                if (faces.size()==2)
                {
                    QPoint leftHand, rightHand;
                    // Draw green rectangle
                    for (int i=0;i<(int)faces.size();i++){
                        rectangle(image,faces[i],Scalar(0,255,0),2);
                    }
                    leftHand = QPoint(faces[0].x,faces[0].y);
                    rightHand = QPoint(faces[1].x,faces[1].y);
                    if(leftHand.x() > rightHand.x()){
                        leftHand = QPoint(faces[1].x,faces[1].y);
                        rightHand = QPoint(faces[0].x,faces[0].y);
                    }

                    if(rightHand.y()+100< leftHand.y()) //LEFT
                        mMove = LEFT;
                    else if (rightHand.y()> leftHand.y()+100 ) //RIGHT
                        mMove = RIGHT;
                    else if(rightHand.x()<leftHand.x()+200) //ROTATE
                        mMove = ROTATE;
                    else if(rightHand.y() > webCam_->get(CV_CAP_PROP_FRAME_HEIGHT)/2+50 && leftHand.y() > webCam_->get(CV_CAP_PROP_FRAME_HEIGHT)/2+50) //DROP
                        mMove = DROP;
                    else //NOTHING;
                        mMove = NOTHING;
                }
                else
                    mMove = NOTHING;
                // Convert to Qt image
                QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
                // Display on label
                mLabel->setPixmap(QPixmap::fromImage(img));
                emit signalMove();
            }
        }
    });

    m_AnimationTimer.setInterval(100);
    m_AnimationTimer.start();
}

WebCam::~WebCam()
{
    delete webCam_;
}
