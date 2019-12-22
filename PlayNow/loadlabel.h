#ifndef LOADLABEL_H
#define LOADLABEL_H

#include <QLabel>
#include<QMovie>

class LoadLabel : public QLabel
{
    Q_OBJECT
public:
    explicit LoadLabel(QWidget *parent = nullptr);
    void initAll(QWidget *parent = nullptr);

signals:

public slots:

private:
    QMovie *load;
    QLabel *label_load;
};

#endif // LOADLABEL_H
