#include <QApplication>
#include "coreengine.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);


   CoreEngine* core = new CoreEngine;


    return app.exec();
}
