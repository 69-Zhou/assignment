#ifndef TOWER2_H
#define TOWER2_H
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include "tower.h"

class Tower2:public Tower
{
public:
    Tower2(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/tower3.png"),int attackRange = 150,int damage = 10,int firerate = 300);
    ~Tower2();

};

#endif // TOWER2_H
