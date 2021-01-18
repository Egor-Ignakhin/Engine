#ifndef LEVEL1_H
#define LEVEL1_H


#include "level.h"
class Model;

class Level1 : public Level
{
protected:
    virtual void load();    
    ~Level1();
public:
    typedef Level base;
};

#endif // LEVEL1_H
