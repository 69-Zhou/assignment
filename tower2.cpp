#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include "tower2.h"

Tower2::Tower2(QPoint pos,MainWindow *game, const QPixmap &sprite /*= QPixmap(":/image/tower3.png")*/,int attackRange /*= 200*/,int damage /*= 10*/,int firerate /*= 1000*/)
    :Tower(pos,game,sprite,attackRange,damage,firerate)
{

}

Tower2::~Tower2()
{

}
