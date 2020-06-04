#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include <QPushButton>

class enemy{
public:
    enemy(int life = LIFE);
    void move();
    void paint(QPainter & qp);
    bool dead();
    void damage(int power);
    void init();
    QImage dot;
    int x;
    int y;
    int life;
private:

    static const int LEN=100;
    static const int LIFE=5000;
    static const int _X=200;//注意修改base
    static const int _Y=60;
    int step;
    int timeID;


};

#endif // ENEMY_H
