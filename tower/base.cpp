#include "enemy.h"
#include "base.h"
#include <QPainter>
#include <QFont>
#include <QDebug>


base::base(int base):_base(base){
    homebase.load(":/new/base0.png");
    x=400;
    y=550;
}

void base::beAttacked(enemy &npc){
    //qDebug()<<npc.life;
    _base-=(npc.attack_amount());
}

void base::paint(QPainter & qp){
    qp.drawImage(x,y,homebase);
    QFont F;
    F.setPointSize(20);
    QPointF p;
    p.setX(x+15);
    p.setY(y+150);
    if (_base>0){
        if (_base<2000){
            qp.setPen("red");
        }
        else{
            qp.setPen("green");
        }
        qp.setFont(F);
        qp.drawText(p,QString::number(_base));
    }

}

void base::reset(int baselife){
    _base=baselife;
}
