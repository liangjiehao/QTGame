#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPushButton>
#include <enemy.h>
#include "tower.h"
#include <QVector>
#include <QList>
#include "base.h"
#include "coin.h"
#include "manageenemy.h"
#include <QtMultimedia/qmediaplayer.h>
#include <QtMultimedia/qmediaplaylist.h>

class tower;
class map : public QWidget
{
public:
    map(QWidget *parent = 0);
    void start();
    bool gameover();
    void npcMove(QVector<tower> &);
    void npcPaint(QPainter &qp);
    void towerAttack();
    void towerPaint(QPainter &qp);
    bool isactive = false;
    void countDeployedTower();
    void npcAttack();
    void reset();
    void drawBackGround(QPainter &qp, QString map);
    bool checkOverlap(int, int);
    void initMain();
    void showTowerRange(QPainter &);
    void waveControl();
    void buyTower();
    void npcAward();
    void deleteTower();
    void setMedia(int num = 1);
    void initMedia();
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    base home;
    QString BG;
    QString pageControl, towerControl;
    coin COIN;

public slots:
    void init();
    void initEasy();
    void initHard();
    void initEvil();
    void deploy();
    void deploy_high();
    void deploy_hasaki();
    void restart();
    void displayRule();
    void selectChapter();
    void backToMain();
    void setButton();
    void initenemy();
    void resetCursor();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QImage backGround;
    QPushButton startButton;
    QPushButton deployTower;
    QPushButton deployTowerHigh;
    QPushButton deployTowerhasaki;
    QPushButton reStart;
    QPushButton enterGame;
    QPushButton showRule;
    QPushButton backTo;
    QPushButton easy, hard, evil;
    QPushButton recycle;
    QString currentTowerType;
    QPushButton defeat, victory;
    QPushButton coin_num;
    static const int DELAY = 140;
    static const int B_WIDTH = 1920;
    static const int B_HEIGHT = 1080;
    static const int LEN = 1000;
    static const int OVERLAP = 150;

    int TOWER_NUM = 5;
    int COUNT_WAVE = 0;

    int currentTowerCost;
    int x;
    int y;
    int count;
    int step;
    int timeID = 0;
    int timeID1 = 0;
    bool allowDeploy;
    int setPower;
    int setRange;
    QVector<enemy> npc;
    QVector<tower> defenceTower;
    enemy test;
    manageenemy waveManage;
    QVector<QVector<int>> wave;
    QVector<int> easyWave = {
        0, 0, 0, 0, 0, 0, 0,
        -1, -1, 1, 1, 0, 0, 0,
        -1, -1, 1, 1, 0, 0, 0, 1, 2};
    QVector<int> hardWave = {
        1, 1, 0, 0, 0, 0, 0, 0, 0, -1, -1, 1, 2, 1,
        0, 0, -1, -1, 1, 1, 2, 0, 0, 3, 3, 3, 0, -1, -1, 1,
        1, 2, 2, 2, 2, 0, 0

    };
    QVector<int> evilWave = {
        0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 3,
        3, 2, -1, -1, 1, 3, 2, 2, 1, 3, 0, 0, 0, 0,
        0, 2, 3, 2, 1, 1, 1, 3, 3, 3, 3, 3, 0, 0, 0, 1,
        -1, -1, 3, 2, 3, 3, 2, 3, 3, 3, 2, 0, 0

    };
};

#endif // MAP_H
