#ifndef TOWER_H
#define TOWER_H

#include <QImage>
#include "enemy.h"


class tower{
public:
    QImage tow;
    tower(int x=800,int y=450,int _power = 30,int _range = 200);
    bool checkEnemy(enemy & npc);
    void attack(QVector <enemy> & npc);
    void paint(QPainter & qp, QVector<enemy>&npc);
    void paint(QPainter &qp);
    int getX(){return x;}
    int getY(){return y;}
private:

    static const int gap = 200;
    QString type;
    int range = 300;
    int power;
    int x;
    int y;
};

#endif // TOWER_H
