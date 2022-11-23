#include "beautySdkDemo.h"
#include "ui_BeautySdkDemo.h"
#include <qslider.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <map>
#include <MyGlView.h>

BEAUTY_PARAM_NAME_TYPE gParam[] = {
    BEAUTY_PARAM_NAME_BUFFING, BEAUTY_PARAM_NAME_SHARPNEN, BEAUTY_PARAM_NAME_NEWWHITE,
    BEAUTY_PARAM_NAME_FILTER_INSTENSITY, BEAUTY_PARAM_NAME_WHITE, BEAUTY_PARAM_NAME_RUDDY,
    FACEWARP_PARAM_NAME_THINFACE, FACEWARP_PARAM_NAME_ENLARGEEYE, FACEWARP_PARAM_NAME_SHRINKNOSE,
    BEAUTY_PARAM_NAME_END
};
QString gParamName[] = {
                        QStringLiteral("磨皮"), QStringLiteral("锐化"), QStringLiteral("新美白"),
                        QStringLiteral("滤镜"), QStringLiteral("美白"), QStringLiteral("红润"),
                        QStringLiteral("廋脸"), QStringLiteral("大眼"), QStringLiteral("窄鼻"),
};
const int gDefaultValue[] = {
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0,
};

const char* gFilterParams[] = {
    "baitao.png", "boshidun.png", "fanchase.png", "feiying.png",
    "fenxia.png", "fugu.png", "heibai.png", "huaijiu.png",
    "huayan.png", "huidiao.png", "huiyi.png", "jizhou.png",
    "juziqishui.png", "lengdan.png", "meiwei.png", "mitaowulong.png",
    "naixing.png", "naiyou.png", "naiyoumitao.png", "niunai.png",
    "nuanchun.png", "nuanshi.png", "nuanyang.png", "pailide.png",
    "qiangwei.png", "qianxing.png", "qingning.png", "qingxi.png",
    "rixi.png", "riza.png", "ruddy512.png", "senxi.png",
    "shaonv.png", "shenyeshitang.png", "shuiguang.png", "shuiwu.png",
    "suyan.png", "tianmei.png", "white512.png", "xiari.png",
    "xinxian.png", "yanxi.png", "youhua1.png", "youhua2.png",
    "zhaohe.png", "zhenzhu.png", "zhigan.png", "zhongxiameng.png",
    NULL
};

std::map<QSlider*, BEAUTY_PARAM_NAME_TYPE> gSliders;


BeautySdkDemo::BeautySdkDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BeautySdkDemo)
{
    //setWindowFlag(Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    ui->setupUi(this);

    mFlipVert=false;
    mFlipHoriz=false;

    QLabel* label2 = new QLabel(this);
    label2->setText(QStringLiteral("滤镜类型："));
    ui->frame->layout()->addWidget(label2);

    QComboBox* combobox = new QComboBox();
    for (int i = 0;; i++)
    {
        if (gFilterParams[i] == NULL) break;
        combobox->addItem(gFilterParams[i]);
    }
    ui->frame->layout()->addWidget(combobox);

    //connect(combobox, &QComboBox::currentIndexChanged, this, &BeautySdkDemo::on_combobox_valueChanged);


    connect(combobox, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), this, &BeautySdkDemo::on_combobox_valueChanged);
    //connect(combobox, SIGNAL(currentIndexChanged(QString&)), this, SLOT(on_combobox_valueChanged(QString&)));

    for (int i = 0;; i++)
    {
        if (gParam[i] == BEAUTY_PARAM_NAME_END) break;

        QLabel* label = new QLabel(this);
        label->setText(gParamName[i]);
        ui->frame->layout()->addWidget(label);

        QSlider* slider = new QSlider(this);
        slider->setMaximum(100);
        slider->setMinimum(0);
        slider->setOrientation(Qt::Orientation::Horizontal);
        slider->setValue(gDefaultValue[i]);
        ui->frame->layout()->addWidget(slider);
        connect(slider, &QSlider::valueChanged, this, &BeautySdkDemo::on_slide_valueChanged);

        gSliders[slider] = gParam[i];
        
        if(gDefaultValue[i] >=0) ui->myGlView->setParam(gSliders[slider], gDefaultValue[i]);

    }
    //ui->openCVviewer->setParam(gSliders[slider], 0);

    ui->myGlView->setParam(BEAUTY_PARAM_NAME_FILTER, "baitao.png");
    if (ui->myGlView->getBeautyLicenseStatus() == 0)
    {
        setWindowTitle(QStringLiteral("美颜Demo"));
    }
    else
    {
        setWindowTitle(QStringLiteral("美颜Demo（License不可用）"));
    }
}

void BeautySdkDemo::on_slide_valueChanged(int value)
{
    QSlider* slider = qobject_cast<QSlider*>(sender());
    if (gSliders.count(slider) > 0)
    {
        ui->myGlView->setParam(gSliders[slider], value);
    }
}

void BeautySdkDemo::on_combobox_valueChanged(const QString& value)
{
    ui->myGlView->setParam(BEAUTY_PARAM_NAME_FILTER, value.toStdString());
}

BeautySdkDemo::~BeautySdkDemo()
{
    if (parent())
    {
        //((QMainWindow*)parent())->show();
    }
    delete ui;
}

void BeautySdkDemo::on_actionStart_triggered()
{
    if( !mCapture.isOpened() )
        if( !mCapture.open( 0 ) )
            return;

    startTimer(0);
}

void BeautySdkDemo::timerEvent(QTimerEvent *event)
{
    cv::Mat image;
    mCapture >> image;

    if( mFlipVert && mFlipHoriz )
        cv::flip( image,image, -1);
    else if( mFlipVert )
        cv::flip( image,image, 0);
    else if( mFlipHoriz )
        cv::flip( image,image, 1);


    // Do what you want with the image :-)

    // Show the image
    ui->myGlView->showImage( image );
}

void BeautySdkDemo::on_actionVertical_Flip_triggered(bool checked)
{
    mFlipVert = checked;
}

void BeautySdkDemo::on_action_Horizontal_Mirror_triggered(bool checked)
{
    mFlipHoriz = checked;
}
