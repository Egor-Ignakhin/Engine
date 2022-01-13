#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vector3.h"

class Transform // класс, отвечающий за трансформацию объектов в пространстве
{

public:
    Transform();
    ~Transform();
    Vector3 position();
    Vector3 rotation();
    Vector3 scale();

    void setPosition(Vector3 vec);
    void setRotation(Vector3 vec);
    void setScale(Vector3 vec);
    void setPosition(float x,float y,float z);
    void setRotation(float x,float y,float z);
    void setScale(float x,float y,float z);
private:
    Vector3 mPosition;
    Vector3 mRotation;
    Vector3 mScale;

};

#endif // TRANSFORM_H
