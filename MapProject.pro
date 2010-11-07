#-------------------------------------------------
#
# Project created by QtCreator 2010-10-08T12:42:35
#
#-------------------------------------------------


QT       += core gui opengl network xml

TARGET = MapProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qgsmap.cpp \
    qgsmap/qgslayer.cpp \
    qgsmap/qgsfeatuefactory.cpp \
    qgsmap/qgsmapinfo.cpp \
    qgsmap/qgssettings.cpp \
    qgsmap/qgsrect.cpp

HEADERS  += mainwindow.h \
    qgsmap.h \
    qgsmap/qgslayer.h \
    qgsmap/qgsfeatuefactory.h \
    qgsmap/qgsmapinfo.h \
    qgsmap/qgssettings.h \
    qgsmap/qgsrect.h

FORMS    += mainwindow.ui
