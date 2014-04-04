#include"Gps_map.h"
#include<cstring>
#include<cstdio>
#include<QDebug>
//int test_count=0;
 Gps_map::Gps_map()
{
    color=0;
}
void Gps_map::read_build(char path[])
{
    char shp[255],dbf[255];
        strcpy(shp,path);
        strcat(shp,".shp");
            strcpy(dbf,path);
        strcat(dbf,".dbf");
        qDebug()<<"dbf" <<dbf;
        InitDbf(dbf);
        read_shp(shp);
}
void Gps_map::read_shp(char shpName[])
{
    FILE *m_ShpFile_fp;
    if((m_ShpFile_fp=fopen(shpName,"rb"))==NULL)
    {
          return;
    }


       int i,j;
       int FileCode;
       int Unused;
       int FileLength;
       int Version;
       int Shapechar;
       double Xmin;
       double Ymin;
       double Xmax;
       double Ymax;
       double Zmin;
       double Zmax;
       double Mmin;
       double Mmax;
       fread(&FileCode,sizeof(int),1,m_ShpFile_fp);
       for(i=0;i<5;i++)
           fread(&Unused,sizeof(int),1,m_ShpFile_fp);
       fread(&FileLength,sizeof(int),1,m_ShpFile_fp);
       fread(&Version,sizeof(int),1,m_ShpFile_fp);
       fread(&Shapechar,sizeof(int),1,m_ShpFile_fp);
       fread(&Xmin,sizeof(double),1,m_ShpFile_fp);
       fread(&Ymin,sizeof(double),1,m_ShpFile_fp);
       fread(&Xmax,sizeof(double),1,m_ShpFile_fp);
       fread(&Ymax,sizeof(double),1,m_ShpFile_fp);
       fread(&Zmin,sizeof(double),1,m_ShpFile_fp);
       fread(&Zmax,sizeof(double),1,m_ShpFile_fp);
       fread(&Mmin,sizeof(double),1,m_ShpFile_fp);
       fread(&Mmax,sizeof(double),1,m_ShpFile_fp);
       printf ("char=%d x=%lf y=%lf\n",Shapechar,Xmin,Ymin);
       switch(Shapechar)
       {
           case 1:OnReadPointSh(m_ShpFile_fp);break;
          // case 3:OnReadLineShp(m_ShpFile_fp,level);break;
       }

       fclose(m_ShpFile_fp);
}
void Gps_map::OnReadPointSh(FILE *m_ShpFile_fp)
{
    int count=0,c=0;
        int w;
        int RecordNumber;
        int ContentLength;
        int num=0;
        while((fread(&RecordNumber,    sizeof(int),   1,m_ShpFile_fp)!=0))
        {
            num++;
            fread(&ContentLength,sizeof(int),   1,m_ShpFile_fp);
            RecordNumber= OnChangecharOrderWY (RecordNumber);
            ContentLength = OnChangecharOrderWY (ContentLength);
            int shapechar;
            double x;double y;
            fread(&shapechar, sizeof(int),   1,m_ShpFile_fp);
            fread(&x, sizeof(double),   1,m_ShpFile_fp);
            fread(&y, sizeof(double),   1,m_ShpFile_fp);
            OnReadDbf_build();
            printf ("%d %s %d %lf %lf\n",RecordNumber,building_name,class_type,x,y);
            build_vector.push_back( Gps_building(building_name,class_type,x,y));

        }
}
void Gps_map::read_file(char path[],int level)
{
    FILE*   m_ShpFile_fp;
    char shpName[256]="",dbfName[256]="";
    strcat(shpName,path);
    strcat(shpName,".shp");
    strcat(dbfName,path);
    strcat(dbfName,".dbf");
    if((m_ShpFile_fp=fopen(shpName,"rb"))==NULL)
    {
        return;
    }
    InitDbf(dbfName);
    int i,j;
    int FileCode;
    int Unused;
    int FileLength;
    int Version;
    int Shapechar;
    double Xmin;
    double Ymin;
    double Xmax;
    double Ymax;
    double Zmin;
    double Zmax;
    double Mmin;
    double Mmax;
    fread(&FileCode,sizeof(int),1,m_ShpFile_fp);
    for(i=0;i<5;i++)
        fread(&Unused,sizeof(int),1,m_ShpFile_fp);
    fread(&FileLength,sizeof(int),1,m_ShpFile_fp);
    fread(&Version,sizeof(int),1,m_ShpFile_fp);
    fread(&Shapechar,sizeof(int),1,m_ShpFile_fp);
    fread(&Xmin,sizeof(double),1,m_ShpFile_fp);
    fread(&Ymin,sizeof(double),1,m_ShpFile_fp);
    fread(&Xmax,sizeof(double),1,m_ShpFile_fp);
    fread(&Ymax,sizeof(double),1,m_ShpFile_fp);
    fread(&Zmin,sizeof(double),1,m_ShpFile_fp);
    fread(&Zmax,sizeof(double),1,m_ShpFile_fp);
    fread(&Mmin,sizeof(double),1,m_ShpFile_fp);
    fread(&Mmax,sizeof(double),1,m_ShpFile_fp);
    OnReadLineShp(m_ShpFile_fp,level);
}
void  Gps_map::InitDbf(char * DbfFileName)
{
           // 打开 dbf 文件
       if((m_DbfFile_fp=fopen(DbfFileName,"rb"))==NULL)
       {
              return;
       }
       int i,j;
       //////**** 读取 dbf 文件的文件头  开始
       char version;
       fread(&version,     1,   1,m_DbfFile_fp);

       char date[3];
       for(i=0;i<3;i++)
       {
              fread(date+i,     1,   1,m_DbfFile_fp);
       }
       int RecordNum;            //******
       fread(&RecordNum,         sizeof(int),   1,m_DbfFile_fp);
       printf ("%d\n",RecordNum);
       short HeadercharNum;
       fread(&HeadercharNum, sizeof(short), 1,m_DbfFile_fp);
        printf ("%d\n",HeadercharNum);
       short RecordcharNum;
       fread(&RecordcharNum, sizeof(short), 1,m_DbfFile_fp);
         printf ("%d\n",RecordcharNum);

       short Reserved1;
       fread(&Reserved1,    sizeof(short), 1,m_DbfFile_fp);
        printf ("%d\n",Reserved1);
       char Flag4s;
       fread(&Flag4s,                 sizeof(char), 1,m_DbfFile_fp);
         printf ("%d\n",Flag4s);
       char EncrypteFlag;
       fread(&EncrypteFlag,            sizeof(char), 1,m_DbfFile_fp);
         printf ("%d\n",EncrypteFlag);
        int Unused;
       for(i=0;i<3;i++)
       {
              fread(&Unused,        sizeof(int),   1,m_DbfFile_fp);
       }
       char MDXFlag;
       fread(&MDXFlag,    sizeof(char), 1,m_DbfFile_fp);
        printf ("%d\n",MDXFlag);

       char LDriID;
       fread(&LDriID,                sizeof(char), 1,m_DbfFile_fp);
        printf ("%d\n",LDriID);
       short Reserved2;
       fread(&Reserved2,    sizeof(short), 1,m_DbfFile_fp);
       char name[11];
       char fieldchar;
       int Reserved3;
       char fieldLength;
       char decimalCount;
       short Reserved4;
       char workID;
       short Reserved5[5];
       char mDXFlag1;

       fieldscount = (HeadercharNum - 32) / 32;
       // 读取记录项信息－共有 8 个记录项
       for(i=0;i< fieldscount;i++)
       {
              //FieldName----11   chars
              fread(name,    11, 1,m_DbfFile_fp);
              printf ("%s\n",name);
              //Fieldchar----1     chars
              fread(&fieldchar,   sizeof(char), 1,m_DbfFile_fp);
               printf ("%c\n",fieldchar);
              //Reserved3----4     chars
              Reserved3      =0;
              fread(&Reserved3, sizeof(int), 1,m_DbfFile_fp);
              //FieldLength--1     chars
              fread(&fieldLength,sizeof(char), 1,m_DbfFile_fp);
               printf ("%d\n",fieldLength);
               len[i]=fieldLength;
               sum+=len[i];
              //DecimalCount-1   chars
              fread(&decimalCount,sizeof(char), 1,m_DbfFile_fp);
                printf ("%d\n",decimalCount);
              //Reserved4----2     chars
              Reserved4      =0;
              fread(&Reserved4, sizeof(short), 1,m_DbfFile_fp);
              //WorkID-------1    chars
              fread(&workID,            sizeof(char), 1,m_DbfFile_fp);
              //Reserved5----10   chars
              for(j=0;j<5;j++)
              {
                     fread(Reserved5+j,sizeof(short), 1,m_DbfFile_fp);
              }
              //MDXFlag1-----1 chars
              fread(&mDXFlag1,       sizeof(char), 1,m_DbfFile_fp);
          printf ("%d\n",mDXFlag1);
       }
       char terminator;
       fread(&terminator,sizeof(char), 1,m_DbfFile_fp);       // 读取 dbf 文件头结束

}
unsigned long Gps_map::OnChangecharOrderWY (unsigned int indata)
{
   int ans=0;
   for (int i=0;i<4;++i)
   {
        ans<<=8;
       ans|=(indata&255);
       indata>>=8;
   }

    return ans;
}
char Gps_map::road_name[10000][255];
int Gps_map::road_num=0;
bool Gps_map::OnReadDbf_build()
{
    char ch[256];
         int count=0;
         int num;
         int i,j,index=0;
            for (i=0;i<fieldscount;++i)
            {
                 index=0;
                for ( j=0;j<len[i];++j)
                {
                  if (fread(&ch[index],sizeof(char),1,m_DbfFile_fp)!=sizeof(char)) return false;
                 if (ch[index]!=32) index++;
                }
                ch[index]=0;
                qDebug()<<ch;
                if (i==0)  strcpy(building_name,ch);
                if (i==1) class_type=atoi(ch);
                // printf ("%s|",ch);

                //     printf ("%d\n",road_num);

            }
             fread(&ch[j],sizeof(char),1,m_DbfFile_fp);
             class_type=class_type*10+ch[j]-'0';

             // if (ch[j]!=32) qDebug()<<"c++"<<ch[j];
}
bool  Gps_map::OnReadDbf()
{
        char ch[256];
        int count=0;
        int num;
        int i,j;
		int index=0;
           for (i=0;i<fieldscount;++i)
           {
				index=0;
               for ( j=0;j<len[i];++j)
               {
                    if (fread(&ch[index],sizeof(char),1,m_DbfFile_fp)!=sizeof(char)) return false;
					if (ch[index]!=32) index++;
			   }
               ch[index]=0;

           //     printf ("%d\n",road_num);
                strcpy(Gps_map::road_name[Gps_map::road_num++],ch);
           }
            fread(&ch[j],sizeof(char),1,m_DbfFile_fp);
        //  if (be_choice) printf ("\n");

}
int Gps_map::create_point(double xx,double yy)
{
     pair< set<Gps_point>::iterator,bool> pa;
     Gps_point p(point_vector.size(),xx,yy);
    pa=point_set.insert(p);
    if (pa.second) {point_vector.push_back(p);}
    //printf ("point_num=%d\n",(*(pa.first)).ID);
    return (*(pa.first)).ID;
}
void Gps_map::create_line(int beforep,int nowp,int level)
{
     Gps_Line l1(line_vector.size(),beforep,nowp,-1,level);
    l1.road_name=road_name[road_num-1];
    //printf ("%s\n",l1.road_name);
    line_vector.push_back(l1);
    b.push_back(false);
    point_vector[beforep].add_line(l1.ID);
    Gps_Line l2(line_vector.size(),nowp,beforep,-1,level);
    l2.road_name=road_name[road_num-1];
    point_vector[nowp].add_line(l2.ID);
    line_vector.push_back(l2);
    line_vector[l1.ID].brother_id=l2.ID;
    line_vector[l2.ID].brother_id=l1.ID;
}
void Gps_map::OnReadLineShp(FILE * m_ShpFile_fp,int level)
{
    int i,j;

        int RecordNumber;
       int ContentLength;
       int num   =0;
       int beforep,nowp;
       while((fread(&RecordNumber,    sizeof(int),   1,m_ShpFile_fp)!=0))
       {
              fread(&ContentLength,sizeof(int),   1,m_ShpFile_fp);
              RecordNumber      = OnChangecharOrderWY (RecordNumber);
            OnReadDbf();

              ContentLength       = OnChangecharOrderWY (ContentLength);
              int shapechar;
              double Box[4];
              int NumParts;
              int NumPoints;
              int *Parts;
              fread(&shapechar,    sizeof(int),   1,m_ShpFile_fp);   // 读 Box
              for( i=0;i<4;i++)
                     fread(Box+i,     sizeof(double),1,m_ShpFile_fp);   // 读 NumParts 和 NumPoints
              fread(&NumParts,     sizeof(int),   1,m_ShpFile_fp);
              fread(&NumPoints,    sizeof(int),   1,m_ShpFile_fp);   // 读 Parts 和 Points
              Parts   = new int[NumParts];
              for(i=0;i<NumParts;i++)
                {
                    fread(Parts+i,   sizeof(int),   1,m_ShpFile_fp);
                }

              int pointNum;

              for(i=0;i<NumParts;i++)
              {
                     if(i!=NumParts-1)
                            pointNum       =Parts[i+1]-Parts[i];
                     else
                            pointNum       =NumPoints-Parts[i];
                     double *PointsX;
                     double *PointsY;

                     PointsX =new double[pointNum];
                     PointsY =new double[pointNum];
                     for(j=0;j<pointNum;j++)
                     {
                            fread(PointsX+j, sizeof(double),1,m_ShpFile_fp);
                            fread(PointsY+j, sizeof(double),1,m_ShpFile_fp);
                       // printf ("point%d x=%lf y=%lf\n",j,PointsX[j],PointsY[j]);
                        beforep=nowp;
                        nowp=create_point(PointsX[j],PointsY[j]);
                        if (i!=0 || j!=0)
                        {
                           create_line(beforep,nowp,level);

                           b.push_back(false);

                          //  printf ("%d %d %d %d\n",l.ID,l.Begin_point_id,l.End_point_id,l.Road_level);
                          //  Gps_edge::create_edge(beforei,nowi,map_num,level,be_choice,Gps_map::road_name[road_num-1]);
                        }
                     }
                     delete[] PointsX;
                     delete[] PointsY;
              }
              delete[] Parts;
       }
}
void Gps_map::find_road(int line_id)
{
    if (line_id==2 || line_id==0) qDebug()<<color-1;
    if (b[line_id]==true) return;
    b[line_id]=true;
   // test_count++;
    line_vector[line_id].Road_section_id=color;
    int now_line_id=line_id;

        int from_point_id=line_vector[line_id].Begin_point_id;
        int to_point_id=line_vector[line_id].End_point_id;
      //  printf ("from=%d to=%d\n",from_point_id,to_point_id);
        if (point_vector[from_point_id].lines_id.size()==2)
        {
            for (int j=0;j<2;++j)
            {
                int line_id=point_vector[from_point_id].lines_id[j];
                if (now_line_id!=line_id)
                {//printf ("一:");
                find_road(line_vector[line_id].brother_id);
                }
            }
        }
        if (point_vector[to_point_id].lines_id.size()==2)
        {
                 for (int j=0;j<2;++j)
            {
                int line_id=point_vector[to_point_id].lines_id[j];
                if (line_vector[now_line_id].brother_id!=line_id)
                {
                 //   printf ("二:");
                    find_road(line_id);
                }
            }

        }


}
void Gps_map::create_road()
{
    int i,j;

    for (i=0;i<line_vector.size();++i)
    {
        if (b[i]==false)
        {
          //  test_count=0;
           // printf ("%s\n",line_vector[i].road_name);
            road_vector.push_back(Gps_road(color,line_vector[i].road_name,0,40,80));
            //printf ("color=%d\n",color);
            find_road(i);
            color++;
        }
    }
}
