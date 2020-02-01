#-------------------------------------------------
#
# Project created by QtCreator 2018-10-22T10:11:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = curves_family
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    aboutframe.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    aboutframe.h

FORMS    += mainwindow.ui \
    aboutframe.ui
CONFIG += c++11
