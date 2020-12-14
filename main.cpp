#include "start.h"

#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QChar>
#include <QLineEdit>

Start start;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start start;

    //qDebug() << QString::compare("a","a");

//    MySQL *s = new MySQL();
//    s->add_user("aja","pass","0");
//    s->add_user("moogila","lplp","0");
//    qDebug()<< "aja passwd:" << s->get_user_passwd("aja");
//    qDebug() << "lk passwd:" <<s->get_user_passwd("lk");
//    delete s;

//    int s[20] = {'0','9','Z','z','_','0','!','@','#','$','%','^','&','*','('};
//    for (int i = 0;i < 20;i++){
//        qDebug() << s[i];
//    }
//    for (int i = '0';i < 'z';i++){
//        qDebug() << i;
//        char t = i;
//        qDebug() << ":" << t;
//    }
//    QString S = "asdfghjkl";
//    foreach(QChar a,S){
//        qDebug() << a;
//    }



//    MainWindow W;
//    W.show();
//    MyMap *M = new MyMap();
//    M->show();



    /***
       QSqlDatabase database;
       database = QSqlDatabase::addDatabase("QSQLITE");
       database.setDatabaseName("MyDataBase.db");
       if (!database.open())
       {
           qDebug() << "Error: Failed to connect database." << database.lastError();
       }
       else
       {
           qDebug() << "Succeed to connect database." ;
       }

       //创建表格
       QSqlQuery sql_query;
       if(!sql_query.exec("create table student(id int primary key, name text, age int)"))
       {
           qDebug() << "Error: Fail to create table."<< sql_query.lastError();
       }
       else
       {
           qDebug() << "Table created!";
       }

       //插入数据
       if(!sql_query.exec("INSERT INTO student VALUES(1, \"Wang\", 23)"))
       {
           qDebug() << sql_query.lastError();
       }
       else
       {
           qDebug() << "inserted Wang!";
       }
       if(!sql_query.exec("INSERT INTO student VALUES(2, \"Li\", 23)"))
       {
           qDebug() << sql_query.lastError();
       }
       else
       {
           qDebug() << "inserted Li!";
       }

       //修改数据
       sql_query.exec("update student set name = \"QT\" where id = 1");
       if(!sql_query.exec())
       {
           qDebug() << sql_query.lastError();
       }
       else
       {
           qDebug() << "updated!";
       }

       //查询数据
       sql_query.exec("select * from student");
       if(!sql_query.exec())
       {
           qDebug()<<sql_query.lastError();
       }
       else
       {
           while(sql_query.next())
           {
               int id = sql_query.value(0).toInt();
               QString name = sql_query.value(1).toString();
               int age = sql_query.value(2).toInt();
               qDebug()<<QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
           }
       }

       //删除数据
//       sql_query.exec("delete from student where id = 1");
//       if(!sql_query.exec())
//       {
//           qDebug()<<sql_query.lastError();
//       }
//       elses
//       {
//           qDebug()<<"deleted!";
//       }

//       //删除表格
//       sql_query.exec("drop table student");
//       if(sql_query.exec())
//       {
//           qDebug() << sql_query.lastError();
//       }
//       else
//       {
//           qDebug() << "table cleared";
//       }

       //关闭数据库
       database.close();

 */

    return a.exec();
}
