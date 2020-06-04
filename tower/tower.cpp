#include "tower.h"
#include <QPainter>
#include <QDebug>
tower::tower(int x,int y,int _power,int _range):range(_range),power(_power),x(x),y(y){
    if (range>=300){
        tow.load("redtow.png");
        type="red";
    }
    else {
        tow.load("bluetow.png");
        type="blue";
    }
}

bool tower::checkEnemy(enemy & npc){
    return (range*range)>((npc.x-x)*(npc.x-x)+(npc.y-y)*(npc.y-y));
}

void tower::attack(QVector <enemy> & npc){
    for (int i=0;i<=npc.size()-1;i++){
        if (checkEnemy(npc[i])){
           npc[i].damage(power);
           //qDebug()<<power<<endl;
        }

    }

}

void tower::paint(QPainter &qp){
    qp.drawImage(x,y,tow);
}

void tower::paint(QPainter &qp,QVector<enemy>&npc){
    qp.drawImage(x,y,tow);
    QPen pen;
    pen.setColor(type);
    pen.setWidthF(2);
    qp.setPen(pen);
    for (int i=0;i<=npc.size()-1;i++){
        if (checkEnemy(npc[i]) && !npc[i].dead()){
           qp.drawLine(npc[i].x+20,npc[i].y+20,x,y);
           //qDebug()<<power<<endl;
        }

    }
}
