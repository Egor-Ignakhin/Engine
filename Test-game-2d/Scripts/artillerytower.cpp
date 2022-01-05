#include "artillerytower.h"

ArtilleryTower::ArtilleryTower()
{
    levels = new ArtilleryLevel[3]{{19, 20,1,1,1},
    {19, 20,1,1,1}, {19, 20,1,1,1}};

}
ArtilleryTower::~ArtilleryTower(){
    delete [] levels;
}
void ArtilleryTower::InitParameters(){

}
