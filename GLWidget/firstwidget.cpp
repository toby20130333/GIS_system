#include "firstwidget.h"
#include "ui_firstwidget.h"
#include <QSqlQuery>

FirstWidget::FirstWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstWidget),canmove(false)
{
    ui->setupUi(this);
    setGeometry(50, 100, 496, 380);
    this->setWindowTitle("寻路指南");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    now_point=0;
}
void FirstWidget::paintEvent(QPaintEvent *)
{
    QPixmap pixmap = QPixmap("D:/demo/GLWidget/images/bg.jpg").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmap);
}

void FirstWidget::mousePressEvent(QMouseEvent *e)
{
    if( (e->pos().x()>= 10) && (e->pos().y()<=45))
    {
        canmove = true;
    }
    else
    {
        canmove = false;
        e->accept();
        return;
    }
    oldPos = e->pos();
    e->accept();
}

void FirstWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(canmove)
    {
        //qDebug()<<this->pos()<<"\n"<<this->y();
        move(e->globalPos() - oldPos);
    }
    e->accept();
}
FirstWidget::~FirstWidget()
{
    delete ui;
}
void FirstWidget::set_gl(GLWidget *gl)
{
    gl_widget=gl;
    connect(gl_widget,SIGNAL(signalSendLocation(QStringList)),this,SLOT(slotSettingEndLocation(QStringList)));
}
void FirstWidget::set_map(Gps_map *m)
{
    map = m;
}
void FirstWidget::on_pushButton_search_clicked()
{
    qDebug()<<"now_point "<<now_point;
    switch(now_point)
    {
        case BEGIN_POINT:
        {
            search_begin.clear();
            ui->comboBox_begin->clear();
            QString str_input = ui->lineEdit_input_road->text();
            QString str_search = "select * from building where Name like '%" + str_input + "%'";
            qDebug() <<"BEGIN_POINT "<<str_search;
            QSqlQuery query_search_building;
            query_search_building =  map->sql_read.search_building(str_search);
            while (query_search_building.next())
            {
                // QString str_result = query_search_building.value(0).toString();
                 Gps_building b(query_search_building.value(0).toInt(),query_search_building.value(1).toString(),
                 query_search_building.value(2).toInt(),query_search_building.value(3).toDouble(),
                             query_search_building.value(4).toDouble());                
                 search_begin.push_back(b);
            }
            qDebug() <<"BEGIN_POINT name "<<search_begin.size();
            for (int i = 0; i < search_begin.size(); i++)
            {
                const Gps_building& b = search_begin[i];
                //qDebug() <<"BEGIN_POINT name "<<b.name;
                ui->comboBox_begin->addItem(b.name);
            }
            break;
        }
        case END_POINT:
        {
            search_end.clear();
            ui->comboBox_end->clear();
            QString str_input = ui->lineEdit_input_road->text();
            QString str_search = "select * from building where Name like '%" + str_input + "%'";
            qDebug()<<str_search;
            QSqlQuery query_search_building;
            query_search_building =  map->sql_read.search_building(str_search);
            while (query_search_building.next())
            {
            // QString str_result = query_search_building.value(0).toString();
                  Gps_building b(query_search_building.value(0).toInt(),query_search_building.value(1).toString(),
                  query_search_building.value(2).toInt(),query_search_building.value(3).toDouble(),
                                 query_search_building.value(4).toDouble());
            search_end.push_back(b);
            }
            for (int i = 0; i < search_end.size(); i++)
            {
                const Gps_building& b = search_end[i];
                ui->comboBox_end->addItem(b.name);
            }
            break;
        }
    }
}

void FirstWidget::on_comboBox_begin_currentIndexChanged(int index)
{
    //qDebug()<<"Change_begin"<<index;
    if(index < 0)
        return;
    if(search_begin.size() ==0)
    {
        return;
    }
    const Gps_building &b = search_begin[index];
    //qDebug() << b.name;

    gl_widget->to_here(b.x,b.y,now_point);
    gl_widget->updateGL();
}

void FirstWidget::on_comboBox_beg_end_currentIndexChanged(int index)
{
    now_point = index;
    qDebug()<<"on_comboBox_beg_end_currentIndexChanged "<<index;
    if(index == 0)
    {
        ui->label_input->setText(QString::fromUtf8("输入起点:"));
    }else{
        ui->label_input->setText(QString::fromUtf8("输入终点:"));
    }
}

void FirstWidget::on_comboBox_end_currentIndexChanged(int index)
{
    qDebug()<<"Change_begin"<<index;
    if (index < 0)
        return;
    if(search_end.size() ==0)
    {
        return;
    }
    const Gps_building &b = search_end[index];

    //qDebug()<<b.name;
    gl_widget->to_here(b.x, b.y, now_point);

    gl_widget->updateGL();
}

void FirstWidget::on_pushButton_find_road_clicked()
{
    if(gl_widget != NULL)
    {
       gl_widget->path_find();
      QList<QString> lst =  gl_widget->getLoadTxt();
      ui->textEdit->clear();
      for(int i=0;i<lst.count();i++)
      {
         ui->textEdit->append(lst.at(i));
         ui->textEdit->append("\n");
      }

    }
}

void FirstWidget::slotSettingEndLocation(QStringList lst)
{
    qDebug()<<"FirstWidget::slotSettingEndLocation "<<lst;
    ui->comboBox_end->clear();
    for(int i=0;i<lst.count();i++)
    {
        ui->comboBox_end->addItem(lst.at(i));
    }
}

void FirstWidget::on_pushButton_clicked()
{
    this->close();
    qApp->quit();
}
