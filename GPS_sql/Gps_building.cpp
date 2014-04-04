#include"Gps_building.h"
#include<cstring>
int Gps_building::count=0;
Gps_building::Gps_building(char n[],int c,double x,double y)
{
	ID=count++;
	strcpy(name,n);
	class_type=c;
	this->x=x;
	this->y=y;
}