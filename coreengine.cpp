#include "coreengine.h"

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
}
