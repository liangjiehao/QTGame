#include "tower.h"
#include <QPainter>
#include <QDebug>
tower::tower(int x,int y):x(x),y(y){
    tow.load("tow1.png");
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
    for (int i=0;i<=npc.size()-1;i++){
        if (checkEnemy(npc[i]) && !npc[i].dead()){
           qp.drawLine(npc[i].x+5,npc[i].y+5,x,y);
           //qDebug()<<power<<endl;
        }

    }
}
