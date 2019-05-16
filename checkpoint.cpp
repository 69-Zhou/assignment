#include "checkpoint.h"
#include "ui_checkpoint.h"

CheckPoint::CheckPoint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckPoint)
{
    ui->setupUi(this);
}

CheckPoint::~CheckPoint()
{
    delete ui;
}

void CheckPoint::on_pushButton_clicked()
{
    accept();
}

void CheckPoint::on_pushButton_2_clicked()
{
    reject();
}

void CheckPoint::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,CheckPoint::width(),CheckPoint::height(), QPixmap(":/image/timg1.jpg"));

}
