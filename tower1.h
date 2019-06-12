#ifndef TOWER1_H
#define TOWER1_H

#include <QSize>
#include <QPixmap>
#include <QObject>
#include "tower.h"

class QPainter;
class Enemy;
class MainWindow;
class QTimer;

class Tower1 : public Tower
{
public:
    Tower1(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/tower2.png"),int attackRange = 150,int damage = 15,int firerate = 1000);
    ~Tower1();
};

#endif // TOWER1_H
