#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

#include <QScrollArea>
#include<QWidget>
#include"mywidget.h"
#include"checkbutton.h"
#include<QFile>
#include"source.h"


class myScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit myScrollArea(QWidget *parent = nullptr);
    void initAll(QWidget *parent = nullptr);

    int current_song;

signals:
    void check();


protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *event);

public slots:

private:
    myWidget* select_widget;
    CheckButton *song[num_of_song];
    QLabel *text[3];

};

#endif // MYSCROLLAREA_H
