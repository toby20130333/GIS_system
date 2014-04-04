#include"Gps_point.h"
Gps_point::Gps_point(int id,double x,double y)
{
    ID=id;
    this->x=x;
    this->y=y;
}
void Gps_point::add_line(int id)
{
	lines_id.push_back(id);
}



