#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sigin.h"
#include "login.h"
#include "welcom.h"
#include "ui_testmainwindow.h"
#include "scribblearea.h"

#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ScribbleArea *s = new ScribbleArea();
    ui->scrollArea->setWidget(s);
    s->openImage(":/map/map/all.png");
    setAttribute(Qt::WA_DeleteOnClose);

}

MainWindow::~MainWindow()
{
    delete ui;
}




