#include "enemy.h"
#include "base.h"
#include <QPainter>

base::base(int base):_base(base){
    homebase.load("base.png");
    x=400;
    y=600;
}

void base::beAttacked(enemy &npc){
    _base-=(npc.life/2);
}

void base::paint(QPainter & qp){
    qp.drawImage(x,y,homebase);
    QPointF p;
    p.setX(x+40);
    p.setY(y+100);
    if (_base>0){
        qp.drawText(p,QString::number(_base));
    }

}

void base::reset(){
    _base=BASE;
}
