#ifndef GPS_SQL_READ_H
#define GPS_SQL_READ_H
#include <QSqlDatabase>
#include <QTextCodec>
#include <QDebug>
#include <QSqlQuery>
//#include "gps_map.h"

class Gps_sql_read
{
public:
    Gps_sql_read();
    QSqlDatabase db;
    QSqlQuery read_point();
    QSqlQuery read_road();
    QSqlQuery read_line();
    QSqlQuery read_building();
    QSqlQuery search_building(QString); // 模糊查找建筑物进行匹配



};

#endif // GPS_SQL_READ_H
