#ifndef SOURCE_H
#define SOURCE_H


#include<cstring>
#include<fstream>

#include<QBitmap>
#include<QButtonGroup>
#include<QCheckBox>
#include<QCursor>
#include<QDataStream>
#include<QDebug>
#include<QFile>
#include<QFileDialog>
#include<QFont>
#include<QGraphicsBlurEffect>
#include<QGraphicsOpacityEffect>
#include<QKeyEvent>
#include<QLabel>
#include<QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QMediaPlaylist>
#include<QMovie>
#include<QtMultimedia/QSound>
#include<QPainter>
#include<QParallelAnimationGroup>
#include<QPixmap>
#include<QPropertyAnimation>
#include<QRadioButton>
#include<QScrollArea>
#include<QSequentialAnimationGroup>
#include<QStackedWidget>
#include<QString>
#include<QTextCodec>
#include<QThread>
#include<QTime>
#include<QTimer>
#include<QVector>
#include<QWidget>


#include"struct.h"
#include"floatnote.h"
#include"combowidget.h"
#include"mymoive.h"

using namespace std;

extern double BPM;

extern QString song_Check;    //选中的歌曲名字

const int num_of_song=3;    //歌曲数量

extern QString song_name[num_of_song+1];  //各选项名字

extern QVector<rhythm>key_load;  //用于存储游戏时音符顺序

extern int key_num;

extern QVector<FloatNote*>float_key;

extern MyMoive *perfect,*great,*miss;

extern int combo;

extern ComboWidget *combo_widget;

extern int score;

extern int perfect_num;
extern int great_num;
extern int miss_num;
extern double accuray_num;
extern int highest_combo;

extern double scale;

extern QVector<archive>save_data;

class source
{
    source();

};


#endif // SOURCE_H
