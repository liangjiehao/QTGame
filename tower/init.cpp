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

void map::initMain()
{
    BG = ":/new/BGMain.png";
    pageControl = "main";

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
    recycle.hide();
    coin_num.hide();

    enterGame.show();
    showRule.show();
    repaint();
}

void map::setButton()
{
    QSize btsize(200, 200);
    QIcon etgicon(":/new/entergame.png");

    enterGame.setIcon(etgicon);
    enterGame.setIconSize(btsize);
    enterGame.move(600, 600);
    enterGame.setParent(this);

    QIcon rulicon(":/new/rule.png");
    showRule.setIcon(rulicon);
    showRule.setIconSize(btsize);
    showRule.move(1100, 600);
    showRule.setParent(this);

    QIcon bckicon(":/new/back.png");
    backTo.setIcon(bckicon);
    backTo.setIconSize(btsize);
    backTo.move(1650, 800);
    backTo.setParent(this);

    btsize.setWidth(300);
    btsize.setHeight(600);
    QIcon esyicon(":/new/easy.png");
    easy.setIcon(esyicon);
    easy.setIconSize(btsize);
    easy.move(250, 200);
    easy.setParent(this);

    QIcon hrdicon(":/new/hard.png");
    hard.setIcon(hrdicon);
    hard.setIconSize(btsize);
    hard.move(750, 200);
    hard.setParent(this);

    QIcon evlicon(":/new/evil.png");
    evil.setIcon(evlicon);
    evil.setIconSize(btsize);
    evil.move(1250, 200);
    evil.setParent(this);

    btsize.setWidth(100);
    btsize.setHeight(100);
    QIcon rsticon(":/new/restart.png");
    reStart.setIcon(rsticon);
    reStart.setIconSize(btsize);
    reStart.move(1620, 480);
    reStart.setParent(this);

    QIcon srticon(":/new/start.png");
    startButton.setIcon(srticon);
    startButton.setIconSize(btsize);

    startButton.move(1760, 480);
    startButton.setParent(this);

    btsize.setWidth(100);
    btsize.setHeight(200);
    QIcon redicon(":/new/redtowic.png");
    deployTowerHigh.setIcon(redicon);
    deployTowerHigh.setIconSize(btsize);
    deployTowerHigh.move(1620, 80);
    deployTowerHigh.setParent(this);

    QIcon bleicon(":/new/bluetowic.png");
    deployTower.setIcon(bleicon);
    deployTower.setIconSize(btsize);
    deployTower.move(1750, 62);
    deployTower.setParent(this);

    QIcon ysoicon(":/new/yasuo1.png");
    deployTowerhasaki.setIcon(ysoicon);
    deployTowerhasaki.setIconSize(QSize(200, 200));
    deployTowerhasaki.move(1620, 280);
    deployTowerhasaki.setParent(this);

    QIcon vicicon(":/new/victory2.png");
    victory.setIcon(vicicon);
    victory.setIconSize(QSize(1500, 700));
    victory.move(200, 150);
    victory.setParent(this);

    QIcon deficon(":/new/defeat2.png");
    defeat.setIcon(deficon);
    defeat.setIconSize(QSize(1500, 700));
    defeat.move(200, 150);
    defeat.setParent(this);

    QIcon recicon(":/new/recycle1.png");
    recycle.setIcon(recicon);
    recycle.setIconSize(QSize(150, 150));
    recycle.move(1670, 670);
    recycle.setParent(this);

    QIcon coiicon(":/new/coin.png");
    coin_num.setIcon(coiicon);
    coin_num.setIconSize(QSize(90, 90));
    coin_num.move(70, 190);
    coin_num.setParent(this);
}

void map::backToMain()
{
    restart();
    initMain();
}

void map::displayRule()
{
    pageControl = "rule";
    BG = ":/new/BGRule2.png";

    startButton.hide();
    deployTower.hide();
    deployTowerHigh.hide();
    deployTowerhasaki.hide();
    reStart.hide();
    easy.hide();
    hard.hide();
    evil.hide();
    enterGame.hide();
    showRule.hide();
    victory.hide();
    defeat.hide();
    recycle.hide();
    coin_num.hide();

    backTo.show();
    repaint();
}

