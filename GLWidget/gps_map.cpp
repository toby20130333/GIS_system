#include "gps_map.h"

Gps_map::Gps_map()
{
    Max_x = -MAXNUM;
    Max_y = -MAXNUM;
    Min_x = MAXNUM;
    Min_y = MAXNUM;
}

void Gps_map::read_point()
{
    QSqlQuery sqlQuery = sql_read.read_point();

    while (sqlQuery.next())
    {
        Gps_point p(sqlQuery.value(0).toInt(),sqlQuery.value(1).toFloat(),
                    sqlQuery.value(2).toFloat());
        if (p.x > Max_x)
            Max_x = p.x;
        if (p.x < Min_x)
            Min_x = p.x;
        if (p.y > Max_y)
            Max_y = p.y;
        if (p.y < Min_y)
            Min_y = p.y;

        point_vector.push_back(p);
    }
}

void Gps_map::read_road()
{
      QSqlQuery sqlQuery = sql_read.read_road();

      while (sqlQuery.next())
      {
          Gps_road r(sqlQuery.value(0).toInt(), sqlQuery.value(1).toString(),
                     sqlQuery.value(2).toInt(), sqlQuery.value(3).toInt(),
                     sqlQuery.value(4).toInt());

          road_vector.push_back(r);
      }
}

void Gps_map::read_line()
{
     QSqlQuery sqlQuery = sql_read.read_line();

     while (sqlQuery.next())
     {
         Gps_Line l(sqlQuery.value(0).toInt(), sqlQuery.value(1).toInt(),
                    sqlQuery.value(2).toInt(), sqlQuery.value(3).toInt(),
                    sqlQuery.value(4).toInt());

         point_vector[l.Begin_point_id].lines_id.push_back(l.ID);
         line_vector.push_back(l);
     }
}

void Gps_map::read_building()
{
    QSqlQuery sqlQuery = sql_read.read_building();
    while (sqlQuery.next())
    {
        Gps_building b(sqlQuery.value(0).toInt(), sqlQuery.value(1).toString(),
                       sqlQuery.value(2).toInt(), sqlQuery.value(3).toDouble(),
                       sqlQuery.value(4).toDouble());
        building_vector.push_back(b);
    }
}

