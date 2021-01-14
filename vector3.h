#ifndef VECTOR3_H
#define VECTOR3_H


struct Vector3
{    
public:
    Vector3(float x = 0, float y = 0,float z = 0);
    void set(float x, float y,float z);    
    float x;
    float y;
    float z;
    /*
    Vector3& operator-(Vector3& value){

        static Vector3 retVec(x - value.x, y - value.y, z - value.z);

        return retVec;
    }*/
};

#endif // VECTOR3_H
