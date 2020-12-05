#include "login.h"
#include "ui_login.h"
#include "base.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");

}

Login::~Login()
{
    delete ui;
}

void Login::on_login_cancel_clicked()
{
    close();
}

void Login::on_login_confirm_clicked()
{
    ui->login_notice->setText("密码错误!");
   // ui->login_notice->getContentsMargins()
    widgetShake(this,5);

}


void Login::on_iforget_linkHovered(const QString &link)
{
    ui->iforget->setText("我也没办法！");

}

void Login::on_iforget_linkActivated(const QString &link)
{
     ui->iforget->setText("我也没办法！");
}
