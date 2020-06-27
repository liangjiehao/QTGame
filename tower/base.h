#ifndef BASE_H
#define BASE_H
#include "enemy.h"
#include <QImage>
#include <QPushButton>
class base{
public:
    base(int base=BASE,QWidget * pt=0);
    void beAttacked(enemy & npc);
    void paint(QPainter & qp);
    void reset(int base=BASE);
    void hide(){homebase.hide();};
    int _base;
private:
    static const int BASE=8000;
    QPushButton homebase;
    int x;
    int y;
};

#endif // BASE_H
