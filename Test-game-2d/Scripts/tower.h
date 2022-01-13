#ifndef TOWER_H
#define TOWER_H
#include <iostream>

class Tower
{
public:
    class TowerLevel
    {
    private:
        int cost;
        int damage;
        int lessionArea;
        int attackRadius;

    public:
        int GetCost(){return cost;}
        int GetDamage(){return damage;}
        int GetLessionArea(){return lessionArea;}
        int GetAttackRadius(){return attackRadius;}
        TowerLevel(int cost, int damage,
              int lessionArea, int attackRadius){
            this->cost = cost;
            this->damage = damage;
            this->lessionArea = lessionArea;
            this->attackRadius = attackRadius;
        }
};
protected:
    int currentLevel;
    TowerLevel *towerLevels;

    virtual void InitParameters() = 0;

public:
    Tower();
    virtual ~Tower();
};

#endif // TOWER_H
