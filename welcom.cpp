#include "welcom.h"
#include "ui_welcom.h"
#include "sigin.h"
#include "login.h"
#include "main.h"

Welcom::Welcom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Welcom)
{
    ui->setupUi(this);
    this->setWindowTitle("地图");
    this->setWindowIcon(QIcon(":/src/icon/src/img/logo_mini.jpg"));
    setAttribute(Qt::WA_DeleteOnClose);
}

Welcom::~Welcom()
{
    delete ui;
}

void Welcom::on_sigin_buttom_clicked()
{
    start->open_sigin();
}

void Welcom::on_login_button_clicked()
{
   start->open_login();
}
