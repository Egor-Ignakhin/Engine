#include "model.h"
#include <QColorDialog>
#include <GL/glu.h>
#define COORD_LIMIT std::numeric_limits<float>::max() //using for coords model

Model::Model(GLWindow* parent, QString name)
{   
    pWindow = parent;
    mName = name.isEmpty()? "New object" : name;
    positionX = 0;
    positionY = 0;
    positionZ = 0;

    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;

    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;
}
QString Model::name(){
    return mName;
}

void Model::setPosition(GLfloat x, GLfloat y, GLfloat z){
    if(x != COORD_LIMIT)
        positionX = x;
    if(y != COORD_LIMIT)
        positionY = y;
    if(z != COORD_LIMIT)
        positionZ = z;
}

void Model::setRotation(GLfloat x,GLfloat y,GLfloat z){
    if(x != COORD_LIMIT)
        rotationX = x;
    if(y != COORD_LIMIT)
        rotationY = y;
    if(z != COORD_LIMIT)
        rotationZ = z;
}

void Model::setScale(GLfloat x, GLfloat y, GLfloat z){
    if(x != COORD_LIMIT)
       scaleX = x;
    if(y != COORD_LIMIT)
        scaleY = y;
    if(z != COORD_LIMIT)
        scaleZ = z;
}
std::vector<GLfloat> Model::getRotation(){

    std::vector<GLfloat> rot{rotationX, rotationY, rotationZ};

    return rot;
}
