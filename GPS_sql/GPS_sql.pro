#-------------------------------------------------
#
# Project created by QtCreator 2013-05-27T11:26:25
#
#-------------------------------------------------

QT       += core gui sql
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = GPS_sql
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Gps_road.cpp \
    Gps_point.cpp \
    Gps_map.cpp \
    Gps_line.cpp \
    Gps_building.cpp

HEADERS  += mainwindow.h \
    Gps_road.h \
    Gps_point.h \
    Gps_map.h \
    Gps_line.h \
    Gps_building.h

FORMS    += mainwindow.ui
