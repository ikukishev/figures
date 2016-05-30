#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T22:32:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kurs3
TEMPLATE = app
CONFIG += c++11 rtti

SOURCES += main.cpp\
        mainwindow.cpp \
    cpolygon.cpp \
    crectangle.cpp \
    ctriangle.cpp \
    cregulapolygon.cpp \
    cfigureregistry.cpp

HEADERS  += mainwindow.h \
    cpolygon.h \
    crectangle.h \
    ctriangle.h \
    cregulapolygon.h \
    cfigureregistry.h

FORMS    += mainwindow.ui
