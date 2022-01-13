#include "enginelauncher.h"
#include <QQuickWidget>


EngineLauncher::EngineLauncher()
{
QQuickWidget* view = new QQuickWidget;
view->setSource(QUrl("qrc:/Screen01.ui.qml"));
view->show();

//auto but = view->rootObject();

//connect(but, SIGNAL( clickSignal() ), this, SLOT( pushButtonClicked() ) );

}
