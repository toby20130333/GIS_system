#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

unsigned long OnChangeByteOrderWY (unsigned int indata)
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

void OnReadShp(const char * ShpFileName)
{
    FILE*   m_ShpFile_fp;
    if((m_ShpFile_fp=fopen(ShpFileName,"rb"))==NULL)
    {
        return;
    }
    int FileCode;
    int Unused;
    int FileLength;
    int Version;
    int ShapeType;
    double Xmin;
    double Ymin;
    double Xmax;
    double Ymax;
    double Zmin;
    double Zmax;
    double Mmin;
    double Mmax;
      fread(&FileCode,sizeof(int),1,m_ShpFile_fp);
    for(int i=0;i<5;i++)
        fread(&Unused,sizeof(int),1,m_ShpFile_fp);
    fread(&FileLength,sizeof(int),1,m_ShpFile_fp);
    fread(&Version,sizeof(int),1,m_ShpFile_fp);

    fread(&ShapeType,sizeof(int),1,m_ShpFile_fp);
    fread(&Xmin,sizeof(double),1,m_ShpFile_fp);
    fread(&Ymin,sizeof(double),1,m_ShpFile_fp);
    fread(&Xmax,sizeof(double),1,m_ShpFile_fp);
    fread(&Ymax,sizeof(double),1,m_ShpFile_fp);
    fread(&Zmin,sizeof(double),1,m_ShpFile_fp);
    fread(&Zmax,sizeof(double),1,m_ShpFile_fp);
    fread(&Mmin,sizeof(double),1,m_ShpFile_fp);
    fread(&Mmax,sizeof(double),1,m_ShpFile_fp);
  //  printf ("type=%d x=%lf y=%lf\n",ShapeType,Xmin,Ymin);
     int RecordNumber;
       int ContentLength;
       int num   =0;
       while((fread(&RecordNumber,sizeof(int),1,m_ShpFile_fp)!=0))
       {
              num++;
              int i;
              double Box[4];
              int NumParts;
              int NumPoints;
              int *Parts;
              int shapeType;
              fread(&ContentLength,sizeof(int), 1,m_ShpFile_fp);
              RecordNumber= OnChangeByteOrderWY (RecordNumber);
              ContentLength = OnChangeByteOrderWY (ContentLength);
              fread(&shapeType,sizeof(int),1,m_ShpFile_fp);
              //¶ÁBox
              for(i=0;i<4;i++)
                     fread(Box+i,sizeof(double),1,m_ShpFile_fp);
              fread(&NumParts,sizeof(int),1,m_ShpFile_fp);
              fread(&NumPoints,sizeof(int),1,m_ShpFile_fp);
              //¶ÁPartsºÍPoints
              Parts  =new int[NumParts];
              for(i=0;i<NumParts;i++)
                     fread(Parts+i,sizeof(int),1,m_ShpFile_fp);
              int pointNum;
              //printf("countlength=%d,shapeType=%d,numparts=%d,numpoints=%d\n",ContentLength,shapeType,NumParts,NumPoints);
              for(i=0;i<NumParts;i++)
              {
                    if(i!=NumParts-1)
                    pointNum       =Parts[i+1]-Parts[i];
                     else
                    pointNum       =NumPoints-Parts[i];
                     double *PointsX=new double[pointNum];
                     double *PointsY=new double[pointNum];
                     for(int j=0;j<pointNum;j++)
                     {
                            fread(PointsX+j, sizeof(double),1,m_ShpFile_fp);
                            fread(PointsY+j, sizeof(double),1,m_ShpFile_fp);
                           // printf("PointsX=%lf,PointsY=%lf\n",*(PointsX+j),PointsY[j]);
                     }
                     delete[] PointsX;
                     delete[] PointsY;
              }
              delete[] Parts;
              //  printf ("%d  %d %d %lf %lf\n",RecordNumber,ContentLength,shapeType,x,y);
       }
}
