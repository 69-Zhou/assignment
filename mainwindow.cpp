#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "enemyson1.h"
#include "enemyson2.h"
#include "bullet.h"
#include "tower.h"
#include "tower1.h"
#include "tower2.h"
#include "audioplayer.h"
#include "dialog.h"
//#include "plistreader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
//#include <QXmlStreamReader>
#include <QtDebug>
#include <QFont>

static const int TowerCost = 300;
//static int SumOfGold = 1000;
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m_waves(0)
	, m_playerHp(5)
    , m_playrGold(1000)
	, m_gameEnded(false)
	, m_gameWin(false)
{
	ui->setupUi(this);
    //this->setMinimumSize(1270,799);
    //this->setMaximumSize(1270,799);
    //拖动事件
    ui->update->hide();
    ui->reStart->hide();//按钮不可见
    ui->reStart->setStyleSheet("QPushButton{border-image:url(:/image/again1.png)}");
    setAutoFillBackground(true);
    ui->denfense1->setPixmap(QPixmap(":/image/tower1.png"));
    ui->denfense2->setPixmap(QPixmap(":/image/tower2.png"));
    ui->defense3->setPixmap(QPixmap(":/image/tower3.png"));
    setAcceptDrops(true);
    ui->denfense1->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁图片
    ui->denfense2->setAttribute(Qt::WA_DeleteOnClose);
    ui->defense3->setAttribute(Qt::WA_DeleteOnClose);
    ui->update->setStyleSheet("QPushButton{border-image:url(:/image/11.png)}");
    //loadTowerPositions();
//	addWayPoints();

    if(m_check==1){
        QMediaPlayer * m_round1 = new QMediaPlayer;
           m_round1->setMedia(QUrl("qrc:/music/round1.mp3"));
           m_round1->play();
    }
    else{
        QMediaPlayer * m_round2 = new QMediaPlayer;
           m_round2->setMedia(QUrl("qrc:/music/round2.mp3"));
           m_round2->play();
    }




	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
	timer->start(30);
	// 设置300ms后游戏启动
    QTimer::singleShot(5000, this, SLOT(gameStart()));
}


MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadTowerPositions()
{
    if(m_check==1){

        QPoint pos[] =
        {
            QPoint(183,80),
            QPoint(727,101),
            QPoint(457,514),
            QPoint(464,265),
            QPoint(840,388),
        };
        int len	= sizeof(pos) / sizeof(pos[0]);
        for (int i = 0; i < len; ++i)
            m_towerPositionsList.push_back(pos[i]);
    }
    else{
        QPoint pos[] =
        {
            QPoint(278,425),
            QPoint(590,285),
            QPoint(220,50),
            QPoint(831,512),
            QPoint(1036,320),
            QPoint(820,50),

        };
        int len	= sizeof(pos) / sizeof(pos[0]);
        for (int i = 0; i < len; ++i)
            m_towerPositionsList.push_back(pos[i]);
    }


}

