#include "mysql.h"
#include <QFileInfo>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

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
       // QMessageBox::about(this, "tip", "数据库创建失败！");
    }
    else
    {
        qDebug() << "(init)Succeed to connect database." ;

    }

    //创建表格
    QSqlQuery sql_query;
    if(!sql_query.exec("create table USERS("
                       "username text primary key, "
                       "passwd text,"
                       "admin int)"))
    {
        qDebug() << "Error: (init)Fail to create USERS table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "(init)Table USERS created!";
    }
    if(!sql_query.exec("create table POINT("
                       "x int primary key, "
                       "y int, "
                       "build int,"
                       "buiding_name text,"
                       "about text,"
                       "next_x int,"
                       "next_y int)"))
    {
        qDebug() << "Error: (init)Fail to create POINT table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "(init)Table POINT created!";
    }
    add_user("admin","admin","1");
}

bool MySQL::add_user(QString name, QString passwd, QString is_admin){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
        return  false;
    }
    QSqlQuery sql_query ;
    QString sql = "INSERT INTO USERS(username,passwd,admin)"
                  "VALUES(\'" + name + "\',\'" + passwd + "\'," + is_admin + ")";
    if (sql_query.exec(sql)){
        qDebug() << "Add user Successfully!";
        return true;
    }else {
        qDebug() << "Error:Add user Failure! sql_string:" + sql;
    }
    return false;
}

QString MySQL::get_user_passwd(QString username){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
    }
    QString sql = "SELECT passwd FROM USERS where username = \'" + username + "\';";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "查找失败" << sql_query.lastError();
        return sql_query.value(0).toString();;
    }
    if (sql_query.next()) {
        qDebug() << "查找用户：" << username << ",passwd:" << sql_query.value(0).toString();
        return sql_query.value(0).toString();
    }
    return "";
}

MySQL:: ~MySQL(){
    this->database.close();
    qDebug() << "Database closed;";
}
