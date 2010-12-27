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
    qgsmap/qgsrect.cpp \
    qgsmap/qgsxmlparser.cpp \
    qgsmap/qgsimageloader.cpp \
    qgsmap/qgscoordinatetransform.cpp

HEADERS  += mainwindow.h \
    qgsmap.h \
    qgsmap/qgslayer.h \
    qgsmap/qgsfeatuefactory.h \
    qgsmap/qgsmapinfo.h \
    qgsmap/qgssettings.h \
    qgsmap/qgsrect.h \
    qgsmap/qgsxmlparser.h \
    qgsmap/qgsimageloader.h \
    qgsmap/qgscoordinatetransform.h

FORMS    += mainwindow.ui
