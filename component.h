#ifndef COMPONENT_H
#define COMPONENT_H


class Component // наследники этого класса являются только игровыми классами
{

public:
    Component();
    virtual void update() = 0; // вызывается каждый кадр
};

#endif // COMPONENT_H
