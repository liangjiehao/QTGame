#include "tower.h"
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QWidget>
#include <QSize>
#include <QObject>
#include "map.h"
#include <QPropertyAnimation>

tower::tower(QWidget * parent,int x,int y,int _power,int _range,QString type)
    :towParent(parent),type(type),range(_range),power(_power),x(x),y(y){
    //qDebug()<<"old tower position:"<<x<<' '<<y<<endl;
    if (this->type=="red"){
        tow.load(":/new/redtow.png");
        towType=QIcon(":/new/redtow.png");
    }
    else if (this->type=="blue"){
        tow.load(":/new/bluetow.png");
        towType=QIcon(":/new/bluetow.png");
    }
    else{
        tow.load(":/new/xiaobing.png");
        towType=QIcon(":/new/xiaobing.png");
    }
    setPosition();
    //qDebug()<<"icon size:"<<towType.actualSize(QSize(100,200)).width()<<' '
           //<<towType.actualSize(QSize(100,200)).height()<<endl;
    this->setParent(towParent);
    this->setIcon(towType);
    this->setIconSize(towType.actualSize(QSize(100,200)));
    this->move(this->x,this->y);
    //qDebug()<<"new tower position:"<<this->x<<' '<<this->y<<endl;
    func();

}

tower::tower(const tower & T):QPushButton(),towParent(T.towParent),range(T.range),power(T.power),x(T.x),y(T.y){
    tow=T.tow;
    type=T.type;
    towType=T.towType;
    singleMode=T.singleMode;
    setParent(towParent);
    setIcon(towType);
    setIconSize(towType.actualSize(QSize(100,200)));
    move(x,y);
    func();
    //qDebug()<<"copy tower position:"<<this->x<<' '<<this->y<<endl;
}

void tower::setSingleMode(){
    singleMode=true;
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
    singleMode=T.singleMode;
    setParent(towParent);
    setIcon(towType);
    setIconSize(towType.actualSize(QSize(100,200)));
    move(x,y);
    func();
    //qDebug()<<"= tower position:"<<this->x<<' '<<this->y<<endl;
}

void tower::func(){
    connect(this,&QPushButton::clicked,this,&tower::towerFunc);
    connect(&updateTower,&QPushButton::clicked,this,&tower::updateTowerFun);
    connect(&deleteTower,&QPushButton::clicked,this,&tower::deleteTowerFun);
}

void tower::setPosition(){
    x -= (towType.actualSize(QSize(100,200)).width()/2+5);
    y -= (towType.actualSize(QSize(100,200)).height()/2+5);
}

bool tower::checkEnemy(enemy & npc){
    return (range*range)>((npc.x-x)*(npc.x-x)+(npc.y-y)*(npc.y-y));
}

void tower::attack(QVector <enemy> & npc){
    QPropertyAnimation *testAnimation = new QPropertyAnimation(this,"pos");
    testAnimation->setDuration(10000);
    testAnimation->setStartValue(QPoint(300,300));
    testAnimation->setEndValue(QPoint(800,800));
    testAnimation->start();

    if (type=="single"){
        for (int i=0;i<=npc.size()-1;i++){
            if (checkEnemy(npc[i]) && !npc[i].dead()){
                npc[i].damage(power);
                break;
            }
        }
    }
    else {
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
    if (type=="single"){
        pen.setColor("green");
    }
    else{
        pen.setColor(type);
    }

    pen.setWidthF(2);
    qp.setPen(pen);
    //qp.drawLine(100,100,200,200);
    for (int i=0;i<=npc.size()-1;i++){
        if (checkEnemy(npc[i]) && !npc[i].dead()){
           //qDebug()<<"tower attack position:"<<x<<' '<<y<<endl;
           qp.drawLine(npc[i].x+npc[i].getWidth()/2,npc[i].y+npc[i].getHeight()/2,x+11,y+2);
           if (type=="single"){
               break;
           }
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

void tower::towerFunc(){
    if (funcControl){
        updateTower.setParent(towParent);
        updateTower.move(x+50,y);
        updateTower.setText("update");
        updateTower.show();

        deleteTower.setParent(towParent);
        deleteTower.move(x+50,y+50);
        deleteTower.setText("delete");
        deleteTower.show();

        funcControl=false;
    }
    else {
        updateTower.hide();
        deleteTower.hide();
        funcControl=true;
    }
}

void tower::updateTowerFun(){
    this->power *= 2;
    this->range += 100;
    map* mappt=dynamic_cast<map*>(towParent);
    mappt->COIN.consumecoin(50);
    mappt->update();
    //qDebug()<<"update";
}

void tower::deleteTowerFun(){
    map* mappt=dynamic_cast<map*>(towParent);
    deletedMark=true;
    mappt->deleteTower();
    mappt->update();
}
