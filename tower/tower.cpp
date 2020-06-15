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
    this->setParent(towParent);
    this->setIcon(towType);
    this->setIconSize(towType.actualSize(QSize(100,200)));
    this->move(this->x,this->y);
    //qDebug()<<"new tower position:"<<this->x<<' '<<this->y<<endl;
    //func();

}

tower::tower(const tower & T):QPushButton(),towParent(T.towParent),range(T.range),power(T.power),x(T.x),y(T.y){
    tow=T.tow;
    type=T.type;
    towType=T.towType;
    setParent(towParent);
    setIcon(towType);
    setIconSize(towType.actualSize(QSize(100,200)));
    move(x,y);
    //qDebug()<<"copy tower position:"<<this->x<<' '<<this->y<<endl;
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
    setParent(towParent);
    setIcon(towType);
    setIconSize(towType.actualSize(QSize(100,200)));
    move(x,y);
    //qDebug()<<"= tower position:"<<this->x<<' '<<this->y<<endl;
}

void tower::func(){
    connect(this,&QPushButton::clicked,this,&tower::updateTowerFun);
}

void tower::setPosition(){
    x -= (towType.actualSize(QSize(100,200)).width()/2+5);
    y -= (towType.actualSize(QSize(100,200)).height()/2+5);
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
    //qp.drawImage(x,y,tow);
    //Q_UNUSED(qp);
    QPushButton::show();

}

void tower::paint(QPainter &qp,QVector<enemy>&npc){
    //qp.drawImage(x,y,tow);

    QPushButton::show();

    QPen pen;
    pen.setColor(type);
    pen.setWidthF(2);
    qp.setPen(pen);
    //qp.drawLine(100,100,200,200);
    for (int i=0;i<=npc.size()-1;i++){
        if (checkEnemy(npc[i]) && !npc[i].dead()){
           //qDebug()<<"tower attack position:"<<x<<' '<<y<<endl;
           qp.drawLine(npc[i].x+20,npc[i].y+20,x+11,y+2);

        }

    }
}
/*
void tower::paintEvent(QPaintEvent * e){
    QPainter qp(towParent);
    QPen pen;
    pen.setColor("red");
    qp.setPen(pen);
    qp.drawLine(100,100,200,200);
    qp.drawEllipse(500,500,500,500);
    qDebug()<<"painted!!!";
}
*/
void tower::showDeployRange(QPainter & qp,int range){
    //QPainter qp(this->towParent);
    QPen pen;
    pen.setColor("green");
    qp.setPen(pen);
    //qp.drawLine(100,100,200,200);
    //qp.drawEllipse(x-range+towType.actualSize(QSize(200,200)).width()/2,y-range,2*range,2*range);
    qp.drawEllipse(x-range,y-range,2*range,2*range);
    //qDebug()<<"painted!!!";
}

void tower::updateTowerFun(){
    if (funcControl){
        updateTower.setParent(towParent);
        updateTower.move(x+50,y);
        updateTower.setText("update");
        updateTower.show();
        funcControl=false;
    }
    else {
        updateTower.hide();
        funcControl=true;
    }

    qDebug()<<"update";
}

void tower::deleteTowerFun(){
    deleteTower.setParent(towParent);
    deleteTower.move(x+50,y+50);
    deleteTower.setText("delete");
    deleteTower.show();
}
