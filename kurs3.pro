#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T22:32:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kurs3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpolygon.cpp \
    crectangle.cpp \
    ctriangle.cpp \
    cregulapolygon.cpp

HEADERS  += mainwindow.h \
    cpolygon.h \
    crectangle.h \
    ctriangle.h \
    cregulapolygon.h

FORMS    += mainwindow.ui
