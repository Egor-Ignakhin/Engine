#ifndef EDITOR_H
#define EDITOR_H
#include <QtWidgets>

class Editor : public QWidget
{
private:
    QWidget* mWindow;
public:
    void init();
public:
     QHBoxLayout* mLayout;
};

#endif // EDITOR_Hr
