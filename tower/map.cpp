#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>
#include <QImage>
#include <QIcon>
#include <QSize>

map::map(QWidget * parent):QWidget(parent){
    setStyleSheet("background-color:rgba(0,0,0,0)");
    resize(B_WIDTH, B_HEIGHT);

    setButton();

    initMain();

    update();
}



void map::start(){
    connect(&backTo,&QPushButton::clicked,this,&map::backToMain);
    connect(&showRule,&QPushButton::clicked,this,&map::displayRule);
    connect(&enterGame,&QPushButton::clicked,this,&map::selectChapter);
    connect(&easy,&QPushButton::clicked,this,&map::initEasy);
    connect(&hard,&QPushButton::clicked,this,&map::initHard);
    connect(&evil,&QPushButton::clicked,this,&map::initEvil);
    connect(&reStart,&QPushButton::clicked,this,&map::restart);
    connect(&deployTower,&QPushButton::clicked,this,&map::deploy);
    connect(&deployTowerHigh,&QPushButton::clicked,this,&map::deploy_high);
    connect(&startButton,&QPushButton::clicked,this,&map::init);
}

void map::backToMain(){
    restart();
    initMain();
}

void map::displayRule(){
    pageControl="rule";
    BG=":/new/BGRule.png";

    startButton.hide();
    deployTower.hide();
    deployTowerHigh.hide();
    reStart.hide();
    easy.hide();
    hard.hide();
    evil.hide();
    enterGame.hide();
    showRule.hide();

    backTo.show();
    repaint();
}

void map::selectChapter(){
    pageControl = "selectChapter";
    BG = ":/new/BGChapter.png";

    startButton.hide();
    deployTower.hide();
    deployTowerHigh.hide();
    reStart.hide();
    enterGame.hide();
    showRule.hide();

    backTo.show();
    easy.show();
    hard.show();
    evil.show();

    repaint();
}



void map::restart(){
    if (isactive){
        killTimer(timeID);
        killTimer(timeID1);
        isactive=false;
    }
    reset();
    update();
}

void map::reset(){
    while(!npc.isEmpty()){
        npc.pop_back();
    }
    if (pageControl == "evil" ){
        home.reset(20000);
    }
    else if (pageControl == "hard"){
        home.reset(12000);
    }
    else home.reset(); //base reset
    //isactive=true;
    while(!defenceTower.isEmpty()){
        defenceTower.pop_back();
        TOWER_NUM++;
    }
}

void map::deploy(){
    //qDebug()<<"tower deployed!"<<endl;
    allowDeploy=true;
    setPower=60;
    setRange=200;
    if (pageControl == "evil"){
        setPower = 200;
    }
}

void map::deploy_high(){
    //qDebug()<<"tower deployed!"<<endl;
    allowDeploy=true;
    setPower=30;
    setRange=400;
    if (pageControl == "evil"){
        setPower = 80;
    }
}

void map::countDeployedTower(){
    TOWER_NUM--;
    allowDeploy=false;
}


bool map::checkOverlap(int x,int y){
    for (int i=0;i<=defenceTower.size()-1;i++){
        if (((x-defenceTower[i].getX())*(x-defenceTower[i].getX())
                +(y-defenceTower[i].getY())*(y-defenceTower[i].getY()))< (OVERLAP*OVERLAP)){
            return false;
        }
    }
    return true;
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
