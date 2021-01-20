#ifndef MODEL_H
#define MODEL_H

#include <QDebug>
#include "transform.h"
#include <QGLWidget>
#include "glwindow.h"

class Level;

class Model : public QObject // наследники могут быть отрисованы в окне OGL.
{    
    Q_OBJECT
public:
    Model(Level* pLevel, QString name);
    QString name();
    Transform transform;
    virtual void draw() = 0;
    QColor faceColors[6];    

protected:
    QString mName;
    GLWindow* pWindow;

signals:
    void signalChangeRotation(Vector3);
};
#endif // MODEL_H
