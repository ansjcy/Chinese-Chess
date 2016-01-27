#-------------------------------------------------
#
# Project created by QtCreator 2015-07-17T20:29:53
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    welcome.cpp \
    ../../model/model.cpp \
    ../../common/global.cpp \
    ../../viewmodel/viewmodel.cpp \
    ../../musicmodel/music/widget.cpp \
    ipconnect.cpp \
    ../../alg/alg.cpp

HEADERS  += mainwindow.h \
    welcome.h \
    ../../musicmodel/music/widget.h \
    ../../viewmodel/viewmodel.h \
    ipconnect.h \
    ../../model/model.h \
    ../../model/moveable.h \
    ../../model/node.h \
    ../../model/recorder.h

FORMS    += mainwindow.ui \
    ../../musicmodel/music/widget.ui

RESOURCES += \
    ../../pic/res.qrc
