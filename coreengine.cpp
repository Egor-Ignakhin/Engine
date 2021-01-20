#include "coreengine.h"
#include "component.h"
#include <QTimer>
#include "CoreTime.h"

CoreEngine::CoreEngine(int argc, char** argv)
{
    QApplication app(argc, argv);

    CoreTime* time = new CoreTime;

    Editor* editor = new Editor;
    editor->init();

    Inspector* inspector = new Inspector();

    glw = new GLWindow(editor);
    app.installEventFilter(glw);
    unsigned lvl = 0;
    Level::setModules(glw, inspector);
    Level::loadLevel(lvl);
    glw->changeLevel(Level::lastLoadedLevel);

    editor->mLayout->addWidget(glw);
    editor->mLayout->addWidget(inspector);
    inspector->setMainWindow(glw);
    updates.append(glw);
    updates.append(time);

    QTimer* timer = new QTimer(this);
    timer->singleShot(1,this,SLOT(callUpdates()));

    app.exec();
}

float CoreTime::deltaTime;
QElapsedTimer* CoreTime::timer;
void CoreEngine::callUpdates(){
    while(!glw->isHidden()){
        CoreTime::timer->start();
        for(int i = 0; i< updates.size(); i++){
            updates[i]->update();
        }
        CoreTime::deltaTime = CoreTime::timer->elapsed() * 0.001;
        //qDebug() <<1/CoreTime::deltaTime << " <- delta time";
        QApplication::processEvents();
    }
}
