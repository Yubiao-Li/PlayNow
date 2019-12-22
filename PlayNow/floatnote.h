#ifndef FLOATNOTE_H
#define FLOATNOTE_H

#include"fortime.h"
#include<QWidget>

class FloatNote : public QWidget
{
    Q_OBJECT
public:
    explicit FloatNote(QWidget *parent = nullptr,double appear=0,char k=' ');
    void setflag(bool );
    bool getflag();
    char key;
    QString img;
    double y;
signals:
    void connect_signal();
    void disconnect_signal();
public slots:
    void dealTimeOut();

private:

    double appear_time;
    int fade_y;
    bool toggle_flag;
    void initAll(double appear,char k);


};

#endif // FLOATNOTE_H
