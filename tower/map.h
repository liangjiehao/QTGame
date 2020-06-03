#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPushButton>
#include <enemy.h>
#include "tower.h"
#include <QVector>
class map : public QWidget{
public:
    map(QWidget *parent = 0);
    void start();
    bool gameover();
    void npcMove();
    void npcPaint(QPainter & qp);
public slots:
        void init();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

private:
    QPushButton startButton;
    static const int DELAY = 140;
    static const int B_WIDTH = 1920;
    static const int B_HEIGHT = 1080;
    static const int LEN = 1000;
    static const int ENEMY_NUM = 10;
    int x;
    int y;
    int count;
    int step;
    int timeID;

    QVector <enemy> npc;
    tower defenceTower;
};

#endif // MAP_H