void map::selectChapter()
{
    pageControl = "selectChapter";
    BG = ":/new/BGChapter.png";

    startButton.hide();
    deployTower.hide();
    deployTowerHigh.hide();
    deployTowerhasaki.hide();
    reStart.hide();
    enterGame.hide();
    showRule.hide();
    victory.hide();
    defeat.hide();
    recycle.hide();
    coin_num.hide();

    backTo.show();
    easy.show();
    hard.show();
    evil.show();

    repaint();
}

void map::restart()
{
    qDebug() << isactive << timeID << timeID1;
    if (isactive)
    {
        killTimer(timeID);
        killTimer(timeID1);
        isactive = false;
    }
    startButton.show();
    deployTower.show();
    deployTowerHigh.show();
    deployTowerhasaki.show();
    reStart.show();
    recycle.show();
    reset();
    update();
}

void map::reset()
{
    while (!npc.isEmpty())
    {
        npc.pop_back();
    }
    if (pageControl == "evil")
    {
        home.reset(20000);
    }
    else if (pageControl == "hard")
    {
        home.reset(12000);
    }
    else
        home.reset();

    while (!defenceTower.isEmpty())
    {
        defenceTower.pop_back();
        TOWER_NUM++;
    }

    allowDeploy = false;
    COIN.reset();
    victory.hide();
    defeat.hide();
    home.hide();
    setCursor(Qt::ArrowCursor);
}

void map::initenemy()
{
    if (isactive)
    {

        if (pageControl == "easy")
        {
            if (easyWave[COUNT_WAVE] == -1)
            {
                return;
            }
            waveManage.generate_wave(wave, easyWave[COUNT_WAVE]);
        }
        else if (pageControl == "hard")
        {
            if (hardWave[COUNT_WAVE] == -1)
            {
                return;
            }
            waveManage.generate_wave(wave, hardWave[COUNT_WAVE]);
        }
        else
        {
            if (evilWave[COUNT_WAVE] == -1)
            {
                return;
            }
            waveManage.generate_wave(wave, evilWave[COUNT_WAVE]);
        }

        for (int i = 0; i <= wave.size() - 1; i++)
        {
            assert(wave[i].size() == 4);
            enemy _npc(wave[i][0], wave[i][1], wave[i][2], wave[i][3]);
            npc.push_back(_npc);
        }
    }
}

void map::drawBackGround(QPainter &qp, QString map)
{
    backGround.load(map);
    qp.drawImage(0, 0, backGround);
}

void map::init()
{

    if (!isactive)
    {
        isactive = true;
        COUNT_WAVE = 0;

        waveControl();
        timeID = startTimer(DELAY);
        timeID1 = startTimer(5 * DELAY);
    }
}

void map::waveControl()
{
    if (isactive && COUNT_WAVE < waveManage.WAVE_NUM)
    {
        initenemy();
        COUNT_WAVE++;
        QTimer::singleShot(waveManage.WAVE_GAP, this, &map::waveControl);
    }
}

void map::initEasy()
{
    reset();

    isactive = false;

    pageControl = "easy";
    BG = ":/new/backgroundnew.png";

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
    recycle.show();
    coin_num.show();

    home.reset();

    waveManage.wave_mode("easy", easyWave.size());
    repaint();
}

void map::initHard()
{
    reset();

    isactive = false;

    pageControl = "hard";
    BG = ":/new/backgroundnew.png";

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
    recycle.show();
    coin_num.show();

    waveManage.wave_mode("hard", hardWave.size());
    home.reset(12000);
    repaint();
}

void map::initEvil()
{
    reset();

    isactive = false;

    pageControl = "evil";
    BG = ":/new/backgroundnew.png";

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
    recycle.show();
    coin_num.show();

    waveManage.wave_mode("evil", evilWave.size());
    home.reset(20000);
    repaint();
}
