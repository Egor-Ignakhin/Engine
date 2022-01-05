#ifndef TOWER_H
#define TOWER_H
#include <iostream>

class Tower
{
public:
    class Level
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
        Level(int cost, int damage,
              int lessionArea, int attackRadius){
            this->cost = cost;
            this->damage = damage;
            this->lessionArea = lessionArea;
            this->attackRadius = attackRadius;
        }
};
protected:
    int currentLevel;
    Level *levels;

    virtual void InitParameters() = 0;

public:
    Tower();
    ~Tower();
};

#endif // TOWER_H
