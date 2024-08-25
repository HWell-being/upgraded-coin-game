#include "mycoin.h"
#include <QDebug>

mycoin::mycoin(QString coin_path)
{
    QPixmap pix;
    bool ret = pix.load(coin_path);

    if(!ret){
        QString str = QString("图片加载的路径是: %1").arg(coin_path);
        qDebug() << str;
    }

    this->setFixedSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //创建定时器
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    //监听定时器timer1
    connect(this->timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString change = QString(":/res/Coin000%1.png").arg(this->min++);
        bool ret = pix.load(change);

        if(!ret){
            QString str = QString("图片加载的路径是: %1").arg(coin_path);
            qDebug() << str;
        }

        this->setFixedSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min >this->max)
        {
            this->min = 1;
            this->timer1->stop();
            isAnimation = false;


        }
    });

    //监听定时器timer2
    connect(this->timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString change = QString(":/res/Coin000%1.png").arg(this->max--);
        bool ret = pix.load(change);

        if(!ret){
            QString str = QString("图片加载的路径是: %1").arg(coin_path);
            qDebug() << str;
        }

        this->setFixedSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min)
        {
            this->max = 8;
            this->timer2->stop();
            isAnimation = false;

        }
    });
}

//点击金币改变金币的标志
void mycoin::changeFlag()
{
    if(this->flag)
    {
        this->timer1->start(30);
        this->flag = false;
    }
    else
    {
        this->timer2->start(30);
        this->flag = true;
    }
    isAnimation = true;
}

void mycoin::mousePressEvent(QMouseEvent *e)
{
    //做动画期间禁用点击

    if (this->isAnimation || this->sucess == true)
    {
        return;

    }
    else
    {
        QPushButton::mousePressEvent(e);
    }

}
