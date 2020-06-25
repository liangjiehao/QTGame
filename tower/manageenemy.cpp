#include "manageenemy.h"
#include <QString>
#include <QVector>

manageenemy::manageenemy(){

}

QVector<int> manageenemy::generate_enemy(QString type){

    //life,defence,attack
    QVector<int> norm_enemy;
    if (type=="normal"){
        norm_enemy.push_back(5000);
        norm_enemy.push_back(50);
        norm_enemy.push_back(500);
        norm_enemy.push_back(0);
    }
    else if(type=="tank"){
        norm_enemy.push_back(2000);
        norm_enemy.push_back(800);
        norm_enemy.push_back(50);
        norm_enemy.push_back(1);
    }
    return norm_enemy;
}

void manageenemy::append_enemy(QVector<QVector<int> > & wave, int num, QString type){
    if (type=="normal_enemies"){
        for (int i=0;i<=num-1;i++){
            wave.append(generate_enemy("normal"));
        }
    }
    else if (type=="normal_tank"){
        wave.append(generate_enemy("tank"));
        for (int i=1;i<=num-1;i++){
            wave.append(generate_enemy("normal"));
        }
    }
}

void manageenemy::generate_wave(QVector<QVector<int> > & wave , int wave_type){
    wave.clear();
    if (wave_type==0){
        append_enemy(wave,1,"normal_enemies");//重复生成相同敌人
    }
    else if (wave_type==1){
        append_enemy(wave,5,"normal_tank");
    }
}

void manageenemy::wave_mode(QString type){
    //wave_gap
    //wave_num
    //enemy_num
    if (type=="easy"){
        WAVE_GAP=3000;
        WAVE_NUM=2;//同步修改map.h初始化
    }
}

