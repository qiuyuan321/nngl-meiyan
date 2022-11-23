#ifndef QTGLWEBCAMDEMO_H
#define QTGLWEBCAMDEMO_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>

#include <opencv2/highgui/highgui.hpp>
#include <ui_beautySdkDemo.h>

namespace Ui {
    class BeautySdkDemo;
}

class BeautySdkDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit BeautySdkDemo(QWidget *parent = 0);
    ~BeautySdkDemo();

private slots:
    void on_actionStart_triggered();

    void on_actionVertical_Flip_triggered(bool checked);

    void on_action_Horizontal_Mirror_triggered(bool checked);

    void on_slide_valueChanged(int value);
    void on_combobox_valueChanged(const QString& value);

private:
    Ui::BeautySdkDemo* ui;

    cv::VideoCapture mCapture;

protected:
    void timerEvent(QTimerEvent *event);

private:
    bool mFlipVert;
    bool mFlipHoriz;
};

#endif // QTGLWEBCAMDEMO_H
