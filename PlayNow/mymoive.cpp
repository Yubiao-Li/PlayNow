#include "mymoive.h"

MyMoive::MyMoive(QWidget *parent,QVector<QString>page) : QStackedWidget(parent)
{

    init(page);
}

void MyMoive::init(QVector<QString> page)
{
    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,&MyMoive::DealTimeout);
    currentFrame=0;
    for(int i=0;i<page.size();i++)
    {
        QLabel* l=new QLabel(this);
        l->setPixmap(page[i]);
        frame.push_back(l);
        addWidget(frame[i]);
    }
}
void MyMoive::start()
{
    timer->start(20);
}

void MyMoive::DealTimeout()
{
    setCurrentIndex(currentFrame);
    currentFrame++;
    if(currentFrame>count())
    {
        timer->stop();
        currentFrame=0;
    }
}
