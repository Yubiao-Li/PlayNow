#include "floatnote.h"
#include<QDebug>

FloatNote::FloatNote(QWidget *parent,double appear,char k) : QWidget(parent)
{
    initAll(appear,k);
}

void FloatNote::initAll(double appear,char k)
{
    fade_y=950;
    y=0;
    appear_time=appear;
    key=k;
    resize(150,150);

    //换位置,设置图片
    switch (key)
    {
    case 'M':       //右键
        img="../img/right_float.png";
        move(1366,0);
        break;
    case 'P':       //下键
        img="../img/down_float.png";
        move(1138,0);
        break;
    case 'H':       //上键
        img="../img/up_float.png";
        move(913,0);
        break;
    case 'K':       //左键
        img="../img/left_float.png";
        move(686,0);
        break;
    case ' ':       //空格键
        img="../img/space_float.png";
        move(457,0);
    default:
        break;
    }
}

void FloatNote::dealTimeOut()
{
    wait_time=myTime.elapsed()-begin_time-pause_time;
    if(y>=fade_y)
        emit disconnect_signal();
    else if(wait_time>=appear_time)
    {
        emit connect_signal();
        y+=interval*current_speed;

        switch (key)
        {
        case 'M':       //右键
            move(1366,y);
            break;
        case 'P':       //下键
            move(1138,y);
            break;
        case 'H':       //上键
            move(913,y);
            break;
        case 'K':       //左键
            move(686,y);
            break;
        case ' ':
            move(457,y);
        default:
            break;
        }
    }
}

void FloatNote::setflag(bool value)
{
    toggle_flag=value;
}

bool FloatNote::getflag()
{
    return toggle_flag;
}
