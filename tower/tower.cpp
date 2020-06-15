#include "tower.h"
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QWidget>
#include <QSize>
#include <QObject>

tower::tower(QWidget * parent,int x,int y,int _power,int _range)
    :towParent(parent),range(_range),power(_power),x(x),y(y){
    //qDebug()<<"old tower position:"<<x<<' '<<y<<endl;
    if (range>=300){
        tow.load(":/new/redtow.png");
        towType=QIcon(":/new/redtow.png");
        type="red";
    }
    else {
        tow.load(":/new/bluetow.png");
        towType=QIcon(":/new/bluetow.png");
        type="blue";
    }
    setPosition();
    //qDebug()<<"icon size:"<<towType.actualSize(QSize(100,200)).width()<<' '
           //<<towType.actualSize(QSize(100,200)).height()<<endl;
    towerButton.setParent(towParent);
    towerButton.setIcon(towType);
    towerButton.setIconSize(towType.actualSize(QSize(100,200)));
    towerButton.move(this->x,this->y);
    //qDebug()<<"new tower position:"<<this->x<<' '<<this->y<<endl;

}

tower::tower(const tower & T):towParent(T.towParent),range(T.range),power(T.power),x(T.x),y(T.y){
    tow=T.tow;
    type=T.type;
    towType=T.towType;
    towerButton.setParent(towParent);
    towerButton.setIcon(towType);
    towerButton.setIconSize(towType.actualSize(QSize(100,200)));
    towerButton.move(x,y);
}

void tower::operator=(const tower & T){
    tow =T.tow;
    type =T.type;
    towType =T.towType;
    towParent =T.towParent;
    range=T.range;
    power=T.power;
    x=T.x;
    y=T.y;
    towerButton.setParent(towParent);
    towerButton.setIcon(towType);
    towerButton.setIconSize(towType.actualSize(QSize(100,200)));
    towerButton.move(x,y);
}

void tower::func(){
    QObject::connect(&updateTower,&QPushButton::clicked,this,&tower::updateTower);
}

void tower::setPosition(){
    x -= towType.actualSize(QSize(100,200)).width()/2;
    y -= towType.actualSize(QSize(100,200)).height()/2;
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
    //Q_UNUSED(qp);
    //towerButton.show();
    //towerButton.lower();
}

void tower::paint(QPainter &qp,QVector<enemy>&npc){
    qp.drawImage(x,y,tow);

    //towerButton.show();
    //towerButton.lower();
    QPen pen;
    pen.setColor(type);
    pen.setWidthF(2);
    qp.setPen(pen);
    for (int i=0;i<=npc.size()-1;i++){
        if (checkEnemy(npc[i]) && !npc[i].dead()){
           qDebug()<<"tower attack position:"<<x<<' '<<y<<endl;
           qp.drawLine(npc[i].x+20,npc[i].y+20,x+11,y+2);

        }

    }
}

void tower::updateTowerFun(){
    updateTower.setParent(towParent);
    updateTower.move(x+50,y);
    updateTower.setText("update");
    updateTower.show();
}

void tower::deleteTowerFun(){
    deleteTower.setParent(towParent);
    deleteTower.move(x+50,y+50);
    deleteTower.setText("delete");
    deleteTower.show();
}
