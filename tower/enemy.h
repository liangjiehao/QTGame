#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include <QPushButton>

class enemy{
public:
    enemy();
    void move();
    void paint(QPainter & qp);
    bool dead();
    QImage dot;
private:

    static const int LEN=100;
    int x;
    int y;
    int step;
    int timeID;

};

#endif // ENEMY_H
