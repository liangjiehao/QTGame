#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTime>
#include <QPushButton>
#include "enemy.h"
#include <QDebug>
<<<<<<< HEAD
enemy::enemy(int life):life(life){
=======

enemy::enemy(int life):QPushButton(),life(life){
>>>>>>> dev
    dot.load(":/new/xiaobing.png");
    x=_X;
    y=_Y;
    step=20;
}

enemy::enemy(const enemy& p):QPushButton(){
    x=p.x;
    y=p.y;
    step=20;
    dot=p.dot;
    life=p.life;
}

void enemy::operator=(const enemy& p){
    x=p.x;
    y=p.y;
    step=20;
    dot=p.dot;
    life=p.life;
}

void enemy::init(){
    dot.load(":/new/xiaobing.png");
    x=_X;
    y=_Y;
    step=20;
    life=LIFE;
    //qDebug()<<"npc"<<endl;
}

void enemy::move(){
    if (y==_Y && x<1500){
        x+=step;
    }
    else if(x==1500 && y<860){
        y+=step;
    }
    else if(y==860 && x>_X){
        x-=step;
    }
    else if(x== _X && y>_Y+180){
        y-=step;
    }
    else if (y==_Y+180 && x<1200){
        x+=step;
    }
    else if (x==1200 && y<600){
        y+=step;
    }
    else if (y==600 && x>_X+300){
        x-=step;
    }

}

void enemy::paint(QPainter &qp){
    if (!dead()){
        qp.drawImage(x,y,dot);
        QFont F;
        F.setPointSize(10);
        QPointF p;
        p.setX(x);
        p.setY(y+70);
        if (life<=2000){
            qp.setPen("red");
        }
        else {
            qp.setPen("white");
        }
        qp.setFont(F);
        qp.drawText(p,QString::number(life));
    }
}

bool enemy::dead(){
    if ((x==_X+300 && y==600) || (life<=0)){
        return true;
    }
    else return false;

}

void enemy::damage(int power){
    //qDebug()<<life<<endl;
    life-=power;
    //qDebug()<<life<<endl;
}
