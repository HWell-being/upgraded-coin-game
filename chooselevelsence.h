#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H

#include <QMainWindow>
#include "playscene.h"
class chooseLevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelSence(QWidget *parent = nullptr);

    //绘图事件
    void paintEvent(QPaintEvent* );

    //维护第三个场景的指针
    PlayScene * pyscene = NULL;


signals:
    //点击返回按钮的信号
    void ChooseSceneBack();

};

#endif // CHOOSELEVELSENCE_H
