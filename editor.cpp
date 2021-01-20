#include "editor.h"
void Editor::init(){
    mWindow = new QWidget;
    mLayout = new QHBoxLayout;

    mWindow->setLayout(mLayout);
    mWindow->resize(1200, 800);

    mWindow->move(1920 / 4,1080 / 6);
    mWindow->show();
}
