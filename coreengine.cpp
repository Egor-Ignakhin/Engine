#include "coreengine.h"
#include "component.h"
#include <QTimer>

CoreEngine::CoreEngine()
{
    Editor* editor = new Editor;
    editor->init();

    Inspector* inspector = new Inspector();


    GLWindow* glw = new GLWindow(editor);
    Cube* column1 = new Cube(glw, "column1"),
            *column2 = new Cube(glw,"column2"),
            *floor = new Cube(glw,"floor");

    inspector->setCurModel(column1);
    floor->setPosition(Vector3(0, -100, 0));
    floor->setRotation(Vector3(5, 0, 0));
    floor->setScale(Vector3(50, 1, 1000));

    column1->setPosition(Vector3(-35, -1, 0));
    column1->setRotation(Vector3(0, 0, 0));
    column1->setScale(Vector3(10, 100, 10));

    column2->setPosition(Vector3(35, -1, 0));
    column2->setRotation(Vector3(0, 0, 0));
    column2->setScale(Vector3(10, 100, 10));
    glw->curmodel = column1;
    editor->mLayout->addWidget(glw);
    editor->mLayout->addWidget(inspector);
    inspector->setMainWindow(glw);
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
