#include "mymap.h"
#include "ui_mymap.h"

MyMap::MyMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMap)
{
    ui->setupUi(this);
}

MyMap::~MyMap()
{
    delete ui;
}
