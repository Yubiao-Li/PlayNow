#include "widget.h"
#include "ui_widget.h"

#define cout qDebug() << "[" <<__FILE__ <<":"<<__FUNCTION__<<":"<<__LINE__ <<"]"

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    for(int i=0;i<6;i++)
    {
        speed[i]=0.8+i*0.1;
    }
    setCursor(QCursor(QPixmap("../img/cursor.png")));
    myTime.start();
    //ui->setupUi(this);
    resize(1920,1080);
    setWindowTitle("Play Now");
    setWindowFlags(Qt::FramelessWindowHint);


    //创建多线程
    thread =new QThread(this);
    myT=new MyThread;
    myT->moveToThread(thread);
    thread->start();

    InitAll();

    connect(this,&Widget::destroyed,this,&Widget::DealClose);

}



void Widget::InitAll()
{
    interval=8;
    myTimer->setParent(this);

    click=new QMediaPlayer;
    click->setMedia(QUrl::fromLocalFile("../music/click.wav"));
    click->setVolume(50);

    //3个淡入动画
    fade_effect=new QGraphicsOpacityEffect;
    fade_effect2=new QGraphicsOpacityEffect;
    fade_effect3=new QGraphicsOpacityEffect;

    effect_fade_on=new QPropertyAnimation(fade_effect,"opacity");
    effect_fade_on->setStartValue(0);
    effect_fade_on->setEndValue(1);
    effect_fade_on->setDuration(300);

    effect2_fade_on=new QPropertyAnimation(fade_effect2,"opacity");
    effect2_fade_on->setStartValue(0);
    effect2_fade_on->setEndValue(0.9999);
    effect2_fade_on->setDuration(300);

    effect3_fade_on=new QPropertyAnimation(fade_effect3,"opacity");
    effect3_fade_on->setStartValue(0);
    effect3_fade_on->setEndValue(0.999999);
    effect3_fade_on->setDuration(300);


    //Begin窗口
    Begin_widget=new myWidget(this);
    Begin_widget->resize(1920,1080);
    drawBackGround(Begin_widget,QString("../img/menu.png"));
    {
        begin_button=new mybutton(Begin_widget,"../img/begin_init.png","../img/begin_press.png","../img/begin_move.png");
        begin_button->setmask();
        begin_button->move(500,450);
        connect(begin_button,&mybutton::clicked,
                [=]()
        {
            next_anima->addAnimation(back_anima);
            next_anima->addAnimation(effect2_fade_on);
            click->play();
            Stacked_Widget->setCurrentIndex(1);
            area_back->setGraphicsEffect(fade_effect2);
            next_anima->start();
        });
        connect(begin_button,&mybutton::clicked,myT,&MyThread::load_save);
        connect(begin_button,&mybutton::clicked,myT,&MyThread::load_widget);
        connect(myT,&MyThread::load_widget_signal,this,&Widget::DealLoadWidget);    //不在同一线程，不能使用lamda表达式

        //退出游戏按钮
        exit_button=new mybutton(Begin_widget,"../img/exit_init.png","../img/exit_press.png","../img/exit_move.png");
        exit_button->setmask();
        exit_button->move(900,450);
        connect(exit_button,&mybutton::clicked,this,&Widget::close);
        connect(exit_button,&mybutton::clicked,myT,&MyThread::keep_save);
    }

    //next窗口
    Next_widget=new myWidget(this);
    Next_widget->resize(1920,1080);
    drawBackGround(Next_widget,QString("../img/game_background.jpg"));
    {
        //返回按钮
        back=new QWidget(Next_widget);
        back->resize(1920,125);
        drawBackGround(back,"../img/back_back.png");
        back_button=new mybutton(back,"../img/back_init.png","../img/back_press.png","../img/back_move.png");
        back_button->setmask();
        back_button->move(50,0);

        next_anima=new QParallelAnimationGroup;
        back_anima=new SlFdanima(nullptr,back,QPoint(0,-125),QPoint(0,0),300,0,0.9999999,300);
        save_anima=new QParallelAnimationGroup;
        save_anima->addAnimation(effect3_fade_on);

        connect(back_button,&mybutton::clicked,
                [=]()
        {
            click->play();
            highest_score->hide();
            Stacked_Widget->setCurrentIndex(0);

        });

        //有滚动条的窗口
        area_back=new QWidget(Next_widget);
        area_back->resize(1327,814);
        drawBackGround(area_back,"../img/SelectSong.png");
        area_back->move(300,150);
        area=new myScrollArea(area_back);
        area->move(100,180);
        connect(area,&myScrollArea::check,this,&Widget::DealSave);

        //确定按钮
        sure=new mybutton(area_back,"../img/sure_init.png","../img/sure_press.png","../img/sure_move.png","../img/sure_forbid.png");
        sure->move(1000,600);
        sure->setforbid();
        connect(sure,&mybutton::clicked,
                [=]()
        {
            click->play();
            Stacked_Widget->setCurrentIndex(3);
        });
        connect(sure,&mybutton::clicked,myT,&MyThread::load_song);
        connect(myT,&MyThread::load_song_finsh,this,&Widget::Game);

        //历史最高评价
        highest_s=new QLabel(area_back);
        highest_a=new QLabel(area_back);
        highest_b=new QLabel(area_back);
        highest_d=new QLabel(area_back);
        highest_s->resize(488,350);
        highest_a->resize(488,350);
        highest_b->resize(488,350);
        highest_d->resize(488,350);
        highest_s->setPixmap(QPixmap("../img/s_best.png"));
        highest_a->setPixmap(QPixmap("../img/a_best.png"));
        highest_b->setPixmap(QPixmap("../img/b_best.png"));
        highest_d->setPixmap(QPixmap("../img/d_best.png"));
        highest_s->move(800,170);
        highest_a->move(800,170);
        highest_b->move(800,170);
        highest_d->move(800,170);
        fade_effect->setOpacity(0);
        fade_effect2->setOpacity(0);

        highest_s->hide();
        highest_a->hide();
        highest_b->hide();
        highest_d->hide();

        //历史最高分数
        QFont font("Brush Script MT",40);
        highest_score=new QLabel(area_back);
        highest_score->setFont(font);
        highest_score->setStyleSheet("QLabel{color:rgb(251,255,221)};");


        //调速
        speed_widget=new QWidget(area_back);
        for(int i=0;i<6;i++)
        {
            speed_num[i]=new QWidget(speed_widget);
            speed_num[i]->hide();

        }
        speed_num[0]->resize(174,64);
        drawBackGround(speed_num[0],"../img/1.5mul.png");
        speed_num[1]->resize(95,63);
        drawBackGround(speed_num[1],"../img/2mul.png");
        speed_num[2]->resize(175,64);
        drawBackGround(speed_num[2],"../img/2.5mul.png");
        speed_num[3]->resize(95,64);
        drawBackGround(speed_num[3],"../img/3mul.png");
        speed_num[4]->resize(98,65);
        drawBackGround(speed_num[4],"../img/4mul.png");
        speed_num[5]->resize(95,63);
        drawBackGround(speed_num[5],"../img/5mul.png");
        for(int i=0;i<6;i++)
        {
            speed_num[i]->move(320-speed_num[i]->width()/2,10);
        }
        speed_widget->resize(450,100);
        for(int i=0;i<6;i++)
        {
            QString init_img="../img/speed"+QString::number(i)+"_init.png";
            QString toggle_img="../img/speed"+QString::number(i)+"_toggle.png";
            speed_button[i]=new CheckButton(speed_widget,init_img,toggle_img);
            speed_button[i]->move(35*i,0);
        }
        for(int i=0;i<6;i++)
        {
            connect(speed_button[i],&QCheckBox::clicked,
                    [=]()
            {
                current_speed=speed[i];
                for(int j=0;j<i;j++)
                {
                    speed_button[j]->setChecked(true);
                }
                for(int j=i+1;j<6;j++)
                {
                    speed_button[j]->setChecked(false);
                }
                if(speed_button[i]->isChecked()==false)
                    speed_button[i]->setChecked(true);
                for(int j=0;j<6;j++)
                {
                    if(i==j)
                        speed_num[j]->show();
                    else
                        speed_num[j]->hide();
                }

                sure->setnormal();  //当有菜单被选中才可以开始
            });
        }
        speed_widget->move(840,540);
        speed_widget->setGraphicsEffect(fade_effect3);
        fade_effect3->setOpacity(0);
    }

    //load窗口
    Begin_label_load=new LoadLabel(this);
    drawBackGround(Begin_label_load,QString("../img/begin_load.jpg"));

    //play窗口
    Play_widget=new PlayWidget(this);
    Play_widget->resize(1920,1080);
    drawBackGround(Play_widget,"../img/play_background.jpg");
    {
        //暂停按钮
        pause=new mybutton(Play_widget,"../img/pause_init.png","../img/pause_press.png","../img/pause_init.png");
        pause->resize(87,82);
        pause->move(20,15);
        pause->setFocusPolicy(Qt::NoFocus);
        connect(pause,&mybutton::clicked,
                [=]()
        {
            click->play();
            music->pause();
            QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect(Play_widget);
            blurEffect->setBlurRadius(20);
            Play_widget->setGraphicsEffect(blurEffect);
            resume->setFocus();
            myTimer->stop();
            pause_begin=myTime.elapsed();
            Pause_widget->show();
        });
    }

    //settle窗口
    Settle_widget=new myWidget(this);
    Settle_widget->resize(1920,1080);
    drawBackGround(Settle_widget,"../img/settle_background.jpg");
    {
        //评分
        s=new QWidget(Settle_widget);
        s->resize(359,460);
        drawBackGround(s,"../img/S.png");
        s->move(1350,200);

        a=new QWidget(Settle_widget);
        a->resize(389,460);
        drawBackGround(a,"../img/A.png");
        a->move(1320,200);

        b=new QWidget(Settle_widget);
        b->resize(365,460);
        drawBackGround(b,"../img/B.png");
        b->move(1330,200);

        d=new QWidget(Settle_widget);
        d->resize(375,460);
        drawBackGround(d,"../img/D.png");
        d->move(1320,200);

        //各项数据
        score_big=new QWidget(Settle_widget);
        score_black=new QWidget(score_big);
        perfect_black=new QWidget(Settle_widget);
        great_black=new QWidget(Settle_widget);
        miss_black=new QWidget(Settle_widget);
        combo_black=new QWidget(Settle_widget);
        rank=new QWidget(Settle_widget);

        score_big->resize(1200,250);
        score_black->resize(978,141);
        perfect_black->resize(978,141);
        great_black->resize(978,141);
        miss_black->resize(978,141);
        combo_black->resize(978,175);
        rank->resize(356,86);

        drawBackGround(score_black,"../img/score_black.png");
        drawBackGround(perfect_black,"../img/perfect_black.png");
        drawBackGround(great_black,"../img/great_black.png");
        drawBackGround(miss_black,"../img/miss_black.png");
        drawBackGround(combo_black,"../img/combo_black.png");
        drawBackGround(rank,"../img/rank.png");

        score_big->move(0,50);
        perfect_black->move(0,230);
        great_black->move(0,410);
        miss_black->move(0,590);
        combo_black->move(0,810);
        rank->move(1400,100);

        score_big_anima=new SlFdanima(nullptr,score_big,QPoint(-978,50),QPoint(0,50),300,0,0.9999,300);
        perfect_black_anima=new SlFdanima(nullptr,perfect_black,QPoint(-978,230),QPoint(0,230),300,0,0.999,300);
        great_black_anima=new SlFdanima(nullptr,great_black,QPoint(-978,410),QPoint(0,410),300,0,0.99,300);
        miss_black_anima=new SlFdanima(nullptr,miss_black,QPoint(-978,590),QPoint(0,590),300,0,0.999,300);
        combo_black_anima=new SlFdanima(nullptr,combo_black,QPoint(-978,810),QPoint(0,810),300,0,0.999,300);
        s_anima=new SlFdanima(nullptr,s,QPoint(1350,300),QPoint(1350,200),500,0,0.99999,500);
        a_anima=new SlFdanima(nullptr,a,QPoint(1320,300),QPoint(1320,200),500,0,0.99999,500);
        b_anima=new SlFdanima(nullptr,b,QPoint(1330,300),QPoint(1330,200),500,0,0.99999,500);
        d_anima=new SlFdanima(nullptr,d,QPoint(1320,300),QPoint(1320,200),500,0,0.99999,500);

        settle_anima=new QSequentialAnimationGroup;
        settle_anima->addAnimation(score_big_anima);
        settle_anima->addAnimation(perfect_black_anima);
        settle_anima->addAnimation(great_black_anima);
        settle_anima->addAnimation(miss_black_anima);
        settle_anima->addAnimation(combo_black_anima);

        score_num_widget=new ResultWidget(score_black,"Microsoft YaHei UI Light",65,"245,224,253");
        perfect_num_widget=new ResultWidget(perfect_black,"Microsoft YaHei UI Light",55,"245,224,253");
        great_num_widget=new ResultWidget(great_black,"Microsoft YaHei UI Light",55,"245,224,253");
        miss_num_widget=new ResultWidget(miss_black,"Microsoft YaHei UI Light",55,"245,224,253");
        accuray_num_widget=new ResultWidget(combo_black,"Microsoft YaHei UI Light",60,"245,224,253");
        highest_combo_widget= new ResultWidget(combo_black,"Microsoft YaHei UI Light",60,"245,224,253");

        //continue按钮
        goon=new mybutton(Settle_widget,"../img/continue_init.png","../img/continue_press.png","../img/continue_init.png");
        goon->resize(402,202);
        goon->move(1480,860);
        goon_anima=new SlFdanima(nullptr,goon,QPoint(1480,800),QPoint(1480,860),300,0,0.9999,300);
        connect(goon,&mybutton::clicked,
                [=]()
        {
            click->play();
            best_result->hide();
            Stacked_Widget->setCurrentIndex(2);
            settle_music->stop();
            delete settle_music;
            delete settle_musiclist;
            bgm=new QMediaPlayer(this);
            bgmlist=new QMediaPlaylist;
            QUrl url=QUrl::fromLocalFile("../music/yhzr.wav");
            bgmlist->addMedia(url);
            bgmlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            bgm->setPlaylist(bgmlist);
            bgm->play();
        });
        connect(goon,&mybutton::clicked,this,&Widget::DealSave);

        //best_result图
        best_result=new QWidget(score_big);
        best_result->resize(187,183);
        drawBackGround(best_result,"../img/best_result.png");
        best_result->move(850,20);
        best_result->hide();
    }

    //stack窗口
    Stacked_Widget=new QStackedWidget(this);
    Stacked_Widget->resize(1920,1080);

    {
        //按顺序添加widget
        Stacked_Widget->addWidget(Begin_widget);
        Stacked_Widget->addWidget(Begin_label_load);
        Stacked_Widget->addWidget(Next_widget);
        Stacked_Widget->addWidget(Play_widget);
        Stacked_Widget->addWidget(Settle_widget);
    }

    //初始化游戏开始界面
    Stacked_Widget->setCurrentIndex(0);

    //pause窗口
    Pause_widget=new myWidget(this);
    Pause_widget->resize(500,800);
    Pause_widget->move(710,130);
    {
        //pause文字
        pause_word=new QWidget(Pause_widget);
        pause_word->resize(300,300);
        drawBackGround(pause_word,"../img/pause.png");
        pause_word->move(Pause_widget->width()/2-150,0);

        //resume按钮
        resume=new mybutton(Pause_widget,"../img/resume_init.png","../img/resume_press.png","../img/resume_init.png");
        resume->move((Pause_widget->width()-resume->width())/2,310);
        resume->setFocusPolicy(Qt::NoFocus);
        connect(resume,&mybutton::clicked,
                [=]()
        {
            click->play();
            pause_time+=myTime.elapsed()-pause_begin;
            music->play();
            Play_widget->setGraphicsEffect(NULL);
            Play_widget->setFocus();
            myTimer->start(interval);
            Pause_widget->hide();
        });

        //quit按钮
        quit=new mybutton(Pause_widget,"../img/quit_init.png","../img/quit_press.png","../img/quit_init.png");
        quit->move((Pause_widget->width()-resume->width())/2,650);
        quit->setFocusPolicy(Qt::NoFocus);
        connect(quit,&mybutton::clicked,this,&Widget::DealQuit);
        connect(quit,&mybutton::clicked,
                [=]()
        {
            click->play();
        });

    }
    Pause_widget->hide();

    //游戏bgm
    bgm=new QMediaPlayer(this);
    bgmlist=new QMediaPlaylist;
    QUrl url=QUrl::fromLocalFile("../music/yhzr.wav");
    bgmlist->addMedia(url);
    bgmlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgm->setPlaylist(bgmlist);
    bgm->play();
}

