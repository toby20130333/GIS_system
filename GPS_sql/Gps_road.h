#ifndef GPSROAD_H
#define GPSROAD_H
#include<string>
using namespace std;
class Gps_road
{
    public:
        int ID;
        char * name;
        int rule;
        int highest_limit,lowerst_limit;
    Gps_road(int id,char * n,int r,int h_l,int l_l);

};
#endif
