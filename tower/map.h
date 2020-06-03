#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPushButton>
#include <enemy.h>
#include "tower.h"

class map : public QWidget{
public:
    map(QWidget *parent = 0);
    void start();
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

    int x;
    int y;
    int count;
    int step=0;
    int timeID;
    enemy npc;
    tower defenceTower;
};

#endif // MAP_H
