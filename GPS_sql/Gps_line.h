#ifndef GPSLINE_H
#define GPSLINE_H
class Gps_Line
{

    public:
        int ID;
        int Begin_point_id,End_point_id;
        int Road_section_id,Road_level;
		bool be_choice;
		int brother_id;
		char * road_name;
    Gps_Line(int id,int bp_id,int ep_id,int rs_id,int r_level);
};
#endif
