#include "model.h"
#include "inspector.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Model* model = new Model;
    Editor* editor = new Editor;
    editor->init();

    Inspector* inspector = new Inspector();
    inspector->curModel = model;
    editor->mLayout->addWidget(model);
    editor->mLayout->addWidget(inspector);



    return app.exec();
}
