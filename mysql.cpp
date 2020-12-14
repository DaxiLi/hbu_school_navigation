#include "mysql.h"
#include "base.h"
#include "point.h"

#include <QFileInfo>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
//#define DATABASE_FILE_PATH ":/sql/src/MyDataBase.db"
#define DATABASE_FILE_PATH "MyDataBase.db"
#ifndef RANGE
#define RANGE 8
#endif

MySQL::MySQL()
{
    //数据库不存在则创建数据库
    QFileInfo file(DATABASE_FILE_PATH);
    database = QSqlDatabase::addDatabase("QSQLITE");
    if (!file.isFile()){
        QFile file(":/sql/src/MyDataBase.db");
        file.setPermissions(QFile::ReadOther | QFile::WriteOther);
        file.copy(DATABASE_FILE_PATH);
        file.close();
        QFile file1(DATABASE_FILE_PATH);
        file1.setPermissions(QFile::ReadOther | QFile::WriteOther);
        //file1.copy(DATABASE_FILE_PATH);
        file1.close();
        //init();
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
    QFile file(":/sql/src/POINT.sql");



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
                       "admin int DEFAULT 0)"))
    {
        qDebug() << "Error: (init)Fail to create USERS table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "(init)Table USERS created!";
    }
    if(!sql_query.exec("create table POINT("
                       "point text primary key,"
                       "x int, "
                       "y int, "
                       "build int DEFAULT 0,"
                       "buiding_name text,"
                       "about text)") ||
            !sql_query.exec("create table NEAR("
                            "x int, "
                            "y int, "
                            "next_x int,"
                            "next_y int,"
                            "int dis)"))
    {
        qDebug() << "Error: (init)Fail to create POINT table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "(init)Table POINT created!";
    }
    add_user("admin","admin","1");
}

QVector<Point> MySQL::get_min_dis_point(int x,int y){
    QVector<Point> retval;
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
    }
    QString sql = "SELECT next_x,next_y,min(dis) FROM NEAR where x = " + QString::number(x) + " and y = " + QString::number(y) + ";";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "查找失败" << sql_query.lastError();
        qDebug() << sql;
    }
    if (sql_query.next()) {
        retval.append(Point(sql_query.value(0).toInt(),sql_query.value(1).toInt()));
    }
    return retval;
}


void MySQL::inser_near(int x,int y,int next_x,int next_y){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
        return;
    }
    QSqlQuery sql_query ;
    QString sql = "insert into NEAR(x, y,next_x ,next_y,dis) select " +
            QString::number(x) + "," +
            QString::number(y) + "," +
            QString::number(next_x) + "," +
            QString::number(next_y) + "," +
            get_dis(x,y,next_x,next_y) + " where not exists (select * from NEAR where  x = " +
            QString::number(x) + " and y = " +
            QString::number(y) + " and next_x = " +
            QString::number(next_x) + " and next_y = " +
             QString::number(next_y) + ")";
    if (sql_query.exec(sql)){
        qDebug() << "Add near Successfully!";
        return;
    }else {
        qDebug() << "Error:Add user Failure! sql_string:" + sql;
    }

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
        return sql_query.value(0).toString();
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

