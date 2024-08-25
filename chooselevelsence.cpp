#include "chooselevelsence.h"
#include <QMenuBar>
#include "QPainter"
#include "mypushbutton.h"
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QSound>

chooseLevelSence::chooseLevelSence(QWidget *parent) : QMainWindow(parent)
{
    //准备音效
    QSound * chooosesound = new QSound(":/res/TapButtonSound.wav",this);
    QSound * backsound = new QSound(":/res/BackButtonSound.wav",this);

    //设置固定的尺寸
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("选择关卡");

    //设置标题的图标
    QIcon icon_window(":/res/Coin0001.png");
    this->setWindowIcon(icon_window);

    //创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);

    //创建菜单
    QMenu* start = bar->addMenu("开始");

    //创建菜单项
    QAction * quitaction = start->addAction("退出");

    //监听退出
    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });


    //创建返回按钮
    mypushbutton * backBtn = new mypushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());



    connect(backBtn,&mypushbutton::clicked,[=](){

        //播放音效
        backsound->play();

        //qDebug() << "返回第一个场景的信号";

        //延时返回主场景
        QTimer::singleShot(200,this,[=](){
            //发送一个自定义信号
            emit this->ChooseSceneBack();
        });

    });

    //创建20个具体关卡按钮
    for(int i = 0 ; i<20; i++)
    {
        mypushbutton * choselevel_btn = new mypushbutton(":/res/LevelIcon.png");


        choselevel_btn->setParent(this);
        choselevel_btn->move(30+70*(i%4),120+80*(i/4));
//        choselevel_btn->setText(QString::number(i+1));    这类的显示有问题
        //显示各个图标上的关卡等级
        QLabel * level = new QLabel;
        level->setParent(this);
        level->setNum(i+1);
        QFont font("华文琥珀",12);
        level->setFont(font);
        level->move(30+70*(i%4),120+80*(i/4));

        //设置Label的尺寸
        level->setFixedSize(choselevel_btn->width(),choselevel_btn->height());
        //设置对齐方式
        level->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置属性 鼠标穿透属性
        level->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(choselevel_btn,&mypushbutton::clicked,[=](){

            //播放音效
            chooosesound->play();

           //qDebug() <<"您选择的是第" << i+1 << "关";
            this->pyscene = new PlayScene(i+1);
            this->pyscene->setGeometry(this->geometry());
            this->pyscene->show();
            this->hide();

            //返回到选择关卡场景
            connect(this->pyscene,&PlayScene::ChooseSceneBack,[=](){
                this->setGeometry(this->pyscene->geometry());
                this->pyscene->hide();
                this->show();

                delete this->pyscene;
                this->pyscene = NULL;
        });
    });

}
}
void chooseLevelSence::paintEvent(QPaintEvent *)
{
    //创建画家
    QPainter painter(this);

    //创建Pixmap对象
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");

    //绘制图像
     painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
     pix.load(":/res/Title.png");

    //缩放图片
     pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);

    //绘制图像
     painter.drawPixmap((this->width() - pix.width())*0.5,30,pix);

}
