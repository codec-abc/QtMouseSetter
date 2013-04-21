#-------------------------------------------------
#
# Project created by QtCreator 2013-04-13T17:26:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MouseSetter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogabout.cpp \
    dialogoption.cpp

HEADERS  += mainwindow.h \
    dialogabout.h \
    dialogoption.h

FORMS    += mainwindow.ui \
    dialogMouseInformation.ui \
    dialogabout.ui \
    dialogoption.ui \
    ../dialog.ui

RESOURCES += \
    Resource.qrc
