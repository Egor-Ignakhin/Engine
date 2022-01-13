#include "transform.h"
#include <QDebug>


Transform::Transform(){
qDebug() << "Создание " << typeid(*this).name();
}
Transform::~Transform(){
    qDebug() << "Удаление " << typeid(*this).name();
}
Vector3 Transform::position(){
    return mPosition;
}
Vector3 Transform::rotation(){
    return mRotation;
}
Vector3 Transform::scale(){
    return mScale;
}
void Transform::setPosition(Vector3 vec){
   mPosition = vec;
}
void Transform::setRotation(Vector3 vec){
   mRotation = vec;
}
void Transform::setScale(Vector3 vec){
   mScale = vec;
}
void Transform::setPosition(float x, float y, float z){
   mPosition.x = x;
   mPosition.y = y;
   mPosition.z = z;
}
void Transform::setRotation(float x, float y, float z){
   mRotation.x = x;
   mRotation.y = y;
   mRotation.z = z;
}
void Transform::setScale(float x, float y, float z){
    mScale.x = x;
    mScale.y = y;
    mScale.z = z;
}
