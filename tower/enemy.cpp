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
    dot.load("xiaobing.png");
    x=400;
    y=500;
    step=20;
    life=LIFE;
    //qDebug()<<"npc"<<endl;
}

void enemy::move(){
    if (x<=640 || x >=1000 || y==700){
        if (x==1000 && y != 500){
            y-=step;
        }
        else{
            x+=step;
        }

    }
    else if (x==660){
        y+=step;
    }

}

void enemy::paint(QPainter &qp){
    if (!dead()){
        qp.drawImage(x,y,dot);
    }

    QPointF p;
    p.setX(x);
    p.setY(y+70);
    //qDebug()<<life<<endl;
    if (!dead()){
        qp.drawText(p,QString::number(life));
    }
}

bool enemy::dead(){
    return (x<1500 ? false :true)||(life<=0);
}

void enemy::damage(int power){
    //qDebug()<<life<<endl;
    life-=power;
    //qDebug()<<life<<endl;
}
