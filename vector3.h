#ifndef VECTOR3_H
#define VECTOR3_H


struct Vector3 // трёхмерный вектор.
{    
public:
    Vector3(float x = 0, float y = 0,float z = 0);
    void set(float x, float y,float z);    
    float x;
    float y;
    float z;
};

#endif // VECTOR3_H
