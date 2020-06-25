#include "map.h"

void map::buyTower(){
    if (currentTowerType =="red"){
        COIN.consumecoin(50);
    }
    else if (currentTowerType =="blue"){
        COIN.consumecoin(70);
    }
    else if (currentTowerType == "single"){
        COIN.consumecoin(100);
    }
}
