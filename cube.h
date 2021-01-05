#ifndef CUBE_H
#define CUBE_H

#include "model.h"

class Cube:public Model
{
public:
    Cube(GLWindow* parent, QString name);
    virtual void draw();
};

#endif // CUBE_H
