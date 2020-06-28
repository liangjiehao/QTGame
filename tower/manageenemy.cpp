#include "manageenemy.h"
#include <QString>
#include <QVector>

manageenemy::manageenemy()
{
}

QVector<int> manageenemy::generate_enemy(QString type)
{

    QVector<int> norm_enemy;
    if (type == "normal")
    {
        norm_enemy.push_back(6000);
        norm_enemy.push_back(50);
        norm_enemy.push_back(500);
        norm_enemy.push_back(0);
    }
    else if (type == "tank")
    {
        norm_enemy.push_back(4000);
        norm_enemy.push_back(900);
        norm_enemy.push_back(100);
        norm_enemy.push_back(1);
    }
    else if (type == "rider")
    {
        norm_enemy.push_back(1500);
        norm_enemy.push_back(50);
        norm_enemy.push_back(1500);
        norm_enemy.push_back(2);
    }
    else if (type == "fast")
    {
        norm_enemy.push_back(3000);
        norm_enemy.push_back(20);
        norm_enemy.push_back(1000);
        norm_enemy.push_back(3);
    }

    return norm_enemy;
}

void manageenemy::append_enemy(QVector<QVector<int>> &wave, int num, QString type)
{
    if (type == "normal_enemies")
    {
        wave.append(generate_enemy("normal"));
    }
    else if (type == "normal_tank")
    {
        wave.append(generate_enemy("tank"));
    }
    else if (type == "normal_rider")
    {
        wave.append(generate_enemy("rider"));
    }
    else if (type == "normal_fast")
    {
        wave.append(generate_enemy("fast"));
    }
}

void manageenemy::generate_wave(QVector<QVector<int>> &wave, int wave_type)
{
    wave.clear();
    if (wave_type == 0)
    {
        append_enemy(wave, 1, "normal_enemies");
    }
    else if (wave_type == 1)
    {
        append_enemy(wave, 1, "normal_tank");
    }
    else if (wave_type == 2)
    {
        append_enemy(wave, 1, "normal_rider");
    }
    else if (wave_type == 3)
    {
        append_enemy(wave, 1, "normal_fast");
    }
}

void manageenemy::wave_mode(QString type, int num)
{

    if (type == "easy")
    {
        WAVE_GAP = 2000;
    }
    else if (type == "hard")
    {
        WAVE_GAP = 1500;
    }
    else if (type == "evil")
    {
        WAVE_GAP = 1000;
    }
    WAVE_NUM = num;
}
