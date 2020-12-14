#ifndef MYSQL_H
#define MYSQL_H
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>


class MySQL
{
public:
    QSqlDatabase database;
    MySQL();
    ~MySQL();
     void init();
     bool add_user(QString name,QString passwd,QString is_admin);
     QString get_user_passwd(QString username);
};

#endif // MYSQL_H
