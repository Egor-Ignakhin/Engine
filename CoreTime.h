#ifndef CORETIME_H
#define CORETIME_H
#include "component.h"
#include <QElapsedTimer>
class CoreTime : public Component
{
public:
    CoreTime();
    void update();
    static float deltaTime;
    static QElapsedTimer* timer;
};

#endif // CORETIME_H
