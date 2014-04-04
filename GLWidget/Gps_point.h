#ifndef GPSPOINT_H
#define GPSPOINT_H
#include<vector>
using namespace std;
class Gps_point
{
    public:
        int ID;
        double x,y;
        vector<int> lines_id;
    Gps_point(int id,double x,double y);
	void add_line(int id);
};
#endif
