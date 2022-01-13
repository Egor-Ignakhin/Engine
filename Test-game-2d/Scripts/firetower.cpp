#include "firetower.h"

FireTower::FireTower()
{
    towerLevels = new Tower::TowerLevel[3]{
    {145, 5, 2, 15},
    {220, 8, 3, 17},
    {350, 10, 6, 20}
    };
}
FireTower::~FireTower(){
     delete [] towerLevels;
}
