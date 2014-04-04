#include <QtGui/QApplication>
#include "glwidget.h"
#include"firstwidget.h"
//#include"gps_sql_read.h"
#include"gps_map.h"
#include"Gps_algorithm.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
    Gps_map map;
    map.read_point();
    map.read_road();
    map.read_line();
    map.read_building();
    Gps_algorithm al(&map);
    w.setWindowTitle("GPS");
    w.show();
    qDebug()<<"x_min"<<map.Min_x;
    qDebug()<<"x_max"<<map.Max_x;
    qDebug()<<"y_min"<<map.Min_y;
    qDebug()<<"y_max"<<map.Max_y;
    w.set_al(&al);
     w.set_map(&map);
    FirstWidget f;
    f.set_map(&map);
    f.set_gl(&w);
    f.show();
    f.on_pushButton_search_clicked();
    return a.exec();
}
