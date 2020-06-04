#include "enemy.h"
#include "base.h"
#include <QPainter>
#include <QFont>
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
    QFont F;
    F.setPointSize(20);
    QPointF p;
    p.setX(x+15);
    p.setY(y+120);
    if (_base>0){
        qp.setPen("white");
        qp.setFont(F);
        qp.drawText(p,QString::number(_base));
    }

}

void base::reset(){
    _base=BASE;
}
