#ifndef WIDGET_H
#define WIDGET_H

#include"source.h"
#include"fortime.h"
#include"mybutton.h"
#include"mywidget.h"
#include"checkbutton.h"
#include"mythread.h"
#include"myscrollarea.h"
#include"loadlabel.h"
#include"playwidget.h"
//#include"floatnote.h"
#include"combowidget.h"
#include"resultwidget.h"
#include"slfdanima.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void InitAll();

    ~Widget();



public slots:
    void DealClose();
    void DealLoadWidget();
    void DealQuit();
    void DealDurationChange(qint64);
    void DealPositionChange(qint64);
    void DealSave();    //处理生成最好记录窗口

private:
    void drawBackGround(QWidget*,QString);
    void Game();
    void Settle();

    Ui::Widget *ui;

    mybutton *begin_button;
    mybutton *exit_button;
    mybutton *back_button;
    mybutton* sure;
    mybutton* pause;
    mybutton* resume;
    mybutton* quit;
    mybutton* goon;
    CheckButton* speed_button[6];

    QMediaPlayer *bgm;
    QMediaPlaylist *bgmlist;
    QMediaPlayer *music;
    QMediaPlayer *settle_music;
    QMediaPlaylist *settle_musiclist;
    QMediaPlayer* click;

    QWidget *area_back;
    myScrollArea *area;
    myWidget *select_widget;
    QStackedWidget *Stacked_Widget;
    myWidget *Begin_widget;
    myWidget *Next_widget;
    myWidget *Pause_widget;
    myWidget *Settle_widget;
    PlayWidget *Play_widget;
    LoadLabel *Begin_label_load;

    QWidget *score_big;
    QWidget *score_black;
    QWidget *perfect_black;
    QWidget *great_black;
    QWidget *miss_black;
    QWidget *combo_black;
    QWidget *rank;
    ResultWidget *score_num_widget;
    ResultWidget *perfect_num_widget;
    ResultWidget *great_num_widget;
    ResultWidget *miss_num_widget;
    ResultWidget *accuray_num_widget;
    ResultWidget *highest_combo_widget;
    QWidget *pause_word;
    QWidget *best_result;
    QWidget *back;
    QLabel *highest_score;
    QLabel *highest_s;
    QLabel *highest_a;
    QLabel *highest_b;
    QLabel *highest_d;
    QWidget *s;
    QWidget *a;
    QWidget *b;
    QWidget *d;
    QWidget *speed_widget;
    QWidget *speed_num[6];

    QGraphicsOpacityEffect *fade_effect;
    QGraphicsOpacityEffect *fade_effect2;
    QGraphicsOpacityEffect *fade_effect3;

    QThread *thread;
    MyThread *myT;

    SlFdanima *back_anima;
    SlFdanima *score_big_anima;
    SlFdanima *perfect_black_anima;
    SlFdanima *great_black_anima;
    SlFdanima *miss_black_anima;
    SlFdanima *combo_black_anima;
    SlFdanima *s_anima;
    SlFdanima *a_anima;
    SlFdanima *b_anima;
    SlFdanima *d_anima;
    SlFdanima *goon_anima;

    QSequentialAnimationGroup *settle_anima;
    QParallelAnimationGroup *next_anima;
    QParallelAnimationGroup *save_anima;
    QPropertyAnimation *back_slide;
    QPropertyAnimation *effect_fade_on;
    QPropertyAnimation *effect2_fade_on;
    QPropertyAnimation *effect3_fade_on;

    int music_duration; //音乐的时长
    double opacity=0;
    double speed[6];
    char eva;

//    FloatNote* test2;


};

#endif // WIDGET_H


