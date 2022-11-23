#include "mainwindowdemo.h"
#include "ui_mainwindowdemo.h"
#include "BeautySdkDemo.h"

MainWindowDemo::MainWindowDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowDemo)
{
    ui->setupUi(this);
    _beautyDemo = NULL;
}

MainWindowDemo::~MainWindowDemo()
{
    delete ui;
}

void MainWindowDemo::on_pushButton_clicked()
{
    if (_beautyDemo != NULL)
    {
        delete _beautyDemo;
        _beautyDemo = NULL;
    }

    if (_beautyDemo == NULL)
    {
        _beautyDemo = new BeautySdkDemo(this);
        _beautyDemo->show();
    }
}
