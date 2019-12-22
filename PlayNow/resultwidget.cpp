#include "resultwidget.h"

ResultWidget::ResultWidget(QWidget *parent,QString font,int size,QString color) : QLabel(parent)
{
    setstyle(font,size,color);
}

void ResultWidget::setstyle(QString ft, int size, QString color)
{
    QFont font(ft,size);
    font.setBold(true);
    QString style="QLabel{color:rgb("+color+")};";
    setStyleSheet(style);
    setFont(font);
}


void ResultWidget::settext_muti(double value)
{
    QString text=QString::number(value,'f',0)+"X";
    setText(text);
    adjustSize();
}

void ResultWidget::settext(double value)
{
    QString text=QString::number(value,'f',0);
    setText(text);
    adjustSize();
}

void ResultWidget::settext_precent(double value)
{
    QString text=QString::number(value,'f',2)+"%";
    setText(text);
    adjustSize();
}
