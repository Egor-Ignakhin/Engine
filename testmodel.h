#ifndef TESTMODEL_H
#define TESTMODEL_H

#include "model.h"

class TestModel : public Model
{
public:
    TestModel(Level* pLevel, QString name);
    virtual void draw();
};

#endif // TESTMODEL_H
