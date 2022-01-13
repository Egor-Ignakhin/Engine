#include "level1.h"
#include <QtDebug>
#include "cube.h"
#include "testmodel.h"

void Level1::load(){
    Cube* column1 = new Cube(this, "column1");
    Cube* column2 = new Cube(this, "column2");
    Cube* floor = new Cube(this, "floor");
    TestModel* testModel = new TestModel(this, "testModel");

    base::inspector->setCurModel(column1);
    floor->transform.setPosition(0, -100, 0);
    floor->transform.setRotation(5, 0, 0);
    floor->transform.setScale(200, 1, 100);

    column1->transform.setPosition(-100, -1, 0);
    column1->transform.setScale(10, 75, 100);

    //column2->transform.setPosition(100, -1, 0);
    //column2->transform.setScale(10, 75, 100);

//    testModel->transform.setPosition(100, -1, 0);
  //  testModel->transform.setScale(10, 75, 100);
}

Level1::~Level1(){
    for(int i = models.size() - 1; i > 0; i--){
        delete models[i];
        models.removeAt(i);
    }
}
