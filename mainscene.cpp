#include "mainscene.h"
#include "ui_mainscene.h"
#include "QPainter"
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置音效
    QSound * mainsound = new QSound(":/res/TapButtonSound.wav",this);



    //点击退出游戏
    connect(ui->actionquit,&QAction::triggered,this,[=](){
        this->close();
    });

    //设置固定的尺寸
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("翻金币游戏");

    //设置标题的图标
    QIcon icon_window(":/res/Coin0001.png");
    this->setWindowIcon(icon_window);

    //创建第二个选关场景
    this->chooselevel = new chooseLevelSence;


    //创建开始按钮
    mypushbutton * startBtn = new mypushbutton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.7);

    connect(startBtn,&mypushbutton::clicked,[=](){

        //播放音效
        mainsound->play();

        //qDebug() << "进入到选关卡";

        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入第二个场景
        QTimer::singleShot(500,this,[=](){
            this->chooselevel->setGeometry(this->geometry());
            this->chooselevel->show();
            this->hide();
        });
    });

    connect(this->chooselevel,&chooseLevelSence::ChooseSceneBack,[=](){
        this->chooselevel->hide();
        this->setGeometry(this->chooselevel->geometry());
        this->show();
    });



}

MainScene::~MainScene()
{
    delete ui;
}

//重写绘图事件
void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家
    QPainter painter(this);

    //创建Pixmap对象
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    //绘制图像
     painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
     pix.load(":/res/Title.png");

    //缩放图片
     pix = pix.scaled(pix.width()*0.6,pix.height()*0.6);

    //绘制图像
     painter.drawPixmap(10,30,pix);



}
