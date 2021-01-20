#ifndef LEVELSCREATOR_H
#define LEVELSCREATOR_H

#include "editor.h"
class LevelsCreator : public Editor // окно для быстрого создания уровней(в разработке)
{
    Q_OBJECT
public:
    LevelsCreator();
public slots:
    void open();
};

#endif // LEVELSCREATOR_H
