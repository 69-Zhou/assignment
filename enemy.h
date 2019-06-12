#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;

class Enemy : public QObject
{
	Q_OBJECT
public:
    //Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemy.png"));
    Enemy(int mapnum,MainWindow *game,const QPixmap &picture=QPixmap(":/image/enemy11.png"),int hp=40,int currenthp=40,int price=10,double movespeed=1.0);
    virtual ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage, int label);
	void getRemoved();
	void getAttacked(Tower *attacker);
	void gotLostSight(Tower *attacker);
    virtual void addwaypoint1();
    virtual void addwaypoint2();
	QPoint pos() const;

public slots:
	void doActivate();

protected:
    bool            m_decelerate;
	bool			m_active;
	int				m_maxHp;
	int				m_currentHp;
    int             m_price;//设置价格
	qreal			m_walkingSpeed;
	qreal			m_rotationSprite;

	QPoint			m_pos;
	WayPoint *		m_destinationWayPoint;
	MainWindow *	m_game;
	QList<Tower *>	m_attackedTowersList;
    QList<WayPoint *>		m_wayPointsList;

	const QPixmap	m_sprite;
	static const QSize ms_fixedSize;
};

#endif // ENEMY_H
