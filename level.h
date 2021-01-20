#ifndef LEVEL_H
#define LEVEL_H

#include "inspector.h"

class Level // наследники класса могут быть созданы и загружены в OGL окно. упрощает разработку уровней
{
public:    
    static Level* lastLoadedLevel;
    static void loadLevel(unsigned char index);
    static void setModules(GLWindow* mainW, Inspector* insp);
    QList<Model*> models;
    static GLWindow* mainWindow;
protected:
    static Inspector* inspector;   
    virtual void load() = 0;
    virtual ~Level() {}
};

#endif // LEVEL_H