void Widget::Game()
{

    //停止bgm
    bgm->stop();
    delete bgm;
    delete bgmlist;

    //播放音乐
    QUrl url=QUrl::fromLocalFile("../music/"+song_Check+".wav");
    music=new QMediaPlayer(this);
    begin_time=myTime.elapsed();
    music->setMedia(url);
    music->play();
    music->setNotifyInterval(50);
    connect(music,SIGNAL(durationChanged(qint64)),this,SLOT(DealDurationChange(qint64)));
    connect(music,SIGNAL(positionChanged(qint64)),this,SLOT(DealPositionChange(qint64)));

    //处理音符出现
    myTimer->start(interval);
    myTimer->setTimerType(Qt::PreciseTimer);
    time_per_beat=60000.0/BPM;
    for(int i=0;i<key_num;i++)
    {
        float_key[i]=new FloatNote(Play_widget,key_load[i].token*time_per_beat-845/current_speed,key_load[i].key);
        float_key[i]->hide();
        drawBackGround(float_key[i],float_key[i]->img);
        connect(myTimer,&QTimer::timeout,float_key[i],&FloatNote::dealTimeOut);

        connect(float_key[i],&FloatNote::connect_signal,
                [=]()
        {
            float_key[i]->show();
        });

        connect(float_key[i],&FloatNote::disconnect_signal,
                [=]()
        {
            if(float_key[i]->key!='@')
            {
                if(combo_widget->isVisible()==true)
                    combo_widget->hide();
                if(combo>highest_combo)
                    highest_combo=combo;
                combo=0;
                perfect->hide();
                great->hide();
                miss->show();
                miss_num+=1;
                miss->start();
             }
            disconnect(myTimer,&QTimer::timeout,float_key[i],&FloatNote::dealTimeOut);
            delete float_key[i];
            float_key[i]=NULL;
        });

    }

    //初始化评价图片和连击数
    combo_widget=new ComboWidget(Play_widget);
    perfect=new MyMoive(Play_widget,{"../img/perfect/1.png","../img/perfect/2.png","../img/perfect/3.png","../img/perfect/4.png"});
    great=new MyMoive(Play_widget,{"../img/great/1.png","../img/great/2.png","../img/great/3.png","../img/great/4.png"});
    miss=new MyMoive(Play_widget,{"../img/miss/1.png","../img/miss/2.png","../img/miss/3.png","../img/miss/4.png"});

    combo_widget->setWindowFlags(Qt::WindowStaysOnTopHint);
    perfect->setWindowFlags(Qt::WindowStaysOnTopHint);
    great->setWindowFlags(Qt::WindowStaysOnTopHint);
    miss->setWindowFlags(Qt::WindowStaysOnTopHint);

    perfect->resize(560,160);
    great->resize(400,150);
    miss->resize(300,150);

    perfect->move(740,200);
    great->move(785,200);
    miss->move(839,200);


//    test2= new FloatNote(this);
//    test2->resize(150,150);
//    drawBackGround(test2,"../img/space_float.png");
//    test2->move(913,845);
//    test2->show();
}


