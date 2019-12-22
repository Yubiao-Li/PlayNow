#ifndef MYMOIVE_H
#define MYMOIVE_H

#include<QString>
#include <QLabel>
#include<QStackedWidget>
#include<QTimer>
#include<QVector>

class MyMoive : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MyMoive(QWidget *parent = nullptr,QVector<QString>page={});
    void init(QVector<QString>page);
    void start();
signals:

public slots:
    void DealTimeout();

private:
    QTimer *timer;
    int currentFrame;
    QVector<QLabel*>frame;
};

#endif // MYMOIVE_H
