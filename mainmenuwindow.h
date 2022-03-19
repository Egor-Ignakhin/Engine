#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QObject>
#include <QWidget>
#include "levelsmenu.h"
#include "settingsmenu.h"

class MainMenuWindow : public QWidget
{   
    Q_OBJECT
public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
private slots:
    void OpenLevelsMenu();
    void OpenSettingsMenu();
    void ExitFromGame() const;
private:
    LevelsMenu* levelsMenu;
    SettingsMenu* settingsMenu;
};

#endif // MAINMENUWINDOW_H
