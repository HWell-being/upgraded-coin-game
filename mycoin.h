#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class mycoin : public QPushButton
{
    Q_OBJECT
public:
    mycoin(QString coin_path);

    int X_pos;      //X坐标
    int Y_pos;      //Y坐标
    bool flag;      //正反标志

    void changeFlag();
    QTimer * timer1;
    QTimer * timer2;
    int min = 1;
    int max = 8;

    //翻转动画的标志
    bool isAnimation = false;

    //重写鼠标的按下事件
    void mousePressEvent(QMouseEvent * e);

    //胜利标志位
    bool sucess = false ;


signals:

};

#endif // MYCOIN_H
