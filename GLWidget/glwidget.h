#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <QWidget>
#include <QString>
#include"PublicValue.h"
//#include <QtOpenGL>
#include"gps_map.h"
#include"Gps_algorithm.h"
namespace Ui {
class GLWidget;
}

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QGLWidget *parent = 0);
    ~GLWidget();
    Gps_map * map;
    Gps_algorithm * al;
    vector <Gps_building> search_begin,search_end;

    void set_al(Gps_algorithm * a);
    void set_map(Gps_map * m);
    void DrawLine(int i,int type);
    void DrawPoint(int id);
    void DrawDirect(int line_id);
    void run();
    void to_here(double x,double y,int choice);

    void path_find();
    QList<QString>  getLoadTxt();
signals:
    void signalSendLocation(QStringList);
protected:
    void getScreenInfo();  //得到当前计算机屏幕的分辨率
    void initializeGL();  //初始化OpenGL窗口部件
    void paintGL();  //绘制整个OpenGL窗口，只要有更新发生，这个函数就会被调用
    void resizeGL(int width, int height); //处理窗口大小变化事件的，参数是新状态下的宽和高
    void keyPressEvent(QKeyEvent *e);  //鼠标处理函数
    void mousePressEvent(QMouseEvent* event);
    void mousehandle();
    void mouseMoveEvent(QMouseEvent *);
    void getCurWinInfo ();
    void resizeEvent(QResizeEvent *);

protected:
    bool fullscreen;  //判断是否全屏的变量
    int g_nActScreenW;  //当前计算机屏幕分辨率宽
    int g_nActScreenH;  //当前计算机屏幕分辨率高
    int g_curW;
    int g_curH;
    double focusx,focusy;
    GLfloat rTri;  //旋转
    float Movex;   //左右移动
    float Movey;   //上下移动
    float Scalez;  //前后移动
    float LineWidth; //设置线的宽度
    float fovy;//可视角度
    double div;//宽高比
    double height;//高度值
    bool find_best_road;
    int from_id,to_id;
    int find_point();
private:
    Ui::GLWidget *ui;
};

#endif // GLWIDGET_H
