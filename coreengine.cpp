#include "coreengine.h"
#include "component.h"
#include <QTimer>

CoreEngine::CoreEngine()
{
    Editor* editor = new Editor;
    editor->init();

    Inspector* inspector = new Inspector();


    GLWindow* glw = new GLWindow;
    Cube* cube1 = new Cube(glw, "Cube1"),
            *cube2 = new Cube(glw,"Cube2");

    inspector->setCurModel(cube1);
    glw->curmodel = cube1;
    glw->models.append(cube1);
    glw->models.append(cube2);
    editor->mLayout->addWidget(glw);
    editor->mLayout->addWidget(inspector);
    inspector->mWindow = glw;
    updates.append(glw);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(callUpdates()));
    timer->start(1); //time specified in sec
}

void CoreEngine::callUpdates(){
    for(int i = 0; i< updates.size(); i++){
        updates[i]->update();
    }
}
