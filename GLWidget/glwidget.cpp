#include "glwidget.h"
#include "ui_glwidget.h"

#include <QtGui>
#include <QtCore>
#include<QDebug>
#include <GL/GLU.h>
//#include <GL/glut.h>
#include <QtDebug>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
GLWidget::GLWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::GLWidget)
{
    ui->setupUi(this);

    this->setMouseTracking( true);

    fullscreen = false;
    setGeometry(500, 100, 940, 480);
    rTri = 0.0f;
    Movex = 0.0f;
    Movey = 0.0f;
    Scalez = -(MAXX-0.01); //初始化为地图的全景样子，所以，Scalez设置为最远处
                    //the value is equal to normal view)
    LineWidth = 0.6f;
    fovy = 45;
    height = tan((fovy/2)/180*PI)*(MAXX-0.01)*2;//
    find_best_road = false;
    from_id=to_id = -1;
    focusx=focusy = 0;
}

void GLWidget::run()
{

}

void GLWidget::getScreenInfo()  //Get this computer's resolution
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    g_nActScreenW = screenRect.width();
    g_nActScreenH = screenRect.height();
}

void GLWidget::getCurWinInfo()
{
    QSize s = this->size();
    g_curH = s.height();
    g_curW=s.width();
}

void GLWidget::initializeGL()  //initialize
{
    // setGeometry(300, 100, 640, 480);

    glShadeModel(GL_SMOOTH);//Set shadow and smooth mode
    glClearColor(0.953,0.949,0.934,0.887);
    glClearDepth(1.0f);//Set depth cache
    glEnable(GL_DEPTH_TEST);//allow depth test
    glDepthFunc(GL_LEQUAL);//Set depth test type
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//Perspective correction
}

void GLWidget::resizeGL(int width, int height)
{
    if(0 == height)
           height = 1;//防止一条边为0

    glViewport(0, 0, (GLint)width, (GLint)height);//重置当前视口，本身不是重置窗口的，只不过是这里被Qt给封装好了
    glMatrixMode(GL_PROJECTION);//选择投影矩阵
    glLoadIdentity();//重置选择好的投影矩阵
    gluPerspective(fovy, (GLfloat)width/(GLfloat)height, 0.5, 100.0);//建立透视投影矩阵，坐标轴高度的计算公式为tan((fovy/2)/180*PI)*scaleZ
    glMatrixMode(GL_MODELVIEW);//以下2句和上面出现的解释一样
    glLoadIdentity();

}

void GLWidget::resizeEvent(QResizeEvent *e)
{
    QRect r=this->geometry();
   // QRect r=this->geometry();
   // qDebug()<<r.height()<<"   ||  "<<r.width();

    g_curH = r.height();
    g_curW=r.width();
}

/**********************************************/
/*               Paint Map                    */
/**********************************************/

void GLWidget::paintGL()
{

    //qDebug()<<height;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

    glRotatef(rTri, 0.0f, 0.0f, 1.0f);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(0,0,Scalez);
    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    glVertex3f(focusx, focusy, Scalez);
    glEnd();

    for (int i=0;i<map->line_vector.size();++i)
    {
        DrawLine(i,1);
    }

    int  t = from_id;
    if (find_best_road == true)
        while (al->after_line[t] != -2)
        {
            DrawLine(al->after_line[t],2);
            DrawDirect(al->after_line[t]);

            t = al->map->line_vector[al->after_line[t]].End_point_id;
        }
    if (from_id != -1)
    {
        glColor3f(0.5,0.5,0);
        DrawPoint(from_id);
    }

    if (to_id != -1)
    {
        glColor3f(0.5,0,0.5);
        DrawPoint(to_id);
    }
}

int GLWidget::find_point()
{
    double x=(-Movex/height+div/2)*(map->Max_y-map->Min_y)+map->Min_x;
    double y=(-Movey/height+0.5)*(map->Max_y-map->Min_y)+map->Min_y;

    return al->find_point(x,y);
}

