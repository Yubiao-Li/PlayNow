#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include<QThread>
#include"mybutton.h"
#include"source.h"
#include"mywidget.h"
#include"checkbutton.h"
#include"struct.h"

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

public slots:
    void load_widget();
    void load_song();
    void load_save();
    void keep_save();
signals:
    void load_widget_signal();
    void load_song_finsh();


};

#endif // MYTHREAD_H
