#include "checkbutton.h"

CheckButton::CheckButton(QWidget *parent,QString img,QString img_check,QString text) : QToolButton(parent)
{
    initAll(parent,img,img_check,text);

}

void CheckButton::initAll(QWidget *parent, QString img, QString img_check,QString word)
{

    init=img;
    check=img_check;
    text=word;

    select=new QMediaPlayer;
    select->setMedia(QUrl::fromLocalFile("../music/select.wav"));
    select->setVolume(30);

    connect(this,&CheckButton::clicked,
            [=]
    {
        select->play();
    });

    setParent(parent);
    QPixmap normal(img_check);

    resize(normal.size());
    /* 设置按钮的有效区域 */
    setMask(QBitmap(normal.mask()));

    setCheckable(true);
}


void CheckButton::paintEvent(QPaintEvent *)
{


    //按钮写字
    QFont font("Calibri",19);
    QPen pen(QColor(191,5,156));
    QPainter painter(this);
    painter.setPen(pen);
    painter.setFont(font);


    if(isChecked())
    {
        painter.drawPixmap(0,0,QPixmap(check));
        painter.drawText(107,92,text);
    }
    else
    {
        painter.drawPixmap(0,0,QPixmap(init));
        painter.drawText(105,90,text);
    }


}

