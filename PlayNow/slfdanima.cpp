#include "slfdanima.h"

SlFdanima::SlFdanima(QObject *parent,QWidget *w,QPoint slide_start,QPoint slide_end,int slide_duration,
                     double start_opa,double end_start,int fade_duration) : QParallelAnimationGroup(parent)
{
    initAll(w,slide_start,slide_end,slide_duration,
                start_opa,end_start,fade_duration);

}

void SlFdanima::initAll(QWidget*w,QPoint slide_start,QPoint slide_end,int slide_duration,
                        double start_opa,double end_start,int fade_duration)
{
    effect=new QGraphicsOpacityEffect;
    w->setGraphicsEffect(effect);
    slide_ani=new QPropertyAnimation(w,"pos");
    fade_ani=new QPropertyAnimation(effect,"opacity");
    slide_ani->setStartValue(slide_start);
    slide_ani->setEndValue(slide_end);
    slide_ani->setDuration(slide_duration);
    fade_ani->setStartValue(start_opa);
    fade_ani->setEndValue(end_start);
    fade_ani->setDuration(fade_duration);
    addAnimation(fade_ani);
    addAnimation(slide_ani);
}

void SlFdanima::setlucency()
{
    effect->setOpacity(0);
}
