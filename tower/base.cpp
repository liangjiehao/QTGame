#include "enemy.h"
#include "base.h"
#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QIcon>


base::base(int base,QWidget * pt):_base(base){
    x=1010;
    y=950;
    homebase.setIcon(QIcon(":/new/homebase.png"));
    homebase.setIconSize(QSize(70,70));
    homebase.move(80,120);
    homebase.setParent(pt);
    homebase.hide();

}

void base::beAttacked(enemy &npc){
    //qDebug()<<npc.attack_amount();
    _base-=(npc.attack_amount());
}

void base::paint(QPainter & qp){
    //qp.drawImage(x-homebase.width()/2+24,y-homebase.height()/2,homebase);
    //qp.drawImage(80,130,homebase);
    homebase.show();
    QFont F;
    F.setPointSize(30);
    F.setBold(true);
    F.setFamily("Helvetica");
    QPointF p;
    p.setX(170);
    p.setY(180);
    if (_base>0){
        if (_base<2000){
            qp.setPen("red");
        }
        else{
            qp.setPen("white");
        }
        qp.setFont(F);
        qp.drawText(p,"BASE:"+QString::number(_base));
    }

}

void base::reset(int baselife){
    _base=baselife;
}
