#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QWizard>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_start_clicked();

    void on_help_clicked();

private:
    Ui::Dialog *ui;
    QWizardPage *createpage();

protected:
    void paintEvent(QPaintEvent *);

};

#endif // DIALOG_H
