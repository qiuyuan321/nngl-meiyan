#ifndef MAINWINDOWDEMO_H
#define MAINWINDOWDEMO_H

#include <QMainWindow>
class BeautySdkDemo;

namespace Ui {
class MainWindowDemo;
}

class MainWindowDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowDemo(QWidget *parent = 0);
    ~MainWindowDemo();

public slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindowDemo *ui;
    BeautySdkDemo* _beautyDemo;
};

#endif // MAINWINDOWDEMO_H
