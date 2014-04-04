#ifndef GPSMAP_H
#define GPSMAP_H
#include"Gps_line.h"
#include"Gps_point.h"
#include"Gps_road.h"
#include"Gps_building.h"
#include<vector>
#include<set>
#include<QDebug>
using namespace std;
class Gps_map
{
    public:
    set<Gps_point,Compare> point_set;
    vector<Gps_Line> line_vector;
    vector<Gps_point> point_vector;
    vector<Gps_road> road_vector;
    vector<bool> b;
    vector<Gps_building> build_vector;
    void read_file(char path[],int level);
    void read_build(char path[]);
    void read_shp(char shaName[]);
    void OnReadPointSh(FILE * m_ShpFile_fp);
    void InitDbf(char * DbfFileName);
    FILE*   m_DbfFile_fp;       //****Dbf ???t????
    int len[100],sum;
    int fieldscount;
    int color;
    int class_type;
    void OnReadLineShp(FILE *m_ShpFile_fp,int level);
    unsigned long OnChangecharOrderWY (unsigned int indata);
    int create_point(double xx,double yy);
    bool OnReadDbf();
    bool OnReadDbf_build();
    static char road_name[10000][255];
    static int road_num;
    void create_road();
    void create_line(int beforep,int nowp,int level);
    void find_road(int line_id);
    Gps_map();
    char building_name[255];
};
#endif
