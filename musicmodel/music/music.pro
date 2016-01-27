#-------------------------------------------------
#
# Project created by QtCreator 2015-07-18T09:02:17
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
macx:QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
macx:QMAKE_MAC_SDK=macosx10.9
TARGET = music
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES +=
