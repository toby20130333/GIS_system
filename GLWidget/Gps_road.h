#ifndef GPSROAD_H
#define GPSROAD_H
#include<QString>
using namespace std;
class Gps_road
{
    public:
        int ID;
        QString name;
        int rule;
        int highest_limit,lowerst_limit;
    Gps_road(int id,QString n,int r,int h_l,int l_l);
};
#endif
