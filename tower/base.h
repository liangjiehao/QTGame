#ifndef BASE_H
#define BASE_H
#include "enemy.h"
#include <QImage>
class base{
public:
    base(int base=BASE);
    void beAttacked(enemy & npc);
    void paint(QPainter & qp);
    void reset();
    int _base;
private:
    static const int BASE=12000;
    QImage homebase;
    int x;
    int y;
};

#endif // BASE_H
