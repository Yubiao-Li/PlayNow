#include "playwidget.h"

PlayWidget::PlayWidget(QWidget *parent) : QWidget(parent)
{
    initAll(parent);
}

void PlayWidget::initAll(QWidget *parent)
{
    setParent(parent);
    PaintScene();
    m_pressFlag=0;
}

void PlayWidget::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        qDebug()<<"press";
        switch(event->key())
        {

        case 16777234:      //左
            track[1]->show();
            for(int i=0;i<key_num;i++)
            {
                if(float_key[i]!=NULL&&float_key[i]->key=='K'&&float_key[i]->y>=750)
                {
                    if(float_key[i]->y>=785)
                    {
                        score+=(404+combo);
                        miss->hide();
                        great->hide();
                        perfect->show();
                        perfect_num+=1;
                        perfect->start();
                    }
                    else
                    {
                        score+=(202+combo);
                        miss->hide();
                        perfect->hide();
                        great->show();
                        great_num+=1;
                        great->start();
                    }
                    combo+=1;
                    combo_widget->setcombo();
                    setscore(this);
                    if(combo_widget->isVisible()==false)
                        combo_widget->show();
                    hit[1]->show();
                    disconnect(myTimer,&QTimer::timeout,float_key[i],&FloatNote::dealTimeOut);
                    delete float_key[i];
                    float_key[i]=NULL;
                    break;
                }
            }
            break;
        case 16777235:      //上
            track[2]->show();
            for(int i=0;i<key_num;i++)
            {
                if(float_key[i]!=NULL&&float_key[i]->key=='H'&&float_key[i]->y>=750)
                {
                    if(float_key[i]->y>=785)
                    {
                        score+=(404+combo);
                        miss->hide();
                        great->hide();
                        perfect->show();
                        perfect_num+=1;
                        perfect->start();
                    }
                    else
                    {
                        score+=(202+combo);
                        miss->hide();
                        perfect->hide();
                        great->show();
                        great_num+=1;
                        great->start();
                    }
                    combo+=1;
                    combo_widget->setcombo();
                    setscore(this);
                    if(combo_widget->isVisible()==false)
                        combo_widget->show();
                    hit[2]->show();
                    disconnect(myTimer,&QTimer::timeout,float_key[i],&FloatNote::dealTimeOut);
                    delete float_key[i];
                    float_key[i]=NULL;
                    break;
                }
            }
            break;
        case 32:            //空格
            track[0]->show();
            for(int i=0;i<key_num;i++)
            {
                if(float_key[i]!=NULL&&float_key[i]->key==' '&&float_key[i]->y>=750)
                {
                    if(float_key[i]->y>=785)
                    {
                        score+=(404+combo);
                        miss->hide();
                        great->hide();
                        perfect->show();
                        perfect_num+=1;
                        perfect->start();
                    }
                    else
                    {
                        score+=(202+combo);
                        miss->hide();
                        perfect->hide();
                        great->show();
                        great_num+=1;
                        great->start();
                    }
                    combo+=1;
                    combo_widget->setcombo();
                    setscore(this);
                    if(combo_widget->isVisible()==false)
                        combo_widget->show();
                    hit[0]->show();
                    disconnect(myTimer,&QTimer::timeout,float_key[i],&FloatNote::dealTimeOut);
                    delete float_key[i];
                    float_key[i]=NULL;
                    break;
                }
            }
            break;
        case 16777237:      //下
            track[3]->show();
            for(int i=0;i<key_num;i++)
            {
                if(float_key[i]!=NULL&&float_key[i]->key=='P'&&float_key[i]->y>=750)
                {
                    if(float_key[i]->y>=785)
                    {
                        score+=(404+combo);
                        miss->hide();
                        great->hide();
                        perfect->show();
                        perfect_num+=1;
                        perfect->start();
                    }
                    else
                    {
                        score+=(202+combo);
                        miss->hide();
                        perfect->hide();
                        great->show();
                        great_num+=1;
                        great->start();
                    }
                    combo+=1;
                    combo_widget->setcombo();
                    setscore(this);
                    if(combo_widget->isVisible()==false)
                        combo_widget->show();
                    hit[3]->show();
                    disconnect(myTimer,&QTimer::timeout,float_key[i],&FloatNote::dealTimeOut);
                    delete float_key[i];
                    float_key[i]=NULL;
                    break;
                }
            }
            break;
        case 16777236:      //右
            track[4]->show();
            for(int i=0;i<key_num;i++)
            {
                if(float_key[i]!=NULL&&float_key[i]->key=='M'&&float_key[i]->y>=750)
                {
                    if(float_key[i]->y>=785)
                    {
                        score+=(404+combo);
                        miss->hide();
                        great->hide();
                        perfect->show();
                        perfect_num+=1;
                        perfect->start();
                    }
                    else
                    {
                        score+=(202+combo);
                        miss->hide();
                        perfect->hide();
                        great->show();
                        great_num+=1;
                        great->start();
                    }
                    combo+=1;
                    combo_widget->setcombo();
                    setscore(this);
                    if(combo_widget->isVisible()==false)
                        combo_widget->show();
                    hit[4]->show();
                    disconnect(myTimer,&QTimer::timeout,float_key[i],&FloatNote::dealTimeOut);
                    delete float_key[i];
                    float_key[i]=NULL;
                    break;
                }
            }
            break;
        }

    }
}

void PlayWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        switch(event->key())
        {
        case 16777234:      //左
            track[1]->hide();
            hit[1]->hide();
            break;
        case 16777235:      //上
            track[2]->hide();
            hit[2]->hide();
            break;
        case 32:            //空格
            track[0]->hide();
            hit[0]->hide();
            break;
        case 16777237:      //下
            track[3]->hide();
            hit[3]->hide();
            break;
        case 16777236:      //右
            track[4]->hide();
            hit[4]->hide();
            break;
        }
    }
}


void PlayWidget::PaintScene()
{
    bar=new myProgressBar(this);
    bar->hide();
    bar->resize(1758,100);
    bar->setMinimum(2000);
    bar->setValue(2000);
    bar->move(135,0);


    //初始化分数窗口
    QString text=QString::number(score);
    score_widget=new QLabel(this);
    QFont font("Haettenschweiler",50);
    score_widget->setFont(font);
    score_widget->setText(text);
    score_widget->setStyleSheet("QLabel{color:rgb(245,224,253);}"); //注意中英文输入法
    score_widget->adjustSize();
    score_widget->move(1890-score_widget->width(),80);

    for(int i=0;i<5;i++)
    {
        track[i]=new QWidget(this);
        track[i]->resize(270,1000);
        track[i]->setStyleSheet("QWidget{border-image:url(../img/audio_track.png);}");

    }
    track[0]->move(395,0);
    track[1]->move(623,0);
    track[2]->move(851,0);
    track[3]->move(1076,0);
    track[4]->move(1303,0);

    for(int i=0;i<5;i++)
    {
        track[i]->hide();

    }

    //初始化5个按钮
    five_key=new QWidget(this);
    five_key->resize(1200,250);
    five_key->move(419,808);
    up   =new QWidget(five_key);
    down =new QWidget(five_key);
    left =new QWidget(five_key);
    right=new QWidget(five_key);
    space=new QWidget(five_key);

    up->   setStyleSheet("QWidget{border-image:url(../img/up.png);}");
    down-> setStyleSheet("QWidget{border-image:url(../img/down.png);}");
    left-> setStyleSheet("QWidget{border-image:url(../img/left.png);}");
    right->setStyleSheet("QWidget{border-image:url(../img/right.png);}");
    space->setStyleSheet("QWidget{border-image:url(../img/space.png);}");

       up->resize(225,225);
     down->resize(225,225);
     left->resize(225,225);
    right->resize(225,225);
    space->resize(225,225);

    space-> move(0,0);
    left->   move(228,0);
    up->move(456,0);
    right->move(908,0);
    down ->move(681,0);

    //初始化击中音符产生的光效
    five_hit=new QWidget(this);
    five_hit->resize(1200,250);
    five_hit->move(432,848);

    for(int i=0;i<5;i++)
    {
        hit[i]=new QWidget(five_hit);
        hit[i]->resize(200,150);
        hit[i]->setStyleSheet("QWidget{border-image:url(../img/hit.png);}");
        hit[i]->hide();
    }
    hit[0]->move(0,0);
    hit[1]->move(228,0);
    hit[2]->move(456,0);
    hit[3]->move(681,0);
    hit[4]->move(908,0);




}

void setscore(PlayWidget* w)
{
    QString text=QString::number(score);
    w->score_widget->setText(text);
    w->score_widget->adjustSize();
    w->score_widget->move(1890-w->score_widget->width(),100);
}