void GLWidget::to_here(double x, double y,int choice)
{
    double xx1;
    double yy1;

    xx1 = (x - map->Min_x)/(map->Max_y - map->Min_y);
    yy1 = (y - map->Min_y)/(map->Max_y - map->Min_y);
    Movex = -(xx1-div/2)*height;
    Movey = -(yy1-0.5)*height;

    switch(choice)
    {
        case 0:al->from_id = from_id = find_point();
            find_best_road = false;
            break;
        case 1:al->to_id = to_id = find_point();
            find_best_road = false;
            break;
    }
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    float w= Scalez * (-0.03);

    switch(e->key())
    {
        //F1: choose full Screen or normal Screen
        case Qt::Key_F1:
            fullscreen = !fullscreen;
            if(fullscreen)
                showFullScreen();
            else
            {
                setGeometry(100, 100, 640, 480);
                showNormal();
            }
            updateGL();
            break;

    case Qt::Key_Right:  // Turn right
        Movex += w*RADSIN(rTri - 90);
        Movey += w*RADCOS(rTri - 90);
        this->updateGL();
        break;

    case Qt::Key_Left:  //Turn left
        Movex -= w*RADSIN(rTri - 90);
        Movey -= w*RADCOS(rTri - 90);
        this->updateGL();
        break;

    case Qt::Key_Up:  // Turn up
         Movex -= w*RADSIN(rTri);
         Movey -= w*RADCOS(rTri);
        this->updateGL();
        break;

    case Qt::Key_Down:   // Turn down
         Movex += w*RADSIN(rTri);
         Movey += w*RADCOS(rTri);
        this->updateGL();
        break;

    case Qt::Key_F2:  // Zoom out
        Scalez /= 1.2f;
        if(Scalez > -0.5)
            Scalez = -0.5;
        this->updateGL();
        break;
    case Qt::Key_F3:    //Zoom in
        Scalez *= 1.2f;
        if(Scalez < (-(MAXX-0.01)))
            Scalez = (-(MAXX-0.01));
        this->updateGL();
        break;
     case Qt::Key_F4:
        rTri += 2.0f;
        if (rTri > 360)
        {
            rTri -= 360;
        }

        this->updateGL();
        break;
    case Qt::Key_F5:
        rTri -= 2.0f;
        if (rTri <0)
        {
            rTri += 360;
        }

        this->updateGL();
        break;
    case Qt::Key_F6:
        find_best_road = false;
        from_id = find_point();
        al->from_id = from_id;

        this->updateGL();
        break;
    case Qt::Key_F7:
        find_best_road = false;
        to_id = find_point();
        al->to_id = to_id;

        this->updateGL();
        break;
    case Qt::Key_F8:
        path_find();
        break;
    case Qt::Key_Escape:   //Quit program
            close();

    }

}

void GLWidget::path_find()
{
    find_best_road = al->find_best_road(from_id, to_id);
    if (find_best_road == true)
    {
        to_here(map->point_vector[from_id].x, map->point_vector[from_id].y, -1);

        const Gps_Line &l=map->line_vector[al->after_line[from_id]];
        const Gps_point &from=map->point_vector[l.Begin_point_id];
        const Gps_point & to=map->point_vector[l.End_point_id];

        rTri = -atan((to.y-from.y)/(to.x-from.x))*180/PI-90;
    }
    this->updateGL();
}

QList<QString> GLWidget::getLoadTxt()
{
    if(al != NULL)
    {
       return al->roadlst;
    }
}

/**********************************************/
/*                 Mouse Event                */
/**********************************************/
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    //mousehandle();
    if (event->button() == Qt::LeftButton)  //Rotate if you enter leftButton
    {
        double x = ((focusx - Movex)/height + div/2)*(map->Max_y - map->Min_y)
                + map->Min_x;
        double y = ((focusy - Movey)/height+0.5)*(map->Max_y - map->Min_y)
                + map->Min_y;

        qDebug()<<"focus "<<focusx<<"   "<<focusy;

        qDebug()<<x<<"   "<<y;

        to_id=al->find_point(x,y);
        QString x1 = QString::number(x, 'f', 2);
        QString y1 = QString::number(y, 'f', 2);
        QString str_search = "select * from building where X like '%" + x1 + "%'"+" and Y like '%"+y1+"%'";
        QSqlQuery query_search_building;
        query_search_building =  map->sql_read.search_building(str_search);
        search_begin.clear();
        while (query_search_building.next())
        {
            // QString str_result = query_search_building.value(0).toString();
             Gps_building b(query_search_building.value(0).toInt(),query_search_building.value(1).toString(),
             query_search_building.value(2).toInt(),query_search_building.value(3).toDouble(),
                         query_search_building.value(4).toDouble());
             search_begin.push_back(b);
        }
        QStringList lst;
        lst.clear();
        qDebug() <<"BEGIN_POINT name "<<search_begin.size()<<"\n"<<str_search;
        for (int i = 0; i < search_begin.size(); i++)
        {
            const Gps_building& b = search_begin[i];
            lst.append(b.name);
            qDebug() <<"BEGIN_POINT name "<<b.name;
            //ui->comboBox_begin->addItem(b.name);
        }
        emit signalSendLocation(lst);
    }
}

void GLWidget::DrawPoint(int id)
{
    double xx1;
    double yy1;

    xx1 = (map->point_vector[id].x - map->Min_x)/(map->Max_y - map->Min_y);
    yy1 = (map->point_vector[id].y - map->Min_y)/(map->Max_y - map->Min_y);

    glBegin(GL_POINTS);
    glVertex3f((xx1-div/2)*height+Movex, (yy1-0.5)*height+Movey, Scalez);
    glEnd();
}

