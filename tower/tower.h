#ifndef TOWER_H
#define TOWER_H

#include <QImage>
#include "enemy.h"
#include <QPushButton>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "animationpixmap.h"
#include <QLabel>

class tower : public QPushButton
{

public:
    tower(QWidget *parent = NULL, int x = 800, int y = 450, int _power = 30, int _range = 200, QString type = "red");
    tower(const tower &);
    void operator=(const tower &);
    bool checkEnemy(enemy &npc, bool ai = false);
    void attack(QVector<enemy> &npc);
    void paint(QPainter &qp, QVector<enemy> &npc);
    void setPosition();
    void paint(QPainter &qp);
    int getX() { return x; }
    int getY() { return y; }
    int getXC() { return x + towType.actualSize(QSize(100, 200)).width() / 2; }
    int getYC() { return y + towType.actualSize(QSize(100, 200)).height() / 2; }
    int getXL() { return x - towType.actualSize(QSize(100, 200)).width() / 2; }
    int getYL() { return y - towType.actualSize(QSize(100, 200)).height() / 2; }
    void func();
    void showDeployRange(QPainter &, int range = 200);
    void setSingleMode();
    bool deletedMark = false;
    QImage tow;
    QIcon towType;
    animationPixmap hasaki, ring;
    int updateWeight = 1;
public slots:
    void updateTowerFun();
    void deleteTowerFun();
    void towerFunc();

private:
    QPushButton updateTower, deleteTower;
    QWidget *towParent;
    bool funcControl = true;
    bool singleMode = false;
    static const int gap = 200;
    QString type;
    int range = 300;
    int power;
    int x;
    int y;
};

#endif // TOWER_H
