#include "fortime.h"



QTime myTime;

QTimer *myTimer=new QTimer;

int wait_time=0;    //等待时长

int begin_time=0;   //开始时刻

int pause_time=0;   //暂停时长

int pause_begin=0;  //暂停时刻

double time_per_beat=0;

int interval=0;   //定时器超时时间间隔

double current_speed=0;

ForTime::ForTime()
{

}
