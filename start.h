#ifndef START_H
#define START_H

#include "mainwindow.h"
#include "welcom.h"
#include "mysql.h"
#include "mymap.h"


class Start
{
public:
    QString WHO_AM_I = "";
    Welcom *welcom ;
    MainWindow *mainwindow;
    Start();
    ~Start();
    void close_welcom();
    void close_mainwindow();
    void set_user(QString name){this->WHO_AM_I = name;}
    void open_mainwindow();

};

#endif // START_H
