#include "dialog.h"
#include "ui_dialog.h"
#include<QWizard>
#include<QLabel>
#include<QHBoxLayout>
#include"checkpoint.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("兵临城下"));
    ui->start->setStyleSheet("QPushButton{border-image:url(:/image/start.png)}");
    ui->help->setStyleSheet("QPushButton{border-image:url(:/image/help1.png)}");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,Dialog::width(),Dialog::height(), QPixmap(":/image/begin11.jpg"));

}


void Dialog::on_start_clicked()
{
     //accept();
    CheckPoint *Check = new CheckPoint;
    Check->show();
    delete this;
}

QWizardPage *Dialog::createpage(){
    QWizardPage *page = new QWizardPage;
    page->resize(400,400);
    QPixmap pix(":/image/helpscene1.jpg");
    QLabel *label = new QLabel;
    label->setPixmap(pix);
    label->setScaledContents(true);
    label->resize(400,390);
    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(label);
    //page->setPixmap(QWizard::BackgroundPixmap,pix);
    page->setLayout(lay);
    return page;
}
void Dialog::on_help_clicked()
{
    QWizard wizard(this);
    wizard.addPage(createpage());
    wizard.setOption(QWizard::NoCancelButton);
    wizard.setOption(QWizard::NoBackButtonOnStartPage);
    wizard.exec();
}
