#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mypushbutton(QWidget *parent = nullptr);

    //参数一：正常图片的路径 ，参数二：点击后图片的路径
    mypushbutton(QString normalImage,QString pressImage = "");
    QString normalPath;
    QString pressPath;

    //向下跳跃
    void zoom1();

    //向上跳跃
    void zoom2();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);


    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);





signals:

};

#endif // MYPUSHBUTTON_H