void Widget::DealClose()
{
  thread->quit();
  thread->wait();
  delete myT;
}


void Widget::drawBackGround(QWidget* w,QString img)
{
    w->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = w->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(img).scaled(// 缩放背景图.
                w->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    w->setPalette(palette);
}



void Widget::DealLoadWidget()
{
    Stacked_Widget->setCurrentIndex(2);
}

void Widget::DealQuit()
{
    Play_widget->setGraphicsEffect(NULL);
    Settle();

}

void Widget::DealDurationChange(qint64 duration)
{
    music_duration=duration;
    Play_widget->bar->setRange(2000,music_duration+2000);
    Play_widget->bar->setValue(2000);
}

void Widget::DealPositionChange(qint64 duration)
{

    if(music_duration!=0&&duration>=music_duration)
    {
        Settle();
    }
    else
    {
        if(Play_widget->bar->isVisible()==false)
            Play_widget->bar->show();
        Play_widget->bar->setValue(duration+2000);
    }
}

void Widget::Settle()
{
    goon_anima->setlucency();
    s_anima->setlucency();
    a_anima->setlucency();
    b_anima->setlucency();
    d_anima->setlucency();
    switch (eva) {
    case 's':
        settle_anima->removeAnimation(s_anima);
        break;
    case 'a':
        settle_anima->removeAnimation(a_anima);
        break;
    case 'b':
        settle_anima->removeAnimation(b_anima);
        break;
    case 'd':
        settle_anima->removeAnimation(d_anima);
        break;
    default:
        break;
    }

    //计算准确率
    if(miss_num+perfect_num+great_num==0)
        accuray_num=0;
    else
        accuray_num=double(perfect_num+great_num)/(miss_num+perfect_num+great_num)*100;
    if(highest_combo==0)
        highest_combo=combo;

    if(area->current_song!=num_of_song)
    {
        if(score>save_data[area->current_song].score)
        {
            save_data[area->current_song].score=score;
            best_result->show();
        }
    }
    Stacked_Widget->setCurrentIndex(4);

    //处理各个数据位置
    score_num_widget->settext(score);
    score_num_widget->move((977-score_num_widget->width())/2,0);
    perfect_num_widget->settext_muti(perfect_num);
    perfect_num_widget->move(630,14);
    great_num_widget->settext_muti(great_num);
    great_num_widget->move(630,14);
    miss_num_widget->settext_muti(miss_num);
    miss_num_widget->move(630,14);
    highest_combo_widget->settext_muti(highest_combo);
    highest_combo_widget->move(60,22);
    accuray_num_widget->settext_precent(accuray_num);
    accuray_num_widget->move(950-accuray_num_widget->width(),22);

    score_big_anima->setlucency();
    perfect_black_anima->setlucency();
    great_black_anima->setlucency();
    miss_black_anima->setlucency();
    combo_black_anima->setlucency();

    if(accuray_num>97&&Play_widget->bar->value()>=music_duration+1800)
    {
        if(area->current_song!=num_of_song)
            if(save_data[area->current_song].grade!='s')
                save_data[area->current_song].grade='s';
        settle_anima->insertAnimation(5,s_anima);
        eva='s';
    }
    else if(accuray_num>95&&Play_widget->bar->value()>=music_duration+1800)
    {
        if(area->current_song!=num_of_song)
            if(save_data[area->current_song].grade!='s'&&save_data[area->current_song].grade!='a')
                save_data[area->current_song].grade='a';
        settle_anima->insertAnimation(5,a_anima);
        eva='a';
    }
    else if(accuray_num>90&&Play_widget->bar->value()>=music_duration+1800)
    {
        if(area->current_song!=num_of_song)
            if(save_data[area->current_song].grade!='s'&&save_data[area->current_song].grade!='a'&&save_data[area->current_song].grade!='b')
                save_data[area->current_song].grade='b';
        settle_anima->insertAnimation(5,b_anima);
        eva='b';
    }
    else
    {
        if(area->current_song!=num_of_song)
            if(save_data[area->current_song].grade!='s'&&save_data[area->current_song].grade!='a'&&save_data[area->current_song].grade!='b'&&save_data[area->current_song].grade!='d')
            {
                save_data[area->current_song].grade='d';
            }
        settle_anima->insertAnimation(5,d_anima);
        eva='d';
    }
    settle_anima->addAnimation(goon_anima);
    settle_anima->start();

    combo=0;
    highest_combo=0;
    score=0;
    perfect_num=0;
    great_num=0;
    miss_num=0;
    accuray_num=0;

    combo_widget->hide();
    perfect->hide();
    great->hide();
    miss->hide();
    myTimer->stop();
    pause_time=0;
    Pause_widget->hide();
    Play_widget->bar->setValue(2000);
    setscore(Play_widget);

    for(int i=0;i<key_num;i++)
    {
        QVector<rhythm>::iterator it1 = key_load.begin();
        key_load.erase(it1);

        if(float_key[0]!=NULL)
        {
            disconnect(myTimer,&QTimer::timeout,float_key[0],&FloatNote::dealTimeOut);
            delete float_key[0];
            float_key[0]=NULL;
        }
        QVector<FloatNote*>::iterator it2=float_key.begin();
        float_key.erase(it2);

    }

    music->stop();
    delete music;
    settle_music=new QMediaPlayer(this);
    QUrl url=QUrl::fromLocalFile("../music/Settle.wav");
    settle_musiclist=new QMediaPlaylist;
    settle_musiclist->addMedia(url);
    settle_musiclist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    settle_music->setPlaylist(settle_musiclist);
    settle_music->play();

}

void Widget::DealSave()
{


    highest_a->hide();
    highest_b->hide();
    highest_d->hide();
    highest_s->hide();
    highest_score->hide();


    if(area->current_song!=num_of_song)
    {
        save_anima->addAnimation(effect_fade_on);
        save_anima->addAnimation(effect2_fade_on);

        highest_score->setGraphicsEffect(fade_effect2);

        switch (save_data[area->current_song].grade)
        {
        case 's':
            highest_s->setGraphicsEffect(fade_effect);
            highest_s->show();
            break;
        case 'a':
            highest_a->setGraphicsEffect(fade_effect);
            highest_a->show();
            break;
        case 'b':
            highest_b->setGraphicsEffect(fade_effect);
            highest_b->show();
            break;
        case 'd':
            highest_d->setGraphicsEffect(fade_effect);
            highest_d->show();
            break;
        default:
            break;
        }


        if(save_data[area->current_song].score!=0)
        {
            highest_score->show();
            highest_score->setText(QString::number(save_data[area->current_song].score));
            highest_score->adjustSize();
            highest_score->move(945-highest_score->width()/2,395);
        }
    }
    else
    {
        save_anima->removeAnimation(effect2_fade_on);
        save_anima->removeAnimation(effect_fade_on);
    }
    speed_widget->setGraphicsEffect(fade_effect3);
    save_anima->start();
}

Widget::~Widget()
{
  delete ui;
}