void GLWidget::mousehandle()
{
    rTri += 2.0f;
    if (rTri > 360)
    {
        rTri -= 360;
    }
    this->updateGL();
}
/*****************end of mouse event***************/

void GLWidget::set_map(Gps_map *m)
{
    map = m;
    div=(map->Max_x-map->Min_x)/(map->Max_y-map->Min_y);
}

void GLWidget::set_al(Gps_algorithm *a)
{
    al = a;
}

void GLWidget::DrawDirect(int line_id)
{
    double len = 0.02;
    Gps_Line &l = map->line_vector[line_id];
    double w = 100.0/l.Road_level/-Scalez;
    if (w < 8)
       return;
    glColor3f(1, 1, 1);
    glLineWidth(3);
    glBegin(GL_LINES);
    double begin_x;
    double begin_y;
    double end_x;
    double end_y;
    double xx1;
    double xx2;
    double yy1;
    double yy2;
    double x1;
    double x2;
    double y1;
    double y2;
    double d = 1.0/3;

    begin_x = (map->point_vector[l.Begin_point_id].x - map->Min_x)/(map->Max_y
                                                                    - map->Min_y);
    begin_y = (map->point_vector[l.Begin_point_id].y - map->Min_y)/(map->Max_y
                                                                    - map->Min_y);
    end_x = (map->point_vector[l.End_point_id].x - map->Min_x)/(map->Max_y
                                                                - map->Min_y);
    end_y = (map->point_vector[l.End_point_id].y - map->Min_y)/(map->Max_y
                                                                - map->Min_y);
    xx2 = (begin_x - div/2)*height;
    yy2 = (begin_y - 0.5)*height;
    xx1 = (end_x - div/2)*height;
    yy1 = (end_y - 0.5)*height;

    double sq = sqrt((xx1-xx2)*(xx1-xx2)+(yy1-yy2)*(yy1-yy2));

    x2 = xx2;
    y2 = yy2;
    x1 = x2 - (xx2-xx1)/sq*len;
    y1 = y2 - (yy2-yy1)/sq*len;

    glVertex3f(x1+Movex, y1+Movey, Scalez);
    glVertex3f(x2+Movex, y2+Movey, Scalez);
    glVertex3f((x2-x1)*d+x1-d*(y2-y1)*0.5+Movex, (y2-y1)*d+y1+d*(x2-x1)*0.5
               + Movey, Scalez);
    glVertex3f(x1+Movex, y1+Movey, Scalez);
    glVertex3f((x2-x1)*d+x1+d*(y2-y1)*0.5+Movex, (y2-y1)*d+y1-d*(x2-x1)*0.5
               + Movey, Scalez);
    glVertex3f(x1+Movex, y1+Movey, Scalez);
    glEnd();
}
void GLWidget::DrawLine(int i, int type)
{

    const Gps_Line &l = map->line_vector[i];
    double zz = -Scalez;
    double w = 20.0/l.Road_level/zz;

    glLineWidth(w);

    if (w < 0.1)
        return;
    else
    {
        if (type == 1)
        {
            glColor3f(236.0/255,148.0/255,15.0/255);
            //glColor3f(l.Road_level, l.Road_level, l.Road_level);
        }

        if (type == 2)
        {
            glColor3f(1,0,0);
        }

        glBegin(GL_LINES);

        double xx1;
        double xx2;
        double yy1;
        double yy2;

        xx1 = (map->point_vector[l.Begin_point_id].x - map->Min_x)/(map->Max_y - map->Min_y);
        yy1 = (map->point_vector[l.Begin_point_id].y - map->Min_y)/(map->Max_y - map->Min_y);
        xx2 = (map->point_vector[l.End_point_id].x - map->Min_x)/(map->Max_y - map->Min_y);
        yy2 = (map->point_vector[l.End_point_id].y - map->Min_y)/(map->Max_y - map->Min_y);

        glVertex3f((xx1-div/2)*height+Movex, (yy1-0.5)*height+Movey, Scalez);
        glVertex3f((xx2-div/2)*height+Movex, (yy2-0.5)*height+Movey, Scalez);
        glEnd();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->pos().x();
    int y = e->pos().y();
    float alpha = (rTri)/180*PI;
    double temp_x;
    double temp_y;

    temp_y = -(0.5-(double)y/g_curH)*height/(MAXX-0.01)*Scalez;
    temp_x = -((double)x/g_curH-div/2)*height/(MAXX-0.01)*Scalez;
    focusx = temp_x*cos(alpha) + temp_y*sin(alpha);
    focusy = -temp_x*sin(alpha) + temp_y*cos(alpha);

    updateGL();
}

GLWidget::~GLWidget()
{
    delete ui;
}
