#include "coreengine.h"
#include "component.h"
#include <QTimer>
#include "CoreTime.h"
#include "enginelauncher.h"

CoreEngine::CoreEngine(int argc, char** argv)
{
    QApplication app(argc, argv);

    qDebug() << "Создание " << typeid(*this).name();

    /*EngineLauncher* launcher = new EngineLauncher();

    while(launcher->GetCanLoadEditor() == false){
        QApplication::processEvents();
    }*/

    CoreTime* time = new CoreTime;

    Editor* editor = new Editor;
    editor->init();

    inspector = new Inspector;

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

CoreEngine::~CoreEngine(){
    qDebug() << "Удаление " << typeid(*this).name();
    delete glw;
    delete inspector;
    //delete updates;?
}

float CoreTime::deltaTime;
QElapsedTimer* CoreTime::timer;
void CoreEngine::callUpdates(){
    while(!glw->isHidden()){
        CoreTime::GetTimer()->start();
        for(int i = 0; i< updates.size(); i++){
            updates[i]->update();
        }
        CoreTime::SetDeltaTime(CoreTime::GetTimer()->elapsed() * 0.001);
        //qDebug() <<1/CoreTime::deltaTime << " <- delta time";
        QApplication::processEvents();
    }
}
