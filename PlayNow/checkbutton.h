#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include<QToolButton>
#include<QPixmap>
#include<QBitmap>
#include<QMouseEvent>
#include<QPainter>
#include<QPaintEvent>
#include<QDebug>
#include<QColor>
#include<QtMultimedia/QMediaPlayer>
#include<QPen>

class CheckButton : public QToolButton
{
    Q_OBJECT
public:
    explicit CheckButton(QWidget *parent = nullptr,QString img="",QString="",QString="");
    void initAll(QWidget *parent = nullptr,QString img="",QString="",QString="");

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    QString text;
    QString check;
    QString init;

    QMediaPlayer* select;
};

#endif // CHECKBUTTON_H
