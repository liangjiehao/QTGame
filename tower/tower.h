#ifndef TOWER_H
#define TOWER_H

#include <QImage>
#include "enemy.h"


class tower{
public:
    QImage tow;
    tower(int x=800,int y=450);
    bool checkEnemy(enemy & npc);
    void attack(QVector <enemy> & npc);
    void paint(QPainter & qp, QVector<enemy>&npc);
    void paint(QPainter &qp);
private:
    static const int power = 30;
    static const int gap = 200;
    static const int range = 300;
    int x;
    int y;
};

#endif // TOWER_H
