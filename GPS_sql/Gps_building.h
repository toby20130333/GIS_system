#ifndef GPSBUILDING_H
#define GPSBUILDING_H
class Gps_building
{
public:
	int ID;
	char name[255];
	int class_type;
	double x,y;
	static int count;
	Gps_building(char n[],int c,double x,double y);
};
#endif