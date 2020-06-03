#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include <QPushButton>

class enemy{
public:
    enemy(int life = 1200);
    void move();
    void paint(QPainter & qp);
    bool dead();
    void damage(int power);
    QImage dot;
    int x;
    int y;
private:

    static const int LEN=100;
    int step;
    int timeID;
    int life;

};

#endif // ENEMY_H
