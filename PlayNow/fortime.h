#ifndef FORTIME_H
#define FORTIME_H

#include<QTime>
#include<QTimer>

extern QTime myTime;

extern QTimer *myTimer;    //计时器

extern int wait_time;

extern int begin_time;

extern int pause_time;

extern int pause_begin;

extern double time_per_beat;

extern int interval;   //定时器超时时间间隔

extern double current_speed;

class ForTime
{
public:
    ForTime();
};

#endif // FORTIME_H
