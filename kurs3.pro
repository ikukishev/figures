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
    cfigureregistry.cpp \
    aboutdialog.cpp \
    ccomplexfigure.cpp \
    cdodecahedron.cpp \
    cfigure.cpp \
    cfigureparser.cpp \
    cprism.cpp \
    cpyramid.cpp \
    editdialog.cpp

HEADERS  += mainwindow.h \
    cpolygon.h \
    crectangle.h \
    ctriangle.h \
    cregulapolygon.h \
    cfigureregistry.h \
    aboutdialog.h \
    ccomplexfigure.h \
    cdodecahedron.h \
    cfigure.h \
    cfigureparser.h \
    cprism.h \
    cpyramid.h \
    editdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    editdialog.ui
