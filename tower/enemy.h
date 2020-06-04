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
private:

    static const int LEN=100;
    static const int LIFE=12000;
    int step;
    int timeID;
    int life;

};

#endif // ENEMY_H
