#include "myprogressbar.h"

myProgressBar::myProgressBar(QWidget *parent) : QProgressBar(parent)
{
    CD=new QWidget(this);
    CD->setStyleSheet("QWidget{border-image:url(../img/CD.png);}");
    CD->resize(61,59);
    QPixmap normal("../img/CD.png");
    CD->setMask(QBitmap(normal.mask()));
}

void myProgressBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    int a=value()-minimum();
    int b=maximum()-minimum();
    double side = double(a)/b*width();
    QRect backRect(0, 0,width(), height());
    QRect frontRect(0, 0, side, height());
    //画底部的进度条
    p.setPen(Qt::NoPen);
    QPixmap backMap = QPixmap("../img/progress_back.png");
    p.drawPixmap(backRect, backMap);
    //画上面的进度条
    QPixmap frontMap = QPixmap("../img/progress_front.png");
    p.drawPixmap(frontRect,frontMap,frontRect);

    CD->move(side-CD->width()/2,25);
}
