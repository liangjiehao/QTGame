#ifndef MANAGEENEMY_H
#define MANAGEENEMY_H

#include <QVector>

class manageenemy
{
public:
    manageenemy();
    QVector<int> generate_enemy(QString type);
    void append_enemy(QVector<QVector<int>> &, int num, QString type);
    void generate_wave(QVector<QVector<int>> &, int wave_type = 0);
    void wave_mode(QString type, int num);
    int WAVE_GAP;
    int WAVE_NUM;
    int ENEMY_NUM;
    int life;
    int defence;
    int attack;
};

#endif // MANAGEENEMY_H
