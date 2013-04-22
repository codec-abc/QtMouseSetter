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
    dialogoption.cpp \
    dialogaddprofile.cpp \
    mouseprofile.cpp \
    dialogmouseinformation.cpp

HEADERS  += mainwindow.h \
    dialogabout.h \
    dialogoption.h \
    dialogaddprofile.h \
    mouseprofile.h \
    dialogmouseinformation.h

FORMS    += mainwindow.ui \
    dialogabout.ui \
    dialogoption.ui \
    dialogaddprofile.ui \
    dialogmouseinformation.ui

RESOURCES += \
    Resource.qrc
