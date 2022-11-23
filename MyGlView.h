#ifndef CQTOPENCVVIEWERGL_H
#define CQTOPENCVVIEWERGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <opencv2/opencv.hpp>
#include <mutex>
#include <CBeautySdk.h>

class MyGlView : public QOpenGLWidget, protected QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit MyGlView(QWidget *parent = 0);
    ~MyGlView();

signals:
    void    imageSizeChanged( int outW, int outH ); /// Used to resize the image outside the widget

public slots:
    bool    showImage(const cv::Mat& image); /// Used to set the image to be viewed
    void    setParam(int paramName, int value);
    void    setParam(int paramName, std::string value);
    int     getBeautyLicenseStatus();

protected:
    void 	initializeGL(); /// OpenGL initialization
    void 	paintGL(); /// OpenGL Rendering
    void 	resizeGL(int width, int height);        /// Widget Resize Event

    void        updateScene();
    void        renderImage();

private:
    cv::Mat     mOrigImage;             /// original OpenCV image to be shown

    QColor      mBgColor;		/// Background color

    float       mImgRatio;             /// height/width ratio

    int mRenderWidth;
    int mRenderHeight;
    int mRenderPosX;
    int mRenderPosY;

    void recalculatePosition();

	std::mutex drawMutex;

    void* _beautySdk;
};

#endif // CQTOPENCVVIEWERGL_H
