#include "tower.h"
#include <QPainter>
#include <QDebug>
#include <QTime>
tower::tower(int x,int y,int _power,int _range):range(_range),power(_power),x(x),y(y){
    if (range>=300){
        tow.load(":/new/redtow.png");
        type="red";
    }
    else {
        tow.load(":/new/bluetow.png");
        type="blue";
    }

}

bool tower::checkEnemy(enemy & npc){
    return (range*range)>((npc.x-x)*(npc.x-x)+(npc.y-y)*(npc.y-y));
}

void tower::attack(QVector <enemy> & npc){
    for (int i=0;i<=npc.size()-1;i++){
        if (checkEnemy(npc[i])){

            QTime time = QTime::currentTime();
            qsrand(time.msec()+time.second()*1000);
            //qsrand(13);
            //int m=0;
            int n = power;
            if (type=="blue"){
                n+=(qrand() % 20);
            }

            if ((qrand() % 67 )==1 && type=="red"){
                n=npc[i].life;
            }

           npc[i].damage(n);
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
