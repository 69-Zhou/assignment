#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "QMediaPlayer"
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QLabel>
#include <QDrag>
#include <QMimeData>
namespace Ui {
class MainWindow;
}

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:

	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
    void setCheckPoint(int check);
	void getHpDamage(int damage = 1);
	void removedEnemy(Enemy *enemy);
	void removedBullet(Bullet *bullet);
	void addBullet(Bullet *bullet);
	void awardGold(int gold);
	AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;
    void loadTowerPositions();
/*
public slots:
    void start();*/

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    //void mouseDoubleClickEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
private slots:
	void updateMap();
	void gameStart();

    void on_reStart_clicked();

    void on_update_clicked();

private:

    //void addWayPoints();
	bool loadWave();
	bool canBuyTower() const;
	void drawWave(QPainter *painter);
	void drawHP(QPainter *painter);
    void drawrect(QPainter*painter);
	void drawPlayerGold(QPainter *painter);
	void doGameOver();
	void preLoadWavesInfo();

private:
	Ui::MainWindow *		ui;
	int						m_waves;
	int						m_playerHp;
	int						m_playrGold;
	bool					m_gameEnded;
	bool					m_gameWin;
	AudioPlayer *			m_audioPlayer;
	QList<QVariant>			m_wavesInfo;
	QList<TowerPosition>	m_towerPositionsList;
	QList<Tower *>			m_towersList;

	QList<Enemy *>			m_enemyList;
	QList<Bullet *>			m_bulletList;
    int                     m_check;
    QMediaPlayer *          m_round1;
    QMediaPlayer *          m_round2;
       QMediaPlayer *          m_HPcut;
       QMediaPlayer *          m_goldadd;
       QMediaPlayer *          m_enemyinto;
       QMediaPlayer *          m_gameover;
       QMediaPlayer *          m_gamewin;

    Tower *                 m_updatetower;
};

#endif // MAINWINDOW_H
