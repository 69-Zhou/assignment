#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow;
class QTimer;

class Tower : QObject
{
	Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/tower1.png"),int attackRange = 200,int damage = 10,int firerate = 700);
    virtual ~Tower();

    void draw(QPainter *painter) const;
	void checkEnemyInRange();
	void targetKilled();
	void attackEnemy();
	void chooseEnemyForAttack(Enemy *enemy);
	void removeBullet();
	void damageEnemy();
	void lostSightOfEnemy();


    bool containPoint(const QPoint &pos) const;
public slots:
	void shootWeapon();
    void update();

protected:
    bool            m_decelerate;
    int             m_enemykilled;
	bool			m_attacking;
	int				m_attackRange;	// 代表塔可以攻击到敌人的距离
	int				m_damage;		// 代表攻击敌人时造成的伤害
	int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    //qreal			m_rotationSprite;
    int             m_level;
	Enemy *			m_chooseEnemy;
	MainWindow *	m_game;
	QTimer *		m_fireRateTimer;

	const QPoint	m_pos;
	const QPixmap	m_sprite;

	static const QSize ms_fixedSize;
};

#endif // TOWER_H
