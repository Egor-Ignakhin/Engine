#ifndef MODEL_H
#define MODEL_H

#include <QGLWidget>
#include "glwindow.h"

class Model
{
public:
    Model(GLWindow* parent, QString name);
    QString name();
    void setRotation(GLfloat x,GLfloat y,GLfloat z);
    void setPosition(GLfloat x,GLfloat y,GLfloat z);
    void setScale(GLfloat x,GLfloat y,GLfloat z);
    virtual void draw() = 0;
    QColor faceColors[6];

    std::vector<GLfloat> getRotation();

protected:
    QString mName;

    GLfloat positionX;
    GLfloat positionY;
    GLfloat positionZ;

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;

    GLfloat scaleX;
    GLfloat scaleY;
    GLfloat scaleZ;

    GLWindow* pWindow;
};
#endif // MODEL_H
