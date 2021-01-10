#ifndef MODEL_H
#define MODEL_H

#include <QDebug>
#include "vector3.h"
#include <QGLWidget>
#include "glwindow.h"

class Model : public QObject
{    
    Q_OBJECT
public:
    Model(GLWindow* parent, QString name);
    QString name();
    void setPosition(Vector3 vec);
    void setRotation(Vector3 vec);
    void setScale(Vector3 vec);
    virtual void draw() = 0;
    QColor faceColors[6];

    Vector3 getPosition();
    Vector3 getRotation();
    Vector3 getScale();

    Vector3 additionalTurn;

protected:
    QString mName;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    GLWindow* pWindow;
signals:
    void signalChangeRotation(Vector3);
};
#endif // MODEL_H
