#ifndef MYSQL_H
#define MYSQL_H
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


class MySQL
{
public:
    QSqlDatabase database;
    MySQL();
    ~MySQL();
     void init();
};

#endif // MYSQL_H
