#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include "tower1.h"



Tower1::Tower1(QPoint pos, MainWindow *game, const QPixmap &sprite /*= QPixmap(":/image/tower2.png")*/,int attackRange /*= 100*/,int damage /*= 20*/,int firerate /*= 1000*/):
    Tower(pos,game,sprite,attackRange,damage,firerate)
{

}

Tower1::~Tower1()
{

}
