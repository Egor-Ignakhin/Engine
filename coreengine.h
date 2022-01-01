#ifndef COREENGINE_H
#define COREENGINE_H
#include <QtWidgets>
#include "glwindow.h"
#include "cube.h"
#include "inspector.h"
#include "level.h"

class Component;

class CoreEngine : QObject// точка старта движка и главный класс
{
    Q_OBJECT
public:
    CoreEngine(int argc, char** argv);   

private slots:
    void callUpdates();
private:
    GLWindow* glw;
    QList<Component*> updates;
};

#endif // COREENGINE_H
