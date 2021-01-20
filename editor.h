#ifndef EDITOR_H
#define EDITOR_H
#include <QtWidgets>

class Editor : public QWidget // главное окно. наследуемые классы используются как вспомогательные окна для разработки
{
private:
    QWidget* mWindow;
public:
    void init();
public:
     QHBoxLayout* mLayout;
};

#endif // EDITOR_Hr
