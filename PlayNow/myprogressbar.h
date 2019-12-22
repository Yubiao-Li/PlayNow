#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H

#include <QProgressBar>
#include"source.h"

class myProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit myProgressBar(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

private:
    QWidget* CD;
signals:

public slots:
};

#endif // MYPROGRESSBAR_H
