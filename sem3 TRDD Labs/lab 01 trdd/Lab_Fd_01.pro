#-------------------------------------------------
#
# Project created by QtCreator 2018-10-06T12:06:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab_Fd_01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mousedrawingview.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
    mousedrawingview.h \
    dialogabout.h

FORMS    += mainwindow.ui \
    dialogabout.ui
CONFIG += c++11
