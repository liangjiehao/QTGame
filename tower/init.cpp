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
#include <QPropertyAnimation>

void map::initMain(){
    BG=":/new/BGMain.png";
    pageControl="main";

    startButton.hide();
    deployTower.hide();
    deployTowerHigh.hide();
    deployTowerhasaki.hide();
    reStart.hide();
    backTo.hide();
    easy.hide();
    hard.hide();
    evil.hide();
    victory.hide();
    defeat.hide();

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

    QIcon ysoicon(":/new/xiaobing.png");
    deployTowerhasaki.setIcon(ysoicon);
    deployTowerhasaki.setIconSize(QSize(100,100));
    deployTowerhasaki.move(1650,700);
    deployTowerhasaki.setParent(this);

    QIcon vicicon(":/new/victory.png");
    victory.setIcon(vicicon);
    victory.setIconSize(QSize(800,300));
    victory.move(400,350);
    victory.setParent(this);

    QIcon deficon(":/new/defeat.png");
    defeat.setIcon(deficon);
    defeat.setIconSize(QSize(800,300));
    defeat.move(400,350);
    defeat.setParent(this);
}

void map::initenemy(){
    if (pageControl == "easy"){
        waveManage.generate_wave(wave,easyWave[COUNT_WAVE]);

    }
    else if (pageControl == "hard"){

    }
    else {

    }


    //qDebug()<<life;
    int temp=npc.size();
    for (int i=0;i<=wave.size()-1;i++){
        enemy _npc(wave[i][0],wave[i][1],wave[i][2],wave[i][3]);
        npc.push_back(_npc);
    }
    /*
    for (int i=temp;i<=npc.size()-1;i++){
            npc[i].x-=(80*i);
    }*/
}

void map::drawBackGround(QPainter & qp,QString map){
    backGround.load(map);
    qp.drawImage(0,0,backGround);
}

void map::init(){

        if (!isactive){
            isactive=true;
            //initenemy();
            /*
            test.setIcon(QIcon(":/new/xiaobing.png"));
            test.setParent(this);
            test.show();

            npc[0].setIcon(QIcon(":/new/xiaobing.png"));
            npc[0].setIconSize(QSize(200,200));
            npc[0].setParent(this);
            npc[0].show();

            QPropertyAnimation *testAnimation = new QPropertyAnimation(&npc[0],"pos");
            testAnimation->setDuration(10000);
            testAnimation->setStartValue(QPoint(300,300));
            testAnimation->setEndValue(QPoint(800,800));
            testAnimation->start();
            */
            waveControl();
            timeID=startTimer(DELAY);
            timeID1=startTimer(3*DELAY);


        }

    }

void map::waveControl(){
    if (COUNT_WAVE<waveManage.WAVE_NUM){
        initenemy();
        qDebug()<<"shot!";
        COUNT_WAVE++;
        QTimer::singleShot(waveManage.WAVE_GAP,this,&map::waveControl);
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
        deployTowerhasaki.show();
        reStart.show();

        home.reset();

/*
        QPropertyAnimation *testAnimation = new QPropertyAnimation(&deployTower,"pos");
        testAnimation->setDuration(5000);
        testAnimation->setStartValue(QPoint(300,300));
        testAnimation->setEndValue(QPoint(800,800));
        testAnimation->start();
*/
        waveManage.wave_mode("easy");
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
        deployTowerhasaki.show();
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
        deployTowerhasaki.show();
        reStart.show();

        home.reset(20000);
        repaint();
}
