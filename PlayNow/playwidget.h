#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include"source.h"
//#include"mythread.h"
#include"source.h"
#include"mybutton.h"
#include"myprogressbar.h"

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWidget(QWidget *parent = nullptr);
    void initAll(QWidget *parent=nullptr);
    void PaintScene();
    friend void setscore(PlayWidget* w);


    myProgressBar *bar;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
signals:

public slots:

private:
    QWidget *five_key,*track[5];
    QWidget *up,*right,*left,*down,*space;
    QWidget *five_hit;
    QWidget *hit[5];
    QLabel *score_widget;
    int m_pressFlag;
};

#endif // PLAYWIDGET_H