void MainWindow::paintEvent(QPaintEvent *)
{
	if (m_gameEnded || m_gameWin)
    {
        if(m_gameEnded)
        {
            QMediaPlayer * m_gameover = new QMediaPlayer;
                       m_gameover->setMedia(QUrl("qrc:/music/Gameover.mp3"));
                       m_gameover->play();
            QPixmap pixmap(":/image/lose.png");
            QPainter painter(this);
            painter.drawPixmap(400,300,300,200,pixmap);
        }
        else
        {
            QMediaPlayer * m_gamewin = new QMediaPlayer;
                       m_gamewin->setMedia(QUrl("qrc:/music/Gamewin.mp3"));
                       m_gamewin->play();
            QPixmap pixmap(":/image/win.png");
            QPainter painter(this);
            painter.drawPixmap(400,300,300,200,pixmap);
        }
    ui->reStart->show();
    ui->denfense1->hide();
    ui->denfense2->hide();
    ui->defense3->hide();
    ui->data1->hide();
    ui->data2->hide();
    ui->data3->hide();
		return;
	}

    if(m_check == 1)
    {
        QPixmap cachePix(":/image/map1.jpg");
	QPainter cachePainter(&cachePix);

	foreach (const TowerPosition &towerPos, m_towerPositionsList)
		towerPos.draw(&cachePainter);

	foreach (const Tower *tower, m_towersList)
		tower->draw(&cachePainter);

    //foreach (const WayPoint *wayPoint, m_wayPointsList)
        //wayPoint->draw(&cachePainter);

	foreach (const Enemy *enemy, m_enemyList)
		enemy->draw(&cachePainter);

	foreach (const Bullet *bullet, m_bulletList)
		bullet->draw(&cachePainter);



	QPainter painter(this);
    painter.drawPixmap(0, 0,1200,799,cachePix);
    drawrect(&painter);
    drawWave(&painter);
    drawHP(&painter);
    drawPlayerGold(&painter);
    }
    else if(m_check == 2){
        QPixmap cachePix(":/image/2.png");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    //foreach (const WayPoint *wayPoint, m_wayPointsList)
        //wayPoint->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);


    QPainter painter(this);
    painter.drawPixmap(0, 0,cachePix);
    drawrect(&painter);
    drawWave(&painter);
    drawHP(&painter);
    drawPlayerGold(&painter);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    //输出点击位置相对于当前窗口的坐标
    qDebug()<<"event->pos() = "<<event->pos();
    //输出点击位置相对于全屏幕的坐标
    //qDebug()<<"event->globalPos() = "<<event->globalPos();
    QPoint pressPos = event->pos();
        foreach (Tower *tower, m_towersList){
            if (tower->containPoint(pressPos)){
                m_updatetower = tower;

                 ui->update->show();
                 update();
                 break;
            }
            else{
                ui->update->hide();
            }
        }
    //拖动
if(pressPos.x()>1200){
    QLabel *child = static_cast<QLabel *>(childAt(event->pos()));
       if(!child->inherits("QLabel")){
           return;
       }
       if(child->acceptDrops()){//排除其他图片的干扰
           return;
       }
       QPixmap pixmap = *child->pixmap();//抓取图片
       QByteArray itemData;
       QDataStream dataStream(&itemData,QIODevice::WriteOnly);
       dataStream<<pixmap<<QPoint(event->pos() - child->pos());//传数据流
       QMimeData *mimeData = new QMimeData;//存数据
       mimeData->setData(":/image/tower1.png",itemData);
       QDrag *drag = new QDrag(this);
       drag->setMimeData(mimeData);
       drag->setPixmap(pixmap.scaled(70,70));//移动过程中显示缩放的图片
       drag->setHotSpot(event->pos() - child->pos());
       if(drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction)== Qt::MoveAction){
           child->show();
           child->setPixmap(pixmap);
           }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasFormat(":/image/tower1.png")){
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
    else{
        event->ignore();
    }
}
/*
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

}
*/

void MainWindow::dropEvent(QDropEvent *event){
    if( event->mimeData()->hasFormat(":/image/tower1.png")){
        QByteArray itemData = event->mimeData()->data(":/image/tower1.png");
        QDataStream dataStream(&itemData,QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QPixmap tower1(":/image/tower1.png");//检查一下图片大小
        QPixmap tower2(":/image/tower2.png");

        QPoint pressPos = event->pos();
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
        {
            if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
            {
                m_playrGold -= TowerCost;
                it->setHasTower();
                if(pixmap.height() == tower1.height()){
                    Tower *tower = new Tower(it->centerPos(), this, pixmap);
                     m_towersList.push_back(tower);
                }
                else if(pixmap.height() == tower2.height()){
                    Tower *tower = new Tower1(it->centerPos(), this, pixmap);
                     m_towersList.push_back(tower);
                }
                else{
                    Tower *tower = new Tower2(it->centerPos(),this, pixmap);
                    m_towersList.push_back(tower);
                }
                update();
                break;
            }
            ++it;
        }
    //}
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
    else{
        event->ignore();
    }
}

bool MainWindow::canBuyTower() const
{
	if (m_playrGold >= TowerCost)
		return true;
	return false;
}

void MainWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(1200, 535, 60, 60), QString("WAVE : %5").arg(m_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(1200, 600, 60, 60), QString("HP : %5").arg(m_playerHp));
}

void MainWindow::drawrect(QPainter *painter)
{
    QPixmap rect(":/image/rect.jpg");
    painter->drawPixmap(1200,0,70,799,rect);
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(1200, 670, 60, 60), QString("GOLD : %1").arg(m_playrGold));
}

void MainWindow::doGameOver()
{
	if (!m_gameEnded)
	{
        m_gameEnded = true;
	}
}

void MainWindow::awardGold(int gold)
{
    QMediaPlayer * m_goldadd = new QMediaPlayer;
       m_goldadd->setMedia(QUrl("qrc:/music/gold.mp3"));
       m_goldadd->play();
	m_playrGold += gold;
	update();
}

AudioPlayer *MainWindow::audioPlayer() const
{
	return m_audioPlayer;
}

/*void MainWindow::addWayPoints()//采用逆序写法
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(1008,284));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(947,284));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(947,679));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(337,679));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5= new WayPoint(QPoint(337,376));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(595,376));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(595,518));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(763,518));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(763,221));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(137,221));
    m_wayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(137,363));
    m_wayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint (39,363));
    m_wayPointsList.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);

}*/

void MainWindow::getHpDamage(int damage/* = 1*/)
{
    QMediaPlayer * m_HPcut = new QMediaPlayer;
        m_HPcut->setMedia(QUrl("qrc:/music/HP-.mp3"));
        m_HPcut->play();

	m_playerHp -= damage;
	if (m_playerHp <= 0)
		doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
	Q_ASSERT(enemy);

	m_enemyList.removeOne(enemy);
	delete enemy;

	if (m_enemyList.empty())
	{
		++m_waves;
		if (!loadWave())
		{
			m_gameWin = true;
			// 游戏胜利转到游戏胜利场景
			// 这里暂时以打印处理
		}
	}
}

void MainWindow::removedBullet(Bullet *bullet)
{
	Q_ASSERT(bullet);

	m_bulletList.removeOne(bullet);
	delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
	Q_ASSERT(bullet);

	m_bulletList.push_back(bullet);
}

void MainWindow::updateMap()
{
	foreach (Enemy *enemy, m_enemyList)
		enemy->move();
	foreach (Tower *tower, m_towersList)
		tower->checkEnemyInRange();
	update();
}

bool MainWindow::loadWave()
{


    if(m_waves>=4)
        return false;
    //WayPoint *startpoint =m_wayPointsList.back();//起始点位航点链表中的最后一位
    int enemystartTime[]={100,1100,2100,3100};//敌人一个个出现时间设置
    int enemystartTime1[]={100,1200,3000};
    int enemystartTime2[]={1000,1300,2000,3000,4000};

    QMediaPlayer * m_enemyinto = new QMediaPlayer;
       m_enemyinto->setMedia(QUrl("qrc:/music/enemyinto.mp3"));
       m_enemyinto->play();

    for(int i=0;i<4;i++){
        Enemy *enemy = new Enemy(this->m_check,this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemystartTime[i],enemy,SLOT(doActivate()));//定时发送信息使敌人移动
    }

    for(int i=0;i<3;i++){
        Enemy *enemyson = new enemyson1(this->m_check,this);
        m_enemyList.push_back(enemyson);
        QTimer::singleShot(enemystartTime1[i],enemyson,SLOT(doActivate()));
    }

    for(int i=0;i<5;i++){
        Enemy *enemyson = new enemyson2(this->m_check,this);
        m_enemyList.push_back(enemyson);
        QTimer::singleShot(enemystartTime2[i],enemyson,SLOT(doActivate()));
    }
    return true;
}

QList<Enemy *> MainWindow::enemyList() const
{
	return m_enemyList;
}

void MainWindow::gameStart()
{
	loadWave();
}

void MainWindow::on_reStart_clicked()
{
    Dialog *start = new Dialog;
    start->show();
    delete this;
}

void MainWindow::setCheckPoint(int check)
{
    this->m_check = check;
}


void MainWindow::on_update_clicked()
{
    if(m_playrGold >= 100 && m_updatetower !=NULL){
           m_playrGold -= 100;
           m_updatetower->update();

       }
}

