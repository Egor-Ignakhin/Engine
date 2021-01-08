#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

class Component : public QObject
{
    Q_OBJECT
public:
    Component();
    virtual void update() = 0;
};

#endif // COMPONENT_H
