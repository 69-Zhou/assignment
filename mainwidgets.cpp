#include "mainwidgets.h"
#include "ui_mainwidgets.h"

mainwidgets::mainwidgets(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwidgets)
{
    ui->setupUi(this);
}

mainwidgets::~mainwidgets()
{
    delete ui;
}

void mainwidgets::paintEvent(QPaintEvent *e){
    QImage map;//加载地图
    QPainter painter(this);
    map.load(":/image/start.jpg.jpg");
    painter.drawImage(QPoint(0,0),map);
}
