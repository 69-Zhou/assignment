#ifndef ENEMYSON1_H
#define ENEMYSON1_H

#include "enemy.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QSize>



class enemyson1 : public Enemy
{
public:
    enemyson1(int mapnum,MainWindow *game,const QPixmap &picture=QPixmap(":/image/enemy22.png"),int hp=60,int currenthp=60,int price=30,double movespeed=3.0);
    virtual ~enemyson1();
    virtual void addwaypoint1();
    virtual void addwaypoint2();
   // MainWindow* m_game;
};

#endif // ENEMYSON1_H
