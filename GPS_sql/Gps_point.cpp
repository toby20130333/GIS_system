#include"Gps_point.h"
#include<cmath>
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
bool Compare::operator()(const Gps_point a, const Gps_point b) const
{
   if (fabs(a.x-b.x)>min_limit) return a.x<b.x;
   if (fabs(a.y-b.y)>min_limit) return a.y<b.y;
    return false;
}



