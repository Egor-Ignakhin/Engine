#ifndef CUBE_H
#define CUBE_H

#include "model.h"

class Cube : public Model // класс наследуется от класса Модель, в свою очередь занимается отрисовкой куба
{
public:
    Cube(Level* pLevel, QString name);
    virtual void draw();
};

#endif // CUBE_H
