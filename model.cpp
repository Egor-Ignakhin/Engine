#include "model.h"
#include <QColorDialog>
#include <GL/glu.h>
#include "level.h"

Model::Model(Level* pLevel, QString name) :
    position(0,0,0), rotation(0,0,0), scale(1,1,1)
{
    pWindow = pLevel->mainWindow;
    pLevel->models.append(this);
    mName = name.isEmpty()? "New object" : name;    
}
QString Model::name(){
    return mName;
}

void Model::setPosition(Vector3 vec){
    position = vec;
}

void Model::setRotation(Vector3 vec){
    rotation = vec;
    emit signalChangeRotation(rotation);
}

void Model::setScale(Vector3 vec){
    scale = vec;
}
Vector3 Model::getPosition(){
    return position;
}
Vector3 Model::getRotation(){
    return rotation;
}
Vector3 Model::getScale(){
    return scale;
}
