#ifndef TOWER_H
#define TOWER_H

#include <QImage>
#include "enemy.h"


class tower{
public:
    QImage tow;
    tower();
    bool checkEnemy(enemy & npc);
    void attack(enemy & npc);
    void paint(QPainter & qp);
private:
    static const int power = 50;
    static const int gap = 200;
    static const int range = 400;
    int x;
    int y;
};

#endif // TOWER_H