void MySQL::inser_point(Point *P){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
    }
    QSqlQuery sql_query ;
    QString sql = "replace INTO POINT(point,x,y,build,buiding_name,about)"
                  "VALUES(\'{" + P->x + "," + P->y + "}"
                    "\',\' "+ P->x +
                    "\',\'" + P->y +
                    "\',\'" + P->build +
                    "\',\'" + P->name +
                    "\',\'" + P->about +
                 "\')";
    if (sql_query.exec(sql)){
        qDebug() << "Add user Successfully!";
       // return true;
    }else {
        qDebug() << sql_query.lastError();
        qDebug() << "Error:Add user Failure! sql_string:" + sql;
    }
}
void MySQL::remove_point_by_XY(int x, int y){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
    }
    QString sql = " DELETE from POINT where x between " +
            QString::number(x - RANGE) +
            " and " +
            QString::number(x + RANGE) +
            " and y between " +
            QString::number(y - RANGE) +
            " and " +
            QString::number(y + RANGE) +
            " ;";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "删除点失败" << sql_query.lastError();
        qDebug() << "sql:" << sql;
        return;
    }
    sql = " DELETE from NEAR where ( x between " +
            QString::number(x - RANGE) +
            " and " +
            QString::number(x + RANGE) +
            " and y between " +
            QString::number(y - RANGE) +
            " and " +
            QString::number(y + RANGE) +
            " )  or (next_x between " +
            QString::number(x - RANGE) +
            " and " +
            QString::number(x + RANGE) +
            " and next_y between " +
            QString::number(y - RANGE) +
            " and " +
            QString::number(y + RANGE) +
            " ) ";
    if (!sql_query.exec(sql)){
        qDebug() << "删除点失败" << sql_query.lastError();
        qDebug() << "sql:" << sql;
        return;
    }
}
void MySQL::get_point_by_XY(Point** p,int x,int y){
    if (p == NULL){return ;}
    if(*p != NULL){
        delete *p;
        *p = NULL;
    }
    qDebug() << "finding point:" << x <<y;
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
    }
    QString sql = " SELECT * FROM POINT where x between " +
            QString::number(x - RANGE) +
            " and " +
            QString::number(x + RANGE) +
            " and y between " +
            QString::number(y - RANGE) +
            " and " +
            QString::number(y + RANGE) +
            " ;";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "查找点失败" << sql_query.lastError();
        qDebug() << "sql:" << sql;
        return;
    }
    if (sql_query.next()) {
        Point *tep = new Point();
        tep->x = sql_query.value(1).toString();
        tep->y = sql_query.value(2).toString();
        tep->build = sql_query.value(3).toString();
        tep->name = sql_query.value(4).toString();
        tep->about = sql_query.value(5).toString();
        qDebug() << "find + 1";
        qDebug() << tep->to_string();
        *p = tep;
        return ;
    }
    return;
}
QVector<Point> MySQL::find_point(int x,int y){
    qDebug() << "finding point:" << x <<y;
            if (!database.open()){
                qDebug() << "Error:数据库已关闭！";
            }
            QVector<Point> retval = QVector<Point>();
            QString sql = " SELECT * FROM POINT where x between " +
                    QString::number(x - RANGE) +
                    " and " +
                    QString::number(x + RANGE) +
                    " and y between " +
                    QString::number(y - RANGE) +
                    " and " +
                    QString::number(y + RANGE) +
                    ";";
            QSqlQuery sql_query;
            if (!sql_query.exec(sql)){
                qDebug() << "查找点失败" << sql_query.lastError();
                qDebug() << "sql:" << sql;
                return retval;
            }
            while (sql_query.next()) {
                Point tep;
                tep.x = sql_query.value(1).toString();
                tep.y = sql_query.value(2).toString();
                tep.build = sql_query.value(3).toString();
                tep.name = sql_query.value(4).toString();
                tep.about = sql_query.value(5).toString();
                retval.append(tep);
                qDebug() << "find + 1";
                qDebug() << tep.to_string();
            }
            return retval;
}
Point MySQL::find_exact_point(int x,int y){
    return Point(x,y);
}
QVector<Point> MySQL::getAllLines(){
            if (!database.open()){
                qDebug() << "Error:数据库已关闭！";
            }
            QVector<Point> retval = QVector<Point>();
            QString sql = " SELECT * FROM NEAR ;";
            QSqlQuery sql_query;
            if (!sql_query.exec(sql)){
                return retval;
            }
            while (sql_query.next()) {
                Point tep;
                tep.x = sql_query.value(0).toString();
                tep.y = sql_query.value(1).toString();
                tep.next_x = sql_query.value(2).toString();
                tep.next_y = sql_query.value(3).toString();
                retval.append(tep);
            }
            return retval;
}

QVector<Point> MySQL::getAllPoints(){
    qDebug() << "finding points";
            if (!database.open()){
                qDebug() << "Error:数据库已关闭！";
            }
            QVector<Point> retval = QVector<Point>();
            QString sql = " SELECT * FROM POINT ;";
            QSqlQuery sql_query;
            if (!sql_query.exec(sql)){
                qDebug() << "查找点失败" << sql_query.lastError();
                qDebug() << "sql:" << sql;
                return retval;
            }
            while (sql_query.next()) {
                Point tep;
                tep.x = sql_query.value(1).toString();
                tep.y = sql_query.value(2).toString();
                tep.build = sql_query.value(3).toString();
                tep.name = sql_query.value(4).toString();
                tep.about = sql_query.value(5).toString();
                retval.append(tep);
                qDebug() << "find + 1";
                qDebug() << tep.to_string();
            }
            return retval;
}

QString MySQL::get_admin_name(){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
    }
    QString sql = "SELECT username FROM USERS where admin = 1";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "查找失败" << sql_query.lastError();
        return  "_error_error_";
    }
    if (sql_query.next()) {
        return sql_query.value(0).toString();
    }
    return "_error_error_";
}

void MySQL::update(QString x,QString y,QString is_build,QString about,QString name){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
    }
    QString sql = "update POINT set build = '" + is_build + "',buiding_name = '" + name + "',about = '" + about + "' where x = " +
            x +
            " and y = " +
            y +
            " ;";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "ERROR:uopdated failure!" << sql_query.lastError();
        qDebug() << "sql:" << sql;
        return;
    }
}
