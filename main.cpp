#include "mainwindow.h"
#include <QApplication>
#include"dialog.h"
#include"checkpoint.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    Dialog StarDialog;//第一个界面
    StarDialog.show();

    return a.exec();
}


