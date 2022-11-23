#include "MyGlView.h"
#include <fstream>
#include <sstream>
#include <iostream>

const char* LICENSE_KEY = "IVBTeDkyPzkxET8jeHpgeng5aWptaT9jOGtuOGw5a2s+O2lpa2xsaGI4Pjk7OD5tOXh2UFN4NSgzPTM0eHpgelBTIVBTU3g5NTc3PzQueHpgeng0Ozc/YHo0ND02KT4xei4/KS56NjM5PzQpP2EzKSkvPw4zNz9gemhqaGh3a2t3aGl6a29gaW1gbmxhPyIqMyg/DjM3P2B6aGpoaXdqaHdoa3prb2BpbWBubGE+Py47MzZgeiEGeDk1Nyo7NCMGeGB6Bng7ODkGeHZ6Bng7KioGeGB6Bng0ND02Pj83NQZ4J2F4dlBTU3g+Py47MzZ4emB6eCEGeDk1Nyo7NCMGeGB6Bng7ODkGeHZ6Bng7KioGeGB6Bng0ND02Pj83NQZ4J3h2UFNTeD8iKjMoPw4zNz94emB6a2xtbGNjaWJsbHZQU1N4MykpLz8OMzc/eHpgemtsbGNoa21ibGx2UFNTeDE/I3h6YHp4LzMxKzVqam1sbzApPjEpIjc0MzUxMTg4aWx4dlBTU3g0Ozc/eHpgeng0ND02KT4xei4/KS56NjM5PzQpP3hQUydQJ1A=";

std::string readFile2(const char* filename)
{
    std::ifstream ifs(filename, std::ios::binary);
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

MyGlView::MyGlView(QWidget *parent) :
    QOpenGLWidget(parent)
{
    mBgColor = QColor::fromRgb(150, 150, 150);
    //_beautySdk = createBeautySdk(LICENSE_KEY);
    std::string licenseStr = readFile2("license.lic");
    _beautySdk = createBeautySdk(licenseStr.c_str());
	
    std::string binary = readFile2(".\\filterImage.bundle");
    createBeautyBundle(_beautySdk, "filters", binary.c_str(), binary.length());
    
}

MyGlView::~MyGlView()
{
    makeCurrent();
    destoryBeautySdk(_beautySdk);
    _beautySdk = NULL;
}

int MyGlView::getBeautyLicenseStatus()
{
    return getLicenseStatus(_beautySdk);
}

void MyGlView::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();

    float r = ((float)mBgColor.darker().red())/255.0f;
    float g = ((float)mBgColor.darker().green())/255.0f;
    float b = ((float)mBgColor.darker().blue())/255.0f;
    glClearColor(r,g,b,1.0f);
    initBeautySdk(_beautySdk);
}

void MyGlView::setParam(int paramName, int value)
{
    setBeautySdkParameter(_beautySdk, (BEAUTY_PARAM_NAME_TYPE)paramName, value / 100.0);
}

void MyGlView::setParam(int paramName, std::string value)
{
    setBeautySdkStringParameter(_beautySdk, (BEAUTY_PARAM_NAME_TYPE)paramName, value.c_str());
}

void MyGlView::resizeGL(int width, int height)
{
    makeCurrent();
    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, -height, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);

    recalculatePosition();

    emit imageSizeChanged(mRenderWidth, mRenderHeight);

    updateScene();
}

void MyGlView::updateScene()
{
    if (this->isVisible()) update();
}

void MyGlView::paintGL()
{
    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderImage();
}

void MyGlView::renderImage()
{

    drawMutex.lock();
    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT);
    if (!mOrigImage.empty())
    {
        glLoadIdentity();

        glPushMatrix();
        {

            cv::Mat scaledImage;
            cv::resize(mOrigImage, scaledImage, cv::Size(mRenderWidth, mRenderHeight));

            // ---> Centering image in draw area

            glRasterPos2i(mRenderPosX, mRenderPosY);
            //glRasterPos2i(0, 0);

            glPixelZoom(1, -1);
            //glBindFramebuffer(GL_FRAMEBUFFER, 0);
            //glBindBuffer(GL_FRAMEBUFFER, defaultFramebufferObject());

            //glDrawPixels(scaledImage.cols, scaledImage.rows, GL_RGBA, GL_UNSIGNED_BYTE, scaledImage.data);
            

            GLuint texture;
            glGenTextures(1, &texture);//创建纹理数量 ：一个  。（.h） GLuint texture[1];

            glBindTexture(GL_TEXTURE_2D, texture);//将纹理绑定到目标纹理上
            glTexImage2D(GL_TEXTURE_2D, 0, 3, scaledImage.cols, scaledImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, scaledImage.data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//滤波
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            //processTextureAndRender(_beautySdk, defaultFramebufferObject(), texture, scaledImage.cols, scaledImage.rows);
            unsigned int filteredTexture = processTexture(_beautySdk, texture, scaledImage.cols, scaledImage.rows);
            renderTexture(_beautySdk, defaultFramebufferObject(), filteredTexture);
            glDeleteTextures(1, &texture);

        }
        glPopMatrix();

        // end
        glFlush();
    }

    drawMutex.unlock();
}

void MyGlView::recalculatePosition()
{
    mImgRatio = (float)mOrigImage.cols/(float)mOrigImage.rows;

    mRenderWidth = this->size().width();
    mRenderHeight = floor(mRenderWidth / mImgRatio);

    if (mRenderHeight > this->size().height())
    {
        mRenderHeight = this->size().height();
        mRenderWidth = floor(mRenderHeight * mImgRatio);
    }

    mRenderPosX = floor((this->size().width() - mRenderWidth) / 2);
    mRenderPosY = -floor((this->size().height() - mRenderHeight) / 2);
}

bool MyGlView::showImage(const cv::Mat& image)
{
	drawMutex.lock();
    cvtColor(image, mOrigImage, cv::COLOR_BGR2RGBA);
    recalculatePosition();
    updateScene();
	drawMutex.unlock();
    return true;
}
