#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H

#include <QWidget>
#include "gps_map.h"
//#include "gps_sql_read.h"
#include"glwidget.h"
#include <QPaintEvent>
namespace Ui {
    class FirstWidget;
}

class FirstWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FirstWidget(QWidget *parent = 0);
    ~FirstWidget();
    vector<Gps_building> vb;
    void set_map(Gps_map * m);
    vector <Gps_building> search_begin,search_end;
    void set_gl(GLWidget * gl);

    bool canmove;
    QPoint oldPos;
public slots:
    void on_pushButton_search_clicked();
private slots:

    void on_comboBox_begin_currentIndexChanged(int index);

    void on_comboBox_beg_end_currentIndexChanged(int index);

    void on_comboBox_end_currentIndexChanged(int index);

    void on_pushButton_find_road_clicked();

    void slotSettingEndLocation(QStringList);

    void on_pushButton_clicked();

private:
    Ui::FirstWidget *ui;
    Gps_map * map;
    GLWidget * gl_widget;
    int now_point;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // FIRSTWIDGET_H
