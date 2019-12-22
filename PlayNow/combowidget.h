#ifndef COMBOWIDGET_H
#define COMBOWIDGET_H

#include<QLabel>
#include<QPainter>
#include<QPen>
#include<QFont>
#include<QLinearGradient>


class ComboWidget : public QLabel
{
    Q_OBJECT
public:
    explicit ComboWidget(QWidget *parent = nullptr);
    void setcombo();


signals:

public slots:
};

#endif // COMBOWIDGET_H
