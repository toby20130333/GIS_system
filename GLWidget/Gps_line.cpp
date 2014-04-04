#include"Gps_line.h"
Gps_Line::Gps_Line(int id,int bp_id,int ep_id,int rs_id,int r_level)
{
    ID=id;
    Begin_point_id=bp_id;
    End_point_id=ep_id;
    Road_section_id=rs_id;
    Road_level=r_level;
	be_choice=false;
}
