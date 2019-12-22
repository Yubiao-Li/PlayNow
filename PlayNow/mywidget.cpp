#include "mywidget.h"

myWidget::myWidget(QWidget *parent) : QWidget(parent)
{
    initAll(parent);
}

void myWidget::initAll(QWidget *parent)
{
    setParent(parent);

    //设置透明窗口
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));
    setPalette(pal);
}

