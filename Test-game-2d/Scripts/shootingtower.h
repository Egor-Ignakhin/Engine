#ifndef SHOOTINGTOWER_H
#define SHOOTINGTOWER_H

#include "tower.h"

class ShootingTower : public Tower
{
public:
    class ShootingTowerLevel: public Tower::TowerLevel{
    public:
        float reloadTime;
        ShootingTowerLevel(int cost, int damage,
                       int lessionArea, int attackRadius, float reloadTime):Tower::TowerLevel(cost, damage, lessionArea, attackRadius){
            this->reloadTime = reloadTime;
        }
    };

    ShootingTower();
    ~ShootingTower();
};

#endif // SHOOTINGTOWER_H
