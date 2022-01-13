#include "level.h"
#include <QDebug>
#include "level1.h"


void Level::setModules(GLWindow* mainW, Inspector* insp){
    mainWindow = mainW;
    inspector = insp;
}

Level* Level::lastLoadedLevel;
GLWindow* Level::mainWindow;
Inspector* Level::inspector;
void Level::loadLevel(unsigned char index){
    qDebug() << "Уровень " << index << "был загружен";
    delete lastLoadedLevel;


    Level* currentLoadedLevel = nullptr;
    switch (index) {
    case 0 : {
        currentLoadedLevel = new Level1;
        currentLoadedLevel->load();
        break;
    }
    default:
        break;
    }

    lastLoadedLevel = currentLoadedLevel;
    mainWindow->changeLevel(lastLoadedLevel);
}
