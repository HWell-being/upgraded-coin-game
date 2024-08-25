#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <mycoin.h>
#include <countdown.h>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);   //有参构造，参数代表当前选择的等级

    int levelIndex;     //成员函数，记录当前关卡号

    //重写绘图事件
    void paintEvent(QPaintEvent * );

    //二维数组  作用是初始化关卡
    int gameArray[4][4];

    //维护金币的二维数组
    mycoin * coinbtn[4][4];

    //判断是否胜利
    bool isWin = true;

    countdown* countdownTimer;  // 添加倒计时模块的成员变量

    void onTimeUp();
signals:
    //点击返回按钮的信号
    void ChooseSceneBack();



};

#endif // PLAYSCENE_H
