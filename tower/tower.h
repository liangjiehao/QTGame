#ifndef TOWER_H
#define TOWER_H

#include <QImage>
#include "enemy.h"
#include <QPushButton>

class tower{
public:
    QImage tow;
    QIcon towType;
    QPushButton towerButton;
    tower(QWidget * parent=NULL,int x=800,int y=450,int _power = 30,int _range = 200);
    tower(const tower &);
    void operator=(const tower &);
    bool checkEnemy(enemy & npc);
    void attack(QVector <enemy> & npc);
    void paint(QPainter & qp, QVector<enemy>&npc);
    void paint(QPainter &qp);
    int getX(){return x;}
    int getY(){return y;}
private:

    QWidget * towParent;
    static const int gap = 200;
    QString type;
    int range = 300;
    int power;
    int x;
    int y;
};

#endif // TOWER_H
