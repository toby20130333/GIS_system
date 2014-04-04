#include "gps_sql_read.h"
#include <QtGui/QApplication>

Gps_sql_read::Gps_sql_read()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("SYSTEM"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("SYSTEM"));

    QApplication::addLibraryPath("./plugins");

    //db= QSqlDatabase::addDatabase("QMYSQL");
    db= QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");
    db.setDatabaseName("MyGpsSql.db");
    //db.setUserName("root");
    //db.setPassword("123456");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    else
        qDebug() << "Success!";
}

QSqlQuery Gps_sql_read::read_point()
{
    QString query_str = "select * from point";
    QSqlQuery sqlQuery(query_str, db);
    sqlQuery.exec();
    return sqlQuery;
}
QSqlQuery Gps_sql_read::read_road()
{
    QString query_str = "select * from road";
    QSqlQuery sqlQuery(query_str, db);
    sqlQuery.exec();
    return sqlQuery;
}

QSqlQuery Gps_sql_read::read_line()
{
    QString query_str = "select * from line";
    QSqlQuery sqlQuery(query_str, db);
    sqlQuery.exec();
    return sqlQuery;
}
QSqlQuery Gps_sql_read::read_building()
{
    QString query_str = "select * from building";
    QSqlQuery sqlQuery(query_str, db);
    sqlQuery.exec();
    return sqlQuery;

}

QSqlQuery Gps_sql_read::search_building(QString str)
{
    QSqlQuery query_search_building;
    query_search_building.exec(str);

    return query_search_building;


}

