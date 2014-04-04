#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTextCodec>
#include "mainwindow.h"
#include <iostream>
#include"Gps_line.h"
#include"Gps_point.h"
#include"Gps_road.h"
#include"Gps_map.h"
#include<cstdio>
#include<cstring>

using namespace std;

int test_count=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("SYSTEM"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("SYSTEM"));

    Gps_map map;
    map.read_file("一级道路L",1);
    map.read_file("二级道路L",2);
    map.read_file("三级道路L",3);
    map.read_file("四级道路L",4);
    map.create_road();
    map.read_build("城区地物P");
    int i;
    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MyGpsSql.db");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    else
        qDebug() << "Success!";

    //QStringList driverList = QSqlDatabase::drivers();
    //qDebug() << driverList;
    //QSqlQuery query(db);
    QSqlQuery query;//(dbconnet);
    bool ok ;

    query.exec("CREATE TABLE point(ID int primary key, Point_X double, Point_Y double)");
    query.exec("CREATE TABLE building(ID int primary key, Name varchar(30), Building_Type int, X double, Y double)");
    query.exec("CREATE TABLE line(ID int primary key, Begin_Point int, End_point int, Road_Section int, Road_level int)");
    query.exec("CREATE TABLE road(ID int primary key, Road_Name varchar(30), Road_Rule int, Highest_Limit int, Lowest_Limit int)");
    qDebug() << map.point_vector.size();
     for (i=0;i<map.point_vector.size();++i)
     {

             Gps_point  p=map.point_vector[i];
             char str[255];
             sprintf(str,"INSERT INTO point (ID, Point_X, Point_Y) VALUES (%d,%lf,%lf)",p.ID,p.x,p.y);
             qDebug()<< str;
             query.exec(str);
     }
        for (i=0;i<map.road_vector.size();++i)
        {
            Gps_road & r=map.road_vector[i];
            char str[255];
            sprintf(str,"INSERT INTO road (ID,Road_Name,Road_Rule,Highest_Limit,Lowest_Limit) VALUES (%d,'%s',%d,%d,%d)",r.ID,r.name,r.rule,r.highest_limit,r.lowerst_limit);
            qDebug()<<str;
            query.exec(str);
        }
        for (i=0;i<map.line_vector.size();++i)
        {
            Gps_Line & l=map.line_vector[i];
             char str[255];
             sprintf (str,"INSERT INTO line (ID,Begin_Point,End_point,Road_Section,Road_level) VALUES (%d,%d,%d,%d,%d)",l.ID,l.Begin_point_id,l.End_point_id,l.Road_section_id,l.Road_level);
             qDebug()<<str;
             query.exec(str);
             //  printf ("%d %d %d %d %d\n",l.ID,l.Begin_point_id,l.End_point_id,l.Road_level);
        }
          for (i=0;i<map.build_vector.size();++i)
          {
              Gps_building & b=map.build_vector[i];
              char str[255];
              sprintf (str,"INSERT INTO building (ID,Name,Building_Type,X,Y) VALUES (%d,'%s',%d,%lf,%lf)",b.ID,b.name,b.class_type,b.x,b.y);
                qDebug()<<str;
                query.exec(str);
          }

    if (ok)
    {
        qDebug() << "OK";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
