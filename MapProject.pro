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
    qgsmap/qgslayer.cpp \
    qgsmap/qgsfeatuefactory.cpp \
    qgsmap/qgsthread.cpp \
    qgsmap/qgsmapinfo.cpp

HEADERS  += mainwindow.h \
    qgsmap.h \
    qgsmap/qgslayer.h \
    qgsmap/qgsfeatuefactory.h \
    qgsmap/qgsthread.h \
    qgsmap/qgsmapinfo.h

FORMS    += mainwindow.ui
