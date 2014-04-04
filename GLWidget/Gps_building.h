#ifndef GPSBUILDING_H
#define GPSBUILDING_H
#include<QString>
class Gps_building
{
public:
	int ID;
    QString name;
    int class_type;
	double x,y;
	static int count;
    Gps_building(int id,QString n,int c,double x,double y);
};
#endif
