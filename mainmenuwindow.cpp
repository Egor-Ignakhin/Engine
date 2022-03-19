#include "mainmenuwindow.h"
#include "QtDebug"
#include "ui_MainMenu.h"
#include <QtCore/QCoreApplication>
#include "ui_LevelsMenu.h"
#include "ui_SettingsMenu.h"

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QWidget{parent}
{    
    Ui::MainMenu mainMenu;
    mainMenu.setupUi(this);

    levelsMenu = new LevelsMenu();
    settingsMenu = new SettingsMenu();

    Ui::LevelsMenu lmUi;
    lmUi.setupUi(levelsMenu);

    Ui::SettingsMenu smUi;
    smUi.setupUi(settingsMenu);

    connect(mainMenu.PlayButton, SIGNAL(clicked(bool)), SLOT(OpenLevelsMenu()));
    connect(mainMenu.SettingsButton, SIGNAL(clicked(bool)), SLOT(OpenSettingsMenu()));
    connect(mainMenu.ExitButton, SIGNAL(clicked(bool)), SLOT(ExitFromGame()));

    show();
}
void MainMenuWindow::OpenLevelsMenu(){
    levelsMenu->show();
    hide();
}
void MainMenuWindow::ExitFromGame() const{    
    exit(EXIT_FAILURE);
}
void MainMenuWindow::OpenSettingsMenu(){
    settingsMenu->show();
    hide();
}
