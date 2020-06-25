#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include <QPushButton>

class enemy:public QPushButton{
public:
    enemy(int life = LIFE,int defence=DEFENCE,int attack=ATTACK,int type=0);
    enemy(const enemy&);
    void operator=(const enemy&);
    void move();
    void paint(QPainter & qp);
    bool dead();
    void damage(int power);
    void init();
    int attack_amount(){return attack+life/2;};
    int getWidth()const{return dot.size().width();};
    int getHeight()const{return dot.size().height();};
    void makePathPoint(int type=0);
    void makePathDirection();
    QImage dot;
    double x;
    double y;
    int life;
private:

    static const int LEN=100;
    static const int LIFE=5000;
    static const int DEFENCE=200;
    static const int ATTACK=1000;
    static const int _X=100;   //200;//注意修改base
    static const int _Y=100;   //60;
    int defence;
    int attack;
    int step;
    int timeID;
    QVector<QPoint> path_point;
    QVector<QVector2D> path_direction;
    int count_step;

};

#endif // ENEMY_H
