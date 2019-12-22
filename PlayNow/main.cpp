#include "widget.h"
#include <QApplication>
#include<QPixmap>
#include<QSplashScreen>
#include<QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QPixmap pixmap("../img/splash.png");
    QSplashScreen *splash=new QSplashScreen(pixmap);
    splash->show();
    QThread::sleep(1);

    w.show();

    splash->finish(&w);
    delete splash;

    return a.exec();
}
