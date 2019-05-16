#ifndef MAINWIDGETS_H
#define MAINWIDGETS_H

#include <QMainWindow>
#include<QPainter>
namespace Ui {
class mainwidgets;
}

class mainwidgets : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwidgets(QWidget *parent = 0);
    ~mainwidgets();
    void paintEvent(QPaintEvent *e);
private:
    Ui::mainwidgets *ui;
};

#endif // MAINWIDGETS_H
