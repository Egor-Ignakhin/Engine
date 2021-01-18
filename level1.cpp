#include "level1.h"
#include <QtDebug>
#include "cube.h"


void Level1::load(){
    Cube* column1 = new Cube(this, "column1");
    Cube* column2 = new Cube(this, "column2");
    Cube* floor = new Cube(this, "floor");

    base::inspector->setCurModel(column1);
    floor->setPosition(Vector3(0, -100, 0));
    floor->setRotation(Vector3(5, 0, 0));
    floor->setScale(Vector3(200, 1, 100));

    column1->setPosition(Vector3(-100, -1, 0));
    column1->setScale(Vector3(10, 75, 10));

    column2->setPosition(Vector3(100, -1, 0));
    column2->setScale(Vector3(10, 75, 10));
}

Level1::~Level1(){
    for(int i = models.size() - 1; i > 0; i--){
        delete models[i];
        models.removeAt(i);
    }
}
