#-------------------------------------------------
#
# Project created by QtCreator 2018-11-22T17:30:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlayNow
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    source.cpp \
    combowidget.cpp \
    floatnote.cpp \
    fortime.cpp \
    mymoive.cpp \
    mybutton.cpp \
    checkbutton.cpp \
    myscrollarea.cpp \
    mywidget.cpp \
    playwidget.cpp \
    myprogressbar.cpp \
    loadlabel.cpp \
    resultwidget.cpp \
    mythread.cpp \
    slfdanima.cpp

HEADERS  += widget.h \
    source.h \
    combowidget.h \
    struct.h \
    floatnote.h \
    fortime.h \
    mymoive.h \
    mybutton.h \
    checkbutton.h \
    myscrollarea.h \
    mywidget.h \
    playwidget.h \
    myprogressbar.h \
    loadlabel.h \
    resultwidget.h \
    mythread.h \
    slfdanima.h

FORMS    += widget.ui

QT += multimedia

RC_ICONS = abc.ico

