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

void map::initMain(){
    BG=":/new/BGMain.png";
    pageControl="main";

    startButton.hide();
    deployTower.hide();
    deployTowerHigh.hide();
    reStart.hide();
    backTo.hide();
    easy.hide();
    hard.hide();
    evil.hide();
    enterGame.show();
    showRule.show();
    repaint();
}

void map::setButton(){
    QSize btsize(200,200);
    QIcon etgicon(":/new/entergame.png");

    enterGame.setIcon(etgicon);
    enterGame.setIconSize(btsize);
    enterGame.move(600,600);
    enterGame.setParent(this);

    QIcon rulicon(":/new/rule.png");
    showRule.setIcon(rulicon);
    showRule.setIconSize(btsize);
    showRule.move(1100,600);
    showRule.setParent(this);

    QIcon bckicon(":/new/back.png");
    backTo.setIcon(bckicon);
    backTo.setIconSize(btsize);
    backTo.move(1600,750);
    backTo.setParent(this);

    btsize.setWidth(300);
    btsize.setHeight(600);
    QIcon esyicon(":/new/easy.png");
    easy.setIcon(esyicon);
    easy.setIconSize(btsize);
    easy.move(250,200);
    easy.setParent(this);

    QIcon hrdicon(":/new/hard.png");
    hard.setIcon(hrdicon);
    hard.setIconSize(btsize);
    hard.move(750,200);
    hard.setParent(this);

    QIcon evlicon(":/new/evil.png");
    evil.setIcon(evlicon);
    evil.setIconSize(btsize);
    evil.move(1250,200);
    evil.setParent(this);

    btsize.setWidth(100);
    btsize.setHeight(100);
    QIcon rsticon(":/new/restart.png");
    reStart.setIcon(rsticon);
    reStart.setIconSize(btsize);
    reStart.move(1650,100);
    reStart.setParent(this);

    QIcon srticon(":/new/start.png");
    startButton.setIcon(srticon);
    startButton.setIconSize(btsize);
    startButton.move(1650,200);
    startButton.setParent(this);

    btsize.setWidth(100);
    btsize.setHeight(200);
    QIcon redicon(":/new/redtowic.png");
    deployTowerHigh.setIcon(redicon);
    deployTowerHigh.setIconSize(btsize);
    deployTowerHigh.move(1650,300);
    deployTowerHigh.setParent(this);

    QIcon bleicon(":/new/bluetowic.png");
    deployTower.setIcon(bleicon);
    deployTower.setIconSize(btsize);
    deployTower.move(1650,500);
    deployTower.setParent(this);

}

void map::initenemy(){
    int life;
    if (pageControl == "easy"){
        ENEMY_NUM=20;
        life=5000;
    }
    else if (pageControl == "hard"){
        ENEMY_NUM=40;
        life=8000;
    }
    else {
        ENEMY_NUM=100;
        life=15000;
    }

    for (int i=0;i<=ENEMY_NUM-1;i++){
        enemy _npc(life);
        npc.push_back(_npc);
    }
    for (int i=0;i<=npc.size()-1;i++){
        npc[i].x-=(80*i);
    }
}

void map::drawBackGround(QPainter & qp,QString map){
    backGround.load(map);
    qp.drawImage(0,0,backGround);}

void map::init(){
        if (!isactive){
            isactive=true;
            initenemy();
            timeID=startTimer(DELAY);
            timeID1=startTimer(3*DELAY);
        }

    }

void map::initEasy(){
        reset();

        isactive=false;

        pageControl = "easy";
        BG=":/new/BGEasy.png";

        easy.hide();
        hard.hide();
        evil.hide();
        enterGame.hide();
        showRule.hide();

        backTo.show();
        startButton.show();
        deployTower.show();
        deployTowerHigh.show();
        reStart.show();

        home.reset();
        repaint();
    }

void map::initHard(){
        reset();

        isactive=false;

        pageControl = "hard";
        BG=":/new/BGHard.png";

        easy.hide();
        hard.hide();
        evil.hide();
        enterGame.hide();
        showRule.hide();

        backTo.show();
        startButton.show();
        deployTower.show();
        deployTowerHigh.show();
        reStart.show();

        home.reset(12000);
        repaint();
    }

void map::initEvil(){
        reset();

        isactive =false;

        pageControl = "evil";
        BG=":/new/BGEvil.png";

        easy.hide();
        hard.hide();
        evil.hide();
        enterGame.hide();
        showRule.hide();

        backTo.show();
        startButton.show();
        deployTower.show();
        deployTowerHigh.show();
        reStart.show();

        home.reset(20000);
        repaint();
}
