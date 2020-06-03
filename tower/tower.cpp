#include "tower.h"
#include <QPainter>
#include <QDebug>
tower::tower(){
    tow.load("tow.png");
    x=800;
    y=200;
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
