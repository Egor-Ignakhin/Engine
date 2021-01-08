#ifndef COREENGINE_H
#define COREENGINE_H
#include <QtWidgets>
#include "glwindow.h"
#include "cube.h"
#include "inspector.h"

class Component;

class CoreEngine : QObject
{
    Q_OBJECT
public:
    CoreEngine();
    QList<Component*> updates;
private slots:
    void callUpdates();
};

#endif // COREENGINE_H
