#include "checkpoint.h"
#include "ui_checkpoint.h"
#include "mainwindow.h"

CheckPoint::CheckPoint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckPoint)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("兵临城下"));
    ui->pushButton->setStyleSheet("QPushButton{border-image:url(:/image/11.png)}");
    ui->pushButton_2->setStyleSheet("QPushButton{border-image:url(:/image/22.png)}");
}

CheckPoint::~CheckPoint()
{
    delete ui;
}

void CheckPoint::on_pushButton_clicked()
{
    //accept();
    MainWindow *w = new MainWindow;
    w->setCheckPoint(1);
    w->setWindowTitle(QObject::tr("兵临城下"));
    w->loadTowerPositions();
    w->show();
    delete this;
}

void CheckPoint::on_pushButton_2_clicked()
{
    //reject();
    MainWindow *w = new MainWindow;
    w->setCheckPoint(2);
    w->setWindowTitle(QObject::tr("兵临城下"));
    w->loadTowerPositions();
    w->show();
    delete this;
}

void CheckPoint::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,CheckPoint::width(),CheckPoint::height(), QPixmap(":/image/begin2.jpg"));

}
