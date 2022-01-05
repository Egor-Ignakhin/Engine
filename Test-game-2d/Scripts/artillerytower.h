#ifndef ARTILLERYTOWER_H
#define ARTILLERYTOWER_H

#include "tower.h"

class ArtilleryTower : public Tower
{
private :
    class ArtilleryLevel: public Tower::Level{
    public:
        float reloadTime;
        ArtilleryLevel(int cost, int damage,
                       int lessionArea, int attackRadius, float reloadTime):Tower::Level(cost, damage, lessionArea, attackRadius){
            this->reloadTime = reloadTime;
        }
    };
protected:
    void InitParameters() override;
public:
    ArtilleryTower();
    ~ArtilleryTower();
};

#endif // ARTILLERYTOWER_H
