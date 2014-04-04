#ifndef GPS_MAP_H
#define GPS_MAP_H
#include "gps_sql_read.h"
#include "Gps_line.h"
#include "Gps_point.h"
#include "Gps_road.h"
#include "Gps_building.h"
#include "PublicValue.h"

#include<vector>

using namespace std;

class Gps_map
{
public:
    Gps_map();
    Gps_sql_read sql_read;
    vector<Gps_Line> line_vector;
    vector<Gps_point> point_vector;
    vector<Gps_road> road_vector;
    vector<Gps_building> building_vector;
    void read_point();
    void read_road();
    void read_line();
    void read_building();
    double Max_x,Min_x,Max_y,Min_y;
};

#endif // GPS_MAP_H
