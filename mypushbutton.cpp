#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

mypushbutton::mypushbutton(QWidget *parent) : QPushButton(parent)
{
}

//参数一：正常图片的路径 ，参数二：点击后图片的路径
mypushbutton::mypushbutton(QString normalImage,QString pressImage)
{
    this->normalPath = normalImage;
    this->pressPath = pressImage;

    //创建一个Pixmap
    QPixmap pix;
    bool result = pix.load(normalImage);
    if (result != true)
    {
        QString str = QString("加载图像失败,失败的路径是：%1！").arg(this->normalPath);
        qDebug() << str;

    }


    //设置按钮的固定尺寸
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));





}

//向下跳跃
void mypushbutton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this , "geometry");

    //设置动画间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);




}

void mypushbutton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this , "geometry");

    //设置动画间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}

void mypushbutton::mousePressEvent(QMouseEvent *e)
{
    //按下的路径不为空，说明要切换图片
    if(this->pressPath != "")
    {
        //创建一个Pixmap
        QPixmap pix;
        bool result = pix.load(pressPath);
        if (result != true)
        {
            QString str = QString("加载图像失败,失败的路径是：%1！").arg(this->pressPath);
            qDebug() << str;

        }


        //设置按钮的固定尺寸
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));


    }
    //把其他事情交给父类处理
    QPushButton::mousePressEvent(e);

}

void mypushbutton::mouseReleaseEvent(QMouseEvent *e)
{
    //按下的路径不为空，说明要还原正常显示的图片
    if(this->pressPath != "")
    {
        //创建一个Pixmap
        QPixmap pix;
        bool result = pix.load(normalPath);
        if (result != true)
        {
            QString str = QString("加载图像失败,失败的路径是：%1！").arg(this->normalPath);
            qDebug() << str;

        }


        //设置按钮的固定尺寸
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));


    }
    //把其他事情交给父类处理
    QPushButton::mouseReleaseEvent(e);
}



