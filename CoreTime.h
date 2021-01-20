#ifndef CORETIME_H
#define CORETIME_H
#include "component.h"
#include <QElapsedTimer>
class CoreTime : public Component // класс является время-высчитывающим компонентом (например можно определить fps)
{
public:
    CoreTime();
    void update();
    static float deltaTime;
    static QElapsedTimer* timer;
};

#endif // CORETIME_H
