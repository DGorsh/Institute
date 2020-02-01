#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T18:56:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphInterface
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scene.cpp \
    mgraphobject.cpp \
    muncorrectinput.cpp \
    solution_0.cpp \
    solution_12.cpp \
    solution_13.cpp \
    solution_17.cpp \
    solution_19.cpp \
    solution_2.cpp \
    msolutionnotfound.cpp \
    solution_21.cpp \
    solution_3.cpp \
    solution_7.cpp \
    solution_15.cpp \
    solution_10.cpp \
    solution_14.cpp \
    solution_4.cpp \
    solution_5.cpp \
    solution_6.cpp \
    solution_11.cpp \
    solution_16.cpp \
    solution_8.cpp \
    solution_9.cpp

HEADERS += \
        mainwindow.h \
    scene.h \
    mgraphobject.h \
    filereader.h \
    msolution.h \
    muncorrectinput.h \
    manswer.h \
    solution_0.h \
    msolutionexecutor.h \
    solution_12.h \
    solution_13.h \
    solution_17.h \
    solution_19.h \
    solution_2.h \
    msolutionnotfound.h \
    solution_21.h \
    solution_3.h \
    mpair.h \
    solution_7.h \
    solution_15.h \
    solution_10.h \
    solution_14.h \
    solution_4.h \
    solution_5.h \
    solution_6.h \
    solution_11.h \
    solution_16.h \
    solution_8.h \
    solution_9.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
