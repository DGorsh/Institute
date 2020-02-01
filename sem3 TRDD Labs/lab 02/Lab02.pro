#-------------------------------------------------
#
# Project created by QtCreator 2018-10-13T10:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab02
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel.cpp

HEADERS  += mainwindow.h \
    tablemodel.h

FORMS    += mainwindow.ui

QT += xlsx
QT += sql
