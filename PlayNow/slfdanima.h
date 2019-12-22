#ifndef SLFDANIMA_H
#define SLFDANIMA_H

#include <QParallelAnimationGroup>
#include<QObject>
#include<QWidget>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QPoint>

class SlFdanima : public QParallelAnimationGroup
{
    Q_OBJECT
public:
    explicit SlFdanima(QObject *parent =Q_NULLPTR,QWidget *w=nullptr,QPoint slide_start=QPoint(0,0),QPoint slide_end=QPoint(0,0),int slide_duration=0,
                       double start_opa=1,double end_start=1,int fade_duration=0);
    void initAll(QWidget*w,QPoint slide_start,QPoint slide_end,int slide_duration,
                  double start_opa,double end_start,int fade_duration);
    void setlucency();

signals:

private:
    QPropertyAnimation *slide_ani;
    QPropertyAnimation *fade_ani;
    QGraphicsOpacityEffect *effect;
public slots:
};

#endif // SLFDANIMA_H
