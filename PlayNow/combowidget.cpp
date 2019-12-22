#include "combowidget.h"
#include"source.h"

ComboWidget::ComboWidget(QWidget *parent) : QLabel(parent)
{

}

void ComboWidget::setcombo()
{
    QString text=QString::number(combo);
    QFont font("Ravie",80);
    setStyleSheet("QLabel{color:rgba(35,5,67,0.5)};");
    setFont(font);
    setText(text);
    adjustSize();
    move(970-width()/2,300);
}
