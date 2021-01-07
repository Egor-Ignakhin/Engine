#ifndef VECTOR3_H
#define VECTOR3_H


class Vector3
{
public:
    float x,y,z;
    Vector3(float wx, float wy,float wz);
    void calculateSelectLine(int mouse_x, int mouse_y, Vector3& p1, Vector3& p2,int height);
    Vector3& operator-(Vector3& value){

        static Vector3 retVec(x - value.x, y - value.y, z - value.z);

        return retVec;
    }
};

#endif // VECTOR3_H
