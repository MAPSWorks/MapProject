#-------------------------------------------------
#
# Project created by QtCreator 2010-10-08T12:42:35
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = MapProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qgsmap.cpp \
    qgsmap/qgslayer.cpp

HEADERS  += mainwindow.h \
    qgsmap.h \
    qgsmap/qgslayer.h

FORMS    += mainwindow.ui
