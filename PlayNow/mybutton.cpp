#include "mybutton.h"
#include"source.h"
#include<QPixmap>
#include<QBitmap>
#include<QRegion>
#include<QDebug>


mybutton::mybutton(QWidget *parent,QString init_image,QString press_image,QString move_image,QString forbid_image) : QPushButton(parent)
{
    initAll(parent,init_image,press_image,move_image,forbid_image);

}

void mybutton::initAll(QWidget *parent, QString init_image, QString press_image, QString move_image,QString forbid_image)
{
    setParent(parent);
    init_img=init_image;
    press_img=press_image;
    move_img=move_image;
    forbid_img=forbid_image;
    QPixmap normal(move_img);
    resize(normal.size());

    setnormal();
}

void mybutton::setnormal()
{
    setEnabled(true);
    QString style("QPushButton{outline:none;"
                                  "border-image:url(%1);"
                                  "}"
                                  "QPushButton:hover{"
                                  "border-image:url(%3);"
                                  "}"

                                  "QPushButton:pressed{"
                                  "border-image:url(%2);"
                                  "}"

                                  );
    setStyleSheet(style.arg(init_img).arg(press_img).arg(move_img));
}

void mybutton::setforbid()
{
    QString style("QPushButton{"
                                  "border-image:url(%1);"
                                  "}"
                                  );
    setStyleSheet(style.arg(forbid_img));
    setEnabled(false);
}


void mybutton::setmask()
{
    QPixmap normal(move_img);
    setMask(QBitmap(normal.mask()));
}
