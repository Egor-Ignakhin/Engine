#ifndef GLWINDOW_H
#define GLWINDOW_H
#include <QGLWidget>
#include <QMouseEvent>
#include "component.h"

class Model;

class GLWindow: public QGLWidget, public Component
{
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void updeateGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public:    
    Model* curmodel;
    GLWindow(QWidget* parent = 0);
    QList<Model*> models;
    GLfloat xCamRot;
    void update();
private:
     int faceAtPosition(const QPoint &pos);
    QPoint lastPos;
};

#endif // GLWINDOW_H
