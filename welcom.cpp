#include "welcom.h"
#include "ui_welcom.h"
#include "sigin.h"
#include "login.h"

Welcom::Welcom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Welcom)
{
    ui->setupUi(this);
    this->setWindowTitle("地图");
    this->setWindowIcon(QIcon(":/src/icon/src/img/logo_mini.jpg"));
}

Welcom::~Welcom()
{
    delete ui;
}



void Welcom::on_sigin_buttom_clicked()
{
    Sigin *S = new Sigin();
    Qt::WindowFlags flags = Qt::Dialog;
    S->setWindowFlags(flags);
    S->setWindowModality(Qt::ApplicationModal);
    // 将窗口焦点强行聚集在子窗口
    S->show();
}

void Welcom::on_login_button_clicked()
{
    Login *S = new Login();
    Qt::WindowFlags flags = Qt::Dialog;
    S->setWindowFlags(flags);
    S->setWindowModality(Qt::ApplicationModal);
    // 将窗口焦点强行聚集在子窗口
    S->show();
}
