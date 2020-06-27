#include "tower.h"
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QTimer>
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
        tow.load(":/new/yasuo.png");
        towType=QIcon(":/new/yasuo.png");

    }

    updateTower.setIcon(QIcon(":/new/update.png"));
    updateTower.setParent(towParent);

    deleteTower.setIcon(QIcon(":/new/delete.png"));
    deleteTower.setParent(towParent);

    hasaki.setIcon(QIcon(":/new/hasaki.png"));
    hasaki.setIconSize(QSize(200,200));
    hasaki.setParent(towParent);

    ring.setIcon(QIcon(":/new/chaojibing.png"));
    ring.setIconSize(QSize(200,200));
    ring.setParent(towParent);

    setPosition();
    //qDebug()<<"icon size:"<<towType.actualSize(QSize(100,200)).width()<<' '
           //<<towType.actualSize(QSize(100,200)).height()<<endl;
    this->resize(towType.actualSize(QSize(300,300)));
    this->setParent(towParent);
    this->setIcon(towType);
    this->setIconSize(towType.actualSize(QSize(300,300)));
    this->move(this->x,this->y);
    //qDebug()<<"new tower position:"<<this->x<<' '<<this->y<<endl;
    func();

}

tower::tower(const tower & T):QPushButton(),towParent(T.towParent),range(T.range),power(T.power),x(T.x),y(T.y){
    tow=T.tow;
    type=T.type;
    towType=T.towType;
    singleMode=T.singleMode;

    updateTower.setIcon(QIcon(":/new/update.png"));
    updateTower.setParent(towParent);

    deleteTower.setIcon(QIcon(":/new/delete.png"));
    deleteTower.setParent(towParent);

    hasaki.setIcon(QIcon(":/new/hasaki.png"));
    hasaki.setIconSize(QSize(200,200));
    hasaki.setParent(towParent);


    ring.setIcon(QIcon(":/new/chaojibing.png"));
    ring.setIconSize(QSize(200,200));
    ring.setParent(towParent);


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

    updateTower.setIcon(QIcon(":/new/update.png"));
    updateTower.setParent(towParent);

    deleteTower.setIcon(QIcon(":/new/delete.png"));
    deleteTower.setParent(towParent);

    hasaki.setIcon(QIcon(":/new/hasaki.png"));
    hasaki.setIconSize(QSize(200,200));
    hasaki.setParent(towParent);

    ring.setIcon(QIcon(":/new/chaojibing.png"));
    ring.setIconSize(QSize(200,200));
    ring.setParent(towParent);


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

bool tower::checkEnemy(enemy & npc, bool ai){
    int temp_range=range;
    if (ai){
        temp_range+=50;
    }
    return (temp_range*temp_range)>((npc.x-x)*(npc.x-x)+(npc.y-y)*(npc.y-y));
}

void tower::attack(QVector <enemy> & npc){
    //QPropertyAnimation *testAnimation = new QPropertyAnimation(&hasaki,"pos",dynamic_cast<map*>(towParent));
    //hasaki.hide();
    //ring.hide();
    if (type=="single"){
        for (int i=0;i<=npc.size()-1;i++){
            if (!npc[i].dead() && checkEnemy(npc[i]) ){


                hasaki.show();
                QPropertyAnimation *testAnimation = new QPropertyAnimation(&hasaki,"geo");
                testAnimation->setDuration(400);
                //testAnimation->setStartValue(QRectF(getXL(),getYL(),20,20));
                testAnimation->setEndValue(QRectF(npc[i].x-npc[i].getWidth(),npc[i].y-npc[i].getHeight(),100,100));
                testAnimation->setEndValue(QRectF(npc[i].x-npc[i].getWidth(),npc[i].y-npc[i].getHeight(),150,150));
                //testAnimation->setEndValue(QRectF(getXL()-50,getYL()-50,150,150));
                testAnimation->start();
                //testAnimation->state();
                //QTimer::singleShot(700,&hasaki,&QPushButton::hide);
                npc[i].damage(power);
                if (npc[i].life<=0 && !npc[i].isKilled){
                    map* mappt=dynamic_cast<map*>(towParent);
                    mappt->COIN.addcoin(npc[i].award);
                    //qDebug()<<npc[i].award;
                    npc[i].isKilled=true;
                }
                break;
            }
        }
    }
    else {
        for (int i=0;i<=npc.size()-1;i++){
            //bool firstMark=true;
            if (!npc[i].dead() && checkEnemy(npc[i])){

                QTime time = QTime::currentTime();
                qsrand(time.msec()+time.second()*1000);
                //qsrand(13);
                //int m=0;
                int n = power;
                bool ignore_defence=false;
                if (type=="blue"){
                    n+=(qrand() % 50);
                    ignore_defence=true;
                }

                if ((qrand() % 20 )==1 && type=="red"){
                    n=npc[i].life;
                    ignore_defence=true;
                }

               npc[i].damage(n,ignore_defence);
               if (npc[i].life<=0 && !npc[i].isKilled){
                   map* mappt=dynamic_cast<map*>(towParent);
                   mappt->COIN.addcoin(npc[i].award);
                   //qDebug()<<npc[i].award;
                   npc[i].isKilled=true;
               }
                /*
               if (firstMark){
                   firstMark=false;
                   ring.show();
                   //ring.move(x,y);
                   QPropertyAnimation *testAnimation = new QPropertyAnimation(&ring,"geo");
                   testAnimation->setDuration(500);
                   testAnimation->setStartValue(QRectF(getXL()-50,getYL(),20,20));
                   testAnimation->setEndValue(QRectF(getXL()-50,getYL(),range*2,range*2));
                   testAnimation->start();
               }*/


               //qDebug()<<power<<endl;
            }

        }
    }


}

void tower::paint(QPainter &qp){
    //qp.drawImage(x,y,tow);
    //Q_UNUSED(qp);
    Q_UNUSED(qp)
    QPushButton::show();

}

void tower::paint(QPainter &qp,QVector<enemy>&npc){
    //qp.drawImage(x,y,tow);
    //this->lower();
    QPushButton::show();
    //hasaki.hide();

    QPen pen;
    if (type=="single"){
        return;
    }
    else{
        pen.setColor(type);
    }

    pen.setWidthF(2);
    qp.setPen(pen);
    //qp.drawLine(100,100,200,200);
    for (int i=0;i<=npc.size()-1;i++){
        if (!npc[i].dead() && checkEnemy(npc[i]) ){
           //qDebug()<<"tower attack position:"<<x<<' '<<y<<endl;
           qp.drawLine(npc[i].x+npc[i].getWidth()/2,npc[i].y+npc[i].getHeight()/2,x+20,y+40);
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
    pen.setColor("red");
    pen.setWidth(4);
    qp.setPen(pen);

    //qp.drawLine(100,100,200,200);
    //qp.drawEllipse(x-range+towType.actualSize(QSize(200,200)).width()/2,y-range,2*range,2*range);
    qp.drawEllipse(x-range,y-range,2*range,2*range);
    //qDebug()<<"painted!!!";
}

void tower::towerFunc(){
    if (funcControl){
        updateTower.setParent(towParent);
        updateTower.setIconSize(QSize(50,50));
        updateTower.move(x+60,y);
        //updateTower.setText("update");
        updateTower.show();

        deleteTower.setParent(towParent);
        deleteTower.setIconSize(QSize(50,50));
        deleteTower.move(x+60,y+50);
        //deleteTower.setText("delete");
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
    this->power *= 1.2;
    this->range += 50;
    map* mappt=dynamic_cast<map*>(towParent);
    mappt->COIN.consumecoin(100*updateWeight);
    mappt->update();
    updateWeight*=2;
    //qDebug()<<"update";
}

void tower::deleteTowerFun(){
    map* mappt=dynamic_cast<map*>(towParent);
    deletedMark=true;
    mappt->deleteTower();
    mappt->update();
}
