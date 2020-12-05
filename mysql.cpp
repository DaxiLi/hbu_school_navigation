#include "mysql.h"
#include <QFileInfo>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#define DATABASE_FILE_PATH "MyDataBase.db"

MySQL::MySQL()
{
    //数据库不存在则创建数据库
    QFileInfo file(DATABASE_FILE_PATH);
    database = QSqlDatabase::addDatabase("QSQLITE");
    if (!file.isFile()){
        init();
    }
    database.setDatabaseName(DATABASE_FILE_PATH);
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Succeed to connect database.";
    }

}

void MySQL::init(){
   // QSqlDatabase database;
    database.setDatabaseName(DATABASE_FILE_PATH);
    if (!database.open())
    {
        qDebug() << "Error: When init, Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "(init)Succeed to connect database." ;
    }

    //创建表格
    QSqlQuery sql_query;
    if(!sql_query.exec("create table USERS("
                       "id int primary key, "
                       "username text, "
                       "passwd text,"
                       "admin int)"))
    {
        qDebug() << "Error: (init)Fail to create USERS table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "(init)Table USERS created!";
    }
//    QSqlQuery sql_query;
//    if(!sql_query.exec("create table MAP("
//                       "id int primary key, "
//                       "username text, "
//                       "passwd text)"))
//    {
//        qDebug() << "Error: (init)Fail to create USERS table."<< sql_query.lastError();
//    }
//    else
//    {
//        qDebug() << "(init)Table USERS created!";
//    }
}



MySQL:: ~MySQL(){
    this->database.close();
    qDebug() << "Database closed;";
}
