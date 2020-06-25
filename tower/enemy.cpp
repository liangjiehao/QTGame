#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTime>
#include <QPushButton>
#include "enemy.h"
#include <QDebug>
#include <QVector2D>

enemy::enemy(int life,int defence,int attack,int type):QPushButton(){
    if (type==0){
        dot.load(":/new/xiaobing.png");


    }
    else if (type==1){
        dot.load(":/new/chaojibing.png");
    }
    this->life=life;
    this->defence=defence;
    this->attack=attack;
    x=_X;
    y=_Y;
    step=20;
    count_step=0;

    makePathPoint();
    makePathDirection();

}

enemy::enemy(const enemy& p):QPushButton(){
    x=p.x;
    y=p.y;
    step=p.step;
    dot=p.dot;
    life=p.life;
    defence=p.defence;
    attack=p.attack;
    path_point=p.path_point;
    path_direction=p.path_direction;
    count_step=p.count_step;
}

void enemy::operator=(const enemy& p){
    x=p.x;
    y=p.y;
    step=p.step;
    dot=p.dot;
    life=p.life;
    defence=p.defence;
    attack=p.attack;
    path_point=p.path_point;
    path_direction=p.path_direction;
    count_step=p.count_step;
}

void enemy::init(){
    dot.load(":/new/chaojibing.png");
    x=_X;
    y=_Y;
    step=20;
    life=LIFE;
    //qDebug()<<"npc"<<endl;
}

void enemy::move(){
    /*
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
    }*/
    //qDebug()<<path_direction.size();
    //qDebug()<<count_step;
    if (count_step<path_direction.size()){
        x+=path_direction[count_step].x()*step;
        y+=path_direction[count_step].y()*step;
        //qDebug()<<x<<" "<<y<<" "<<path_direction[count_step].x()<<" "<<path_direction[count_step].y();
        count_step++;
    }
    //qDebug()<<path_direction.size();


}

void enemy::paint(QPainter &qp){
    if (!dead()){
        qp.drawImage(x,y,dot);
        QFont F;
        F.setPointSize(10);
        QPointF p;

        p.setX(x);
        p.setY(y+dot.size().height());
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
    //qDebug()<<power*(1-defence/1000.0)<<" power "<<power<<" defence "<<defence;
    life-=(power*(1-defence/1000.0));
    //qDebug()<<life<<endl;
}

void enemy::makePathPoint(int type){
    path_point.clear();
    if (type==0){
        path_point.append(QPoint(100,100));
        path_point.append(QPoint(400,700));
        path_point.append(QPoint(800,400));
        path_point.append(QPoint(1400,700));
    }
}

void enemy::makePathDirection(){
    path_direction.clear();
    qDebug()<<path_point.size();
    for (int i=0;i<=path_point.size()-2;i++){
        QVector2D direct(path_point[i+1]-path_point[i]);

        double step_num=(direct.length())/((direct.normalized().length()*step));
        qDebug()<<direct.length()<<direct.normalized().length()<<step<<step_num;
        direct.normalize();
        for (int j=0;j<=step_num;j++){
            path_direction.append(direct);
        }
    }
}
