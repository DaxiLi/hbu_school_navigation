#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sigin.h"
#include "login.h"
#include "welcom.h"
#include "ui_testmainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Welcom *W = new Welcom();
    W->show();

//
//    this->setWindowTitle("地图");
//    this->setWindowIcon(QIcon(":/src/icon/src/img/logo_mini.jpg"));
    //ui->login_button->setFlat(true);
   // ui->sigin_buttom->setFlat(true);
   // QImage *image= new QImage("qrc:/src/icon/logo");
    //ui->logo->setPixmap(QPixmap::fromImage(*image));
}

MainWindow::~MainWindow()
{
    delete ui;
}


