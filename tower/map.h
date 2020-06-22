#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPushButton>
#include <enemy.h>
#include "tower.h"
#include <QVector>
#include "base.h"
class map : public QWidget{
public:
    map(QWidget *parent = 0);
    void start();
    bool gameover();
    void npcMove();
    void npcPaint(QPainter & qp);
    void towerAttack();
    void towerPaint(QPainter & qp);
    bool isactive = false;
    void countDeployedTower();
    void npcAttack();
    void reset();
    void drawBackGround(QPainter & qp,QString map);
    bool checkOverlap(int,int);
    void initMain();
    void initenemy();
<<<<<<< HEAD
    base home;
    QString BG;
    QString pageControl;
=======
    void showTowerRange(QPainter &);
    base home;
    QString BG;
    QString pageControl,towerControl;
>>>>>>> dev
public slots:
        void init();
        void initEasy();
        void initHard();
        void initEvil();
        void deploy();
        void deploy_high();
        void restart();
        void displayRule();
        void selectChapter();
        void backToMain();
        void setButton();
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QImage backGround;
    QPushButton startButton;
    QPushButton deployTower;
    QPushButton deployTowerHigh;
    QPushButton reStart;
    QPushButton enterGame;
    QPushButton showRule;
    QPushButton backTo;
    QPushButton easy,hard,evil;
    static const int DELAY = 140;
    static const int B_WIDTH = 1920;
    static const int B_HEIGHT = 1080;
    static const int LEN = 1000;
    static const int OVERLAP =150;
    int ENEMY_NUM = 20;
    int TOWER_NUM = 5;
    int x;
    int y;
    int count;
    int step;
    int timeID;
    int timeID1;
    bool allowDeploy;
    int setPower;
    int setRange;
    QVector <enemy> npc;
    QVector <tower> defenceTower;
    enemy test;
};

#endif // MAP_H
