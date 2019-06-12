#ifndef ENEMYSON2_H
#define ENEMYSON2_H

#include "enemy.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QSize>
class enemyson2 : public Enemy
{
public:
    enemyson2(int mapnum,MainWindow *game,const QPixmap &picture=QPixmap(":/image/enemy55.png"),int hp=70,int currenthp=70,int price=40,double movespeed=4.0);
    virtual ~enemyson2();
    virtual void addwaypoint1();
    virtual void addwaypoint2();

};


#endif // ENEMYSON2_H
