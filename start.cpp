#include "start.h"
#include "mainwindow.h"
#include "welcom.h"
#include "mysql.h"
#include "mymap.h"
#include "main.h"

QString WHO_AM_I = "";
Welcom *welcom ;
MainWindow *mainwindow;

Start::Start()
{
    welcom = new Welcom();
    welcom->show();
}

void Start::close_welcom(){
    if (welcom == NULL){
        return;
    }
    welcom->close();
    free(welcom);
}

void Start::close_mainwindow(){
    if (mainwindow == NULL){
        return;
    }
    mainwindow->close();
    free( mainwindow);
}
void Start::open_mainwindow(){
    if (mainwindow == NULL){
        mainwindow = new MainWindow();
    }
    mainwindow->show();
}

Start::~Start(){
    if (mainwindow != NULL){
        mainwindow->close();
        free(mainwindow);
    }
    if (welcom != NULL){
        welcom->close();
        free(welcom);
    }
}
