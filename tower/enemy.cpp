#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTime>
#include <QPushButton>
#include "enemy.h"
#include <QDebug>
enemy::enemy(int life):life(life){
    dot.load("xiaobing.png");
    x=400;
    y=500;
    step=20;
}

void enemy::init(){
    dot.load("dot.png");
    x=400;
    y=500;
    step=20;
    life=LIFE;
    qDebug()<<"npc"<<endl;
}

void enemy::move(){
    x+=step;
}

void enemy::paint(QPainter &qp){
    qp.drawImage(x,y,dot);
    QPointF p;
    p.setX(x);
    p.setY(y+100);
    //qDebug()<<life<<endl;
    if (life<=0)
        qp.drawText(p,"X");
    else{
        qp.drawText(p,QString::number(life));
    }

}

bool enemy::dead(){
    return (x<1500 ? false :true)|(life<=0);
}

void enemy::damage(int power){
    //qDebug()<<life<<endl;
    life-=power;
    //qDebug()<<life<<endl;
}
