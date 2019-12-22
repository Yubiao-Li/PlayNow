#include "loadlabel.h"

LoadLabel::LoadLabel(QWidget *parent) : QLabel(parent)
{
    initAll(parent);
}

void LoadLabel::initAll(QWidget *parent)
{
    setParent(parent);
    resize(1920,1080);

    load=new QMovie("../img/load.gif");
    label_load=new QLabel(this);
    label_load->setMovie(load);
    label_load->move(1500,830);

    load->start();
}
