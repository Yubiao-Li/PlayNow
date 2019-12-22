#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QPalette>

class myWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myWidget(QWidget *parent = nullptr);
    void initAll(QWidget *parent = nullptr);



signals:

public slots:
};

#endif // MYWIDGET_H
