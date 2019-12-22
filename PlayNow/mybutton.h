#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QEvent>
#include<QMouseEvent>

class mybutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mybutton(QWidget *parent = nullptr,QString init_img="",QString press_img="",QString move_img="",QString forbid_img="");
    void initAll(QWidget *parent = nullptr,QString init_img="",QString press_img="",QString move_img="",QString forbid_img="");
    void setnormal();
    void setforbid();
    void setmask();

signals:

public slots:


private:
    QString init_img;
    QString press_img;
    QString move_img;
    QString forbid_img;
};

#endif // MYBUTTON_H
