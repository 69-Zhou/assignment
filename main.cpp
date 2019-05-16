#include "mainwidgets.h"
#include <QApplication>
#include"dialog.h"
#include"checkpoint.h"
#include <QtWidgets>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwidgets w;
    Dialog StarDialog;//第一个界面
    StarDialog.setWindowTitle(QObject::tr("蟹黄堡"));
    w.setWindowTitle(QObject::tr("蟹黄堡"));
    if(StarDialog.exec() == QDialog::Accepted){
        CheckPoint check;//选择关卡界面
        check.setWindowTitle(QObject::tr("蟹黄堡"));
        check.show();
        if(check.exec() == QDialog::Accepted){
           w.show();
           return a.exec();//让主窗口中的事件继续运行；
        }
        else {
            return 0;//直接关闭程序；
        }
    }
    else{
        return 0;
    }
}
