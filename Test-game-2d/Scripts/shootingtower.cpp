#include "shootingtower.h"

ShootingTower::ShootingTower()
{
    towerLevels = new ShootingTowerLevel[3]{
    {170, 10, 0, 50, 1.0F},
    {250, 14, 0, 70, 0.9F},
    {400, 15, 0, 95, 0.75F}
    };
}
ShootingTower::~ShootingTower(){
     delete [] towerLevels;
}
