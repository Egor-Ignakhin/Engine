#include "artillerytower.h"

ArtilleryTower::ArtilleryTower()
{    
    towerLevels = new ArtilleryLevel[3]{
    {240, 15, 5, 2, 100},
    {300, 22, 7, 3, 150},
    {400, 30, 8, 6, 200}
    };

}
ArtilleryTower::~ArtilleryTower(){
    delete [] towerLevels;
}
void ArtilleryTower::InitParameters(){

}
