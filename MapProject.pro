#-------------------------------------------------
#
# Project created by QtCreator 2010-10-08T12:42:35
#
#-------------------------------------------------

<<<<<<< HEAD
QT       += core gui opengl network
=======
QT       += core gui opengl network xml
>>>>>>> acbcfe76a74a984cdf3bca8d3d5c589c0d4a6ffa

TARGET = MapProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qgsmap.cpp \
    qgsmap/qgslayer.cpp \
    qgsmap/qgsfeatuefactory.cpp \
    qgsmap/qgsthread.cpp \
    qgsmap/qgsmapinfo.cpp \
    qgsmap/qgssettings.cpp

HEADERS  += mainwindow.h \
    qgsmap.h \
    qgsmap/qgslayer.h \
    qgsmap/qgsfeatuefactory.h \
    qgsmap/qgsthread.h \
    qgsmap/qgsmapinfo.h \
    qgsmap/qgssettings.h

FORMS    += mainwindow.ui
