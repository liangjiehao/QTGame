#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>
#include <QImage>
#include <QIcon>
#include <QSize>

map::map(QWidget *parent) : QWidget(parent), home(8000, this), COIN()
{
    setStyleSheet("background-color:rgba(0,0,0,0)");
    resize(B_WIDTH, B_HEIGHT);

    //initMedia();

    setButton();

    initMain();

    update();
}

void map::initMedia()
{

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sound/battle.mp3"));
    playlist->setCurrentIndex(0);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->setCurrentIndex(0);
    QMediaPlayer *player = new QMediaPlayer();

    player->setPlaylist(playlist);
    player->setVolume(1);
    player->play();

}

void map::start()
{
    connect(&backTo, &QPushButton::clicked, this, &map::backToMain);
    connect(&showRule, &QPushButton::clicked, this, &map::displayRule);
    connect(&enterGame, &QPushButton::clicked, this, &map::selectChapter);
    connect(&easy, &QPushButton::clicked, this, &map::initEasy);
    connect(&hard, &QPushButton::clicked, this, &map::initHard);
    connect(&evil, &QPushButton::clicked, this, &map::initEvil);
    connect(&reStart, &QPushButton::clicked, this, &map::restart);
    connect(&deployTower, &QPushButton::clicked, this, &map::deploy);
    connect(&deployTowerHigh, &QPushButton::clicked, this, &map::deploy_high);
    connect(&deployTowerhasaki, &QPushButton::clicked, this, &map::deploy_hasaki);
    connect(&startButton, &QPushButton::clicked, this, &map::init);
    connect(&victory, &QPushButton::clicked, this, &map::restart);
    connect(&defeat, &QPushButton::clicked, this, &map::restart);
    connect(&recycle, &QPushButton::clicked, this, &map::resetCursor);
}

void map::deploy()
{

    setCursor(QPixmap(":/new/bluetow.png"));
    towerControl = "showTowerRange";
    currentTowerType = "blue";
    currentTowerCost = 50;
    update();
    allowDeploy = true;
    setPower = 200;
    setRange = 200;
    if (pageControl == "evil")
    {
        setPower = 300;
    }
}

void map::deploy_high()
{

    setCursor(QPixmap(":/new/redtow.png"));
    towerControl = "showTowerRange";
    currentTowerType = "red";
    currentTowerCost = 75;
    update();
    allowDeploy = true;
    setPower = 150;
    setRange = 350;
    if (pageControl == "evil")
    {
        setPower = 250;
    }
}

void map::deploy_hasaki()
{

    QPixmap temp(":/new/yasuo.png");

    setCursor(temp.scaled(120, 120, Qt::KeepAspectRatio));
    towerControl = "showTowerRange";
    currentTowerType = "single";
    currentTowerCost = 100;
    update();
    allowDeploy = true;
    setPower = 1000;
    setRange = 400;
    if (pageControl == "evil")
    {
        setPower = 2000;
    }
}

void map::countDeployedTower()
{
    TOWER_NUM--;
    allowDeploy = false;
}

void map::showTowerRange(QPainter &qp)
{
    if (!defenceTower.isEmpty())
    {
        for (int i = 0; i <= defenceTower.size() - 1; i++)
        {
            defenceTower[i].showDeployRange(qp, OVERLAP);
        }
    }
}

bool map::checkOverlap(int x, int y)
{
    for (int i = 0; i <= defenceTower.size() - 1; i++)
    {

        if (((x - defenceTower[i].getXC()) * (x - defenceTower[i].getXC()) + (y - defenceTower[i].getYC()) * (y - defenceTower[i].getYC())) < (OVERLAP * OVERLAP))
        {
            return false;
        }
    }
    return true;
}

void map::npcMove(QVector<tower> &T)
{
    for (int i = 0; i <= npc.size() - 1; i++)
    {
        if (npc[i].isAI())
        {
            npc[i].move(T);
        }
        else
        {
            npc[i].move();
        }
    }
}

void map::npcPaint(QPainter &qp)
{
    for (int i = 0; i <= npc.size() - 1; i++)
    {
        npc[i].paint(qp);
    }
}

void map::towerAttack()
{
    for (int i = 0; i <= defenceTower.size() - 1; i++)
    {
        defenceTower[i].attack(npc);
    }
}

void map::towerPaint(QPainter &qp)
{
    for (int i = 0; i <= defenceTower.size() - 1; i++)
    {
        defenceTower[i].paint(qp, npc);
    }
}

void map::npcAttack()
{
    for (int i = 0; i <= npc.size() - 1; i++)
    {
        if (npc[i].dead() && npc[i].life > 0)
        {

            home.beAttacked(npc[i]);
            npc[i].life = 0;
        }
    }
}

void map::npcAward()
{
    for (int i = 0; i <= npc.size() - 1; i++)
    {
        if (npc[i].isKilled)
        {
            COIN.addcoin(npc[i].award);
            npc.remove(i);
            i--;
        }
    }
}

bool map::gameover()
{
    bool temp = true;
    for (int i = 0; i <= npc.size() - 1; i++)
    {
        temp = (temp && (npc[i].dead()));
    }
    return temp && waveManage.WAVE_NUM == COUNT_WAVE;
}

void map::deleteTower()
{
    for (int i = 0; i <= defenceTower.size() - 1; i++)
    {
        if (defenceTower[i].deletedMark)
        {
            defenceTower.remove(i);
            i--;
        }
    }
}

void map::resetCursor()
{
    setCursor(Qt::ArrowCursor);
    allowDeploy = false;
    towerControl = "";
    update();
}
