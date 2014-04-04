#ifndef GPSPOINT_H
#define GPSPOINT_H
#include<vector>
using namespace std;
#define min_limit 0.0001
class Gps_point
{
    public:
        int ID;
        double x,y;
        vector<int> lines_id;
    Gps_point(int id,double x,double y);
	void add_line(int id);
};
class Compare
{
    public:
   bool operator ()(const Gps_point a, const Gps_point b) const;
};
#endif
