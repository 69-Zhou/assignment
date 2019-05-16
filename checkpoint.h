#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QDialog>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
namespace Ui {
class CheckPoint;
}

class CheckPoint : public QDialog
{
    Q_OBJECT

public:
    explicit CheckPoint(QWidget *parent = 0);
    ~CheckPoint();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CheckPoint *ui;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CHECKPOINT_H
