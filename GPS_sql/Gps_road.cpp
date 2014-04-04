#include"Gps_road.h"
#include<cstdio>
Gps_road::Gps_road(int id,char* n,int r,int h_l,int l_l)
{
    ID=id;
    name=n;
   // printf ("%s\n",name);
    rule=r;
    highest_limit=h_l;
    lowerst_limit=l_l;
}
