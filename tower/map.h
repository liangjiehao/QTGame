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
    base home;
public slots:
        void init();
        void deploy();
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QPushButton startButton;
    QPushButton deployTower;
    static const int DELAY = 140;
    static const int B_WIDTH = 1920;
    static const int B_HEIGHT = 1080;
    static const int LEN = 1000;
    static const int ENEMY_NUM = 20;
    int TOWER_NUM = 5;
    int x;
    int y;
    int count;
    int step;
    int timeID;
    int timeID1;
    bool allowDeploy;
    QVector <enemy> npc;
    QVector <tower> defenceTower;
};

#endif // MAP_H
