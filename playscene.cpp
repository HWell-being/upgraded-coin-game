#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <mycoin.h>
#include <dataconfig.h>
#include <QPropertyAnimation>
#include <QSound>
#include <countdown.h>
#include <QMessageBox>

PlayScene::PlayScene(int index)
{
    //准备音效
    QSound * backsound = new QSound(":/res/BackButtonSound.wav",this);
    QSound * sucesssound = new QSound(":/res/LevelWinSound.wav",this);
    QSound * coinsound = new QSound(":/res/ConFlipSound.wav",this);

    this->levelIndex = index;
    qDebug() <<"进入的是第" << this->levelIndex << "关";

    //设置固定的尺寸
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("翻金币");

    //设置标题的图标
    QIcon icon_window(":/res/Coin0001.png");
    this->setWindowIcon(icon_window);

    //创建菜单栏
    QMenuBar * bar = menuBar();
    QMenu * start = bar->addMenu("开始");
    QAction * exit = start->addAction("退出");

    connect(exit,&QAction::triggered,[=](){
       this->close();

    });

    //创建返回按钮
    mypushbutton * backBtn = new mypushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());



    connect(backBtn,&mypushbutton::clicked,[=](){

        backsound->play();

        //qDebug() << "返回第二个场景的信号";
        QTimer::singleShot(300,this,[=](){
            emit this->ChooseSceneBack();
        });
    });


    //显示当前关卡号
    QLabel * label_level = new QLabel(this);

    QString lv = QString("LEVLE: %1").arg(this->levelIndex);
    label_level->setText(lv);
    QFont font("微软雅黑",18);
    label_level->setFont(font);

    //设置标签大小、位置
    label_level->setGeometry(QRect(30,this->height() - 50 ,this->width() ,50));

    label_level->setAttribute(Qt::WA_TransparentForMouseEvents);

    //设置成功界面
    QLabel * win_label = new QLabel(this);
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    win_label->setGeometry(0,0,pix.width(),pix.height());
    win_label->setPixmap(pix);
    win_label->move((this->width()-pix.width())*0.5,-pix.height());



    //初始化关卡的二维数组
    dataConfig config;
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ;j++) {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }


    //创建金币的背景图片
    for(int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0; j < 4 ; j++) {
            //绘制背景图片
            QLabel * bkp = new QLabel(this);
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            bkp->setGeometry(0,0,pix.width(),pix.height());
            bkp->setPixmap(pix);
            bkp->move(57 + i * pix.width() ,200 + j* pix.height());

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1){
                str = ":/res/Coin0001.png";
            }
            else {
                str = ":/res/Coin0008.png";
            }
            mycoin * coin = new mycoin(str);
            coin->setParent(this);
            coin->move(59 + i * pix.width() ,204 + j* pix.height());

            coin->X_pos = i ;
            coin->Y_pos = j ;
            coin->flag = gameArray[i][j];

            this->coinbtn[i][j] = coin;

            //点击金币翻转
            connect(coin,&mycoin::clicked,[=](){
                //音乐播放
                coinsound->play();

                // 创建倒计时模块
                countdownTimer = new countdown(this, 60000, 1000);  // 60秒倒计时
                countdownTimer->move(10, 10);  // 设置倒计时的位置

                // 连接倒计时结束的信号到游戏结束的槽函数
                connect(countdownTimer, &countdown::timeUp, this, &PlayScene::onTimeUp);

                countdownTimer->start();  // 开始倒计时



                //禁用所有金币的点击
                for (int i = 0 ; i < 4 ; i++ ) {
                    for (int j = 0 ; j <4 ; j++ ) {

                        this->coinbtn[i][j]->sucess = true;
                    }
                }

                coin->changeFlag();

                //记录游戏的二维数字记录 ,利于后期扩展 存档读档
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0 ;

                //翻转周围金币
                if(coin->X_pos -1 >= 0 )
                {
                    this->coinbtn[coin->X_pos -1][coin->Y_pos]->changeFlag();
                    gameArray[coin->X_pos -1][coin->Y_pos] = gameArray[coin->X_pos -1][coin->Y_pos] == 0 ? 1 : 0 ;
                }

                if(coin->X_pos + 1 <= 3)
                {
                    this->coinbtn[coin->X_pos +1][coin->Y_pos]->changeFlag();
                    gameArray[coin->X_pos + 1][coin->Y_pos] = gameArray[coin->X_pos + 1][coin->Y_pos] == 0 ? 1 : 0 ;

                }

                if(coin->Y_pos -1 >= 0 )
                {
                    this->coinbtn[coin->X_pos][coin->Y_pos -1]->changeFlag();
                    gameArray[coin->X_pos][coin->Y_pos -1] = gameArray[coin->X_pos][coin->Y_pos -1] == 0 ? 1 : 0 ;
                }

                if(coin->Y_pos + 1 <= 3)
                {
                    this->coinbtn[coin->X_pos][coin->Y_pos +1]->changeFlag();
                    gameArray[coin->X_pos][coin->Y_pos +1] = gameArray[coin->X_pos][coin->Y_pos +1] == 0 ? 1 : 0 ;
                }

                //检测游戏是否胜利
                this->isWin = true;
                for (int i = 0 ; i < 4 ; i++ ) {
                    for (int j = 0 ; j <4 ; j++ ) {
                        if(this->coinbtn[i][j]->flag == false){
                            this->isWin = false;
                            break;
                        }
                    }
                }
                if(this->isWin){
                    for (int i = 0 ; i < 4 ; i++ ) {
                        for (int j = 0 ; j <4 ; j++ ) {
                            this->coinbtn[i][j]->sucess = true;

                        }
                    }

                    sucesssound->play();
                    //将胜利图片显示
                    QPropertyAnimation * animation = new QPropertyAnimation(win_label,"geometry");
                    animation->setDuration(1000);
                    animation->setStartValue(QRect(win_label->x(),win_label->y(),win_label->width(),win_label->height()));
                    animation->setEndValue(QRect(win_label->x(),win_label->y()+180,win_label->width(),win_label->height()));
                    animation->setEasingCurve(QEasingCurve::OutBounce);
                    animation->start(QAbstractAnimation::DeleteWhenStopped);



                }
                else
                {
                    //禁用所有金币的点击
                    for (int i = 0 ; i < 4 ; i++ ) {
                        for (int j = 0 ; j <4 ; j++ ) {

                            this->coinbtn[i][j]->sucess = false;
                        }
                    }

                }

            });

        }
    }



}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter  painter(this);
    //绘制背景
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}

void PlayScene::onTimeUp()
{
    QMessageBox::information(this, "Time's Up", "时间结束，游戏结束！");

}
