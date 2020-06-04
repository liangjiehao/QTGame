#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>
#include <QImage>

map::map(QWidget * parent):QWidget(parent){
    setStyleSheet("background-color:white;");
    resize(B_WIDTH, B_HEIGHT);

    for (int i=0;i<=ENEMY_NUM-1;i++){
        enemy _npc;
        npc.push_back(_npc);
    }
    reStart.setText("重置");
    reStart.move(1700,150);
    reStart.setParent(this);
    deployTower.setText("一级防御塔");
    deployTower.move(1700,250);
    deployTower.setParent(this);
    deployTowerHigh.setText("二级防御塔");
    deployTowerHigh.move(1700,300);
    deployTowerHigh.setParent(this);
    startButton.setText("开始");
    startButton.move(1700,200);
    startButton.setParent(this);
    backGround.load("background.png");
    count=0;
    step=0;
    reset();
    isactive=false;
    update();
}

void map::drawBackGround(QPainter & qp){
    qp.drawImage(0,0,backGround);
}
void map::start(){
    connect(&reStart,&QPushButton::clicked,this,&map::restart);
    connect(&deployTower,&QPushButton::clicked,this,&map::deploy);
    connect(&deployTowerHigh,&QPushButton::clicked,this,&map::deploy_high);
    connect(&startButton,&QPushButton::clicked,this,&map::init);
}

void map::init(){
    timeID=startTimer(DELAY);
    timeID1=startTimer(3*DELAY);
}

void map::restart(){
    if (isactive){
        killTimer(timeID);
        killTimer(timeID1);
    }
    reset();
    update();
}

void map::reset(){
    for (int i=0;i<=npc.size()-1;i++){
        npc[i].init();
        npc[i].x-=(80*i);
    } //enemy reset
    home.reset(); //base reset
    isactive=true;
    while(!defenceTower.isEmpty()){
        defenceTower.pop_back();
        TOWER_NUM++;
    }
}

void map::deploy(){
    qDebug()<<"tower deployed!"<<endl;
    allowDeploy=true;
    setPower=80;
    setRange=200;
}

void map::deploy_high(){
    qDebug()<<"tower deployed!"<<endl;
    allowDeploy=true;
    setPower=30;
    setRange=350;
}

void map::countDeployedTower(){
    TOWER_NUM--;
    allowDeploy=false;
}
void map::mousePressEvent(QMouseEvent * e){
    if (allowDeploy && TOWER_NUM >=1){
        tower _tow(e->x()-18,e->y()-60,setPower,setRange);
        defenceTower.push_back(_tow);
        QPainter qp(this);
        _tow.paint(qp);
        countDeployedTower();
        update();
    }

    //qDebug()<<e->x()<<" "<<e->y();
}

void map::timerEvent(QTimerEvent * e){
    //Q_UNUSED(e);

        if (gameover() || home._base<=0){
            killTimer(timeID);
            killTimer(timeID1);
            isactive=false;
            qDebug()<<timeID<<" killed";
        }
        else {
            if (e->timerId()==timeID){
                npcMove();
            }
            if (e->timerId()==timeID1){
                towerAttack();
            }
            npcAttack();
            repaint();
        }


}

void map::paintEvent(QPaintEvent * e){
    Q_UNUSED(e);
    QPainter qp(this);
    drawBackGround(qp);
    home.paint(qp);
    npcPaint(qp);
    towerPaint(qp);
}

void map::npcMove(){
    for (int i=0;i<=npc.size()-1;i++){
        npc[i].move();
    }
}

void map::npcPaint(QPainter &qp){
    for (int i=0;i<=npc.size()-1;i++){
        npc[i].paint(qp);
    }
}

void map::towerAttack(){
    for (int i=0;i<=defenceTower.size()-1;i++){
        defenceTower[i].attack(npc);
    }
}

void map::towerPaint(QPainter & qp){
    for (int i=0;i<=defenceTower.size()-1;i++){
        defenceTower[i].paint(qp,npc);
    }
}

void map::npcAttack(){
    for (int i=0;i<=npc.size()-1;i++){
        if (npc[i].dead() && npc[i].life>0){
            home.beAttacked(npc[i]);
            npc[i].life=0;
        }
    }
}

bool map::gameover(){
    bool temp=true;
    for (int i=0;i<=npc.size()-1;i++){
        temp=(temp && (npc[i].dead()));
    }
    return temp ;
}
