#include "myscrollarea.h"

myScrollArea::myScrollArea(QWidget *parent) : QScrollArea(parent)
{
    initAll(parent);

}


void myScrollArea::initAll(QWidget *parent)
{

    setParent(parent);
    resize(700,550);
    select_widget=new myWidget(this);
    setWidget(select_widget);
    select_widget->resize(700,1000);
    QFile file("../scrollbar.qss");
    file.open(QIODevice::ReadOnly);
    setStyleSheet(file.readAll());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);
    QButtonGroup* song_group=new QButtonGroup(select_widget);

    for(int i=0;i<num_of_song+1;i++)
    {

        song[i]=new CheckButton(select_widget,"../img/tab.png","../img/tab_check.png",song_name[i]);
        song_group->addButton(song[i]);
        song[i]->move(0,115*i);

        //建立信号和槽
        connect(song[i],&CheckButton::toggled,
                [=]()
        {
            current_song=i;
            if(song[i]->isChecked()==true)
            {
                emit check();
                if(i==num_of_song)
                {
                    song_Check=QFileDialog::getOpenFileName(this,"open","../","source(*.txt)");
                    QStringList sections = song_Check.split('/');
                    song_Check=sections[sections.size()-1];
                    sections=song_Check.split('.');
                    song_Check=sections[0];
                }
                else
                {

                    song_Check=song_name[i];
                }
            }

        });

    }


}

void myScrollArea::keyPressEvent(QKeyEvent *){}
void myScrollArea::keyReleaseEvent(QKeyEvent *){}
