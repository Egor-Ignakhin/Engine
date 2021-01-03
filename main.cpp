#include "model.h"
#include "inspector.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QWidget* mWindow = new QWidget;
    QHBoxLayout* l = new QHBoxLayout;

    Model* model = new Model;


    Inspector* inspector = new Inspector();
    inspector->curModel = model;
    l->addWidget(model);
    l->addWidget(inspector);

    //model->setRotationX(50);


    mWindow->setLayout(l);
    mWindow->resize(1200,800);


    mWindow->move(1920/4,1080/6);
    mWindow->show();
    return app.exec();
}
