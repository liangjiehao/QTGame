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

<<<<<<< HEAD
    //reset();
    update();
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

void map::paintEvent(QPaintEvent * e){
    Q_UNUSED(e);
    QPainter qp(this);
    if (pageControl == "main"){
        drawBackGround(qp,BG);
    }
    else if (pageControl == "rule"){
        drawBackGround(qp,BG);
    }
    else if (pageControl == "selectChapter" ){
        drawBackGround(qp,BG);
    }
    else {
        drawBackGround(qp,BG);
        home.paint(qp);
        npcPaint(qp);
        towerPaint(qp);
    }

}

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

void map::drawBackGround(QPainter & qp,QString map){
    backGround.load(map);
    qp.drawImage(0,0,backGround);
}
=======
    update();
}



>>>>>>> dev
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
<<<<<<< HEAD
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
=======
>>>>>>> dev
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
    allowDeploy=false;
    setCursor(Qt::ArrowCursor);
}

void map::deploy(){
    //qDebug()<<"tower deployed!"<<endl;
    setCursor(QPixmap(":/new/bluetow.png"));
    towerControl="showTowerRange";
    update();
    allowDeploy=true;
    setPower=60;
    setRange=200;
    if (pageControl == "evil"){
        setPower = 200;
    }
}

void map::deploy_high(){
    //qDebug()<<"tower deployed!"<<endl;
    setCursor(QPixmap(":/new/redtow.png"));
    towerControl="showTowerRange";
    update();
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
<<<<<<< HEAD
void map::mousePressEvent(QMouseEvent * e){
    if (allowDeploy && TOWER_NUM >=1){
        if (checkOverlap(e->x(),e->y())){
            tower _tow(e->x()-18,e->y()-60,setPower,setRange);
            defenceTower.push_back(_tow);
            QPainter qp(this);
            _tow.paint(qp);
            countDeployedTower();
        }
        else{
            allowDeploy=false;
        }
        update();
    }

    //qDebug()<<e->x()<<" "<<e->y();
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

void map::timerEvent(QTimerEvent * e){
    //Q_UNUSED(e);

        if (gameover() || home._base<=0){
            killTimer(timeID);
            killTimer(timeID1);
            isactive=false;
            //qDebug()<<timeID<<" killed";
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
=======

void map::showTowerRange(QPainter &qp){
    if(!defenceTower.isEmpty()){
        for (int i=0;i<=defenceTower.size()-1;i++){
            defenceTower[i].showDeployRange(qp,OVERLAP);
>>>>>>> dev
        }
    }
}


bool map::checkOverlap(int x,int y){
    for (int i=0;i<=defenceTower.size()-1;i++){

<<<<<<< HEAD

=======
        if (((x-defenceTower[i].getXC())*(x-defenceTower[i].getXC())
                +(y-defenceTower[i].getYC())*(y-defenceTower[i].getYC()))< (OVERLAP*OVERLAP)){
            return false;
        }
    }
    return true;
}
>>>>>>> dev

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
