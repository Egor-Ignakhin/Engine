#include "model.h"
#include <QColorDialog>
#include <GL/glu.h>
#include "level.h"

Model::Model(Level* pLevel, QString name)
{
    pWindow = pLevel->mainWindow;
    pLevel->models.append(this);
    mName = name.isEmpty()? "New object" : name;    
}
QString Model::name(){
    return mName;
}
