#ifndef GLWINDOW_H
#define GLWINDOW_H
#include <QGLWidget>
#include <QMouseEvent>
#include "component.h"

class Model;

class GLWindow: public QGLWidget, public Component
{
    Q_OBJECT
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public:    
    Model* curmodel;
    GLWindow(QWidget* parent = 0);
    QList<Model*> models;
    double yCamRot;
    void update();   
private:
    void rotateCamera(bool right);
    int faceAtPosition(const QPoint &pos);
    QPoint lastPos;
    int globPosX;
    int globPosY;
    int globWidth;
    int globHeight;
    float speed = 10;

    void updateWindow();
    enum motionVector{forward, backward, right, left};
    void move(motionVector mVector,bool multiply);
public slots:
    void slotForwardMove();
    void slotBackwardMove();
    void slotRightMove();
    void slotLeftMove();
signals:
    void signalChangeYCamRot(GLfloat);

};

#endif // GLWINDOW_H
