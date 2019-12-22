#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QLabel>

class ResultWidget : public QLabel
{
    Q_OBJECT
public:
    explicit ResultWidget(QWidget *parent = nullptr,QString font="",int size=16,QString color="");
    void setstyle(QString font,int size,QString color);
    void settext_precent(double );
    void settext_muti(double);
    void settext(double );
signals:

public slots:

private:

};

#endif // RESULTWIDGET_H
