#-------------------------------------------------
#
# Project created by QtCreator 2012-12-05T12:19:33
#
#-------------------------------------------------

QT       += core gui opengl sql


TARGET = GLWidget
#TEMPLATE = app


SOURCES += main.cpp\
        glwidget.cpp \
    Gps_line.cpp \
    Gps_point.cpp \
    Gps_road.cpp \
    firstwidget.cpp \
    gps_map.cpp \
    gps_sql_read.cpp \
    Gps_algorithm.cpp \
    Gps_building.cpp

HEADERS  += glwidget.h \
    PublicValue.h \
    Gps_line.h \
    Gps_point.h \
    Gps_road.h \
    firstwidget.h \
    gps_map.h \
    gps_sql_read.h \
    Gps_algorithm.h \
    Gps_building.h

FORMS    += glwidget.ui \
    firstwidget.ui
