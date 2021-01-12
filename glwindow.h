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
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);
    void keyPressEvent(QKeyEvent* event);
public:    
    Model* curmodel;
    GLWindow(QWidget* parent = 0);
    QList<Model*> models;
    double yCamRot;
    void update();   
private:
    void rotateCamera(float multiply);
    int faceAtPosition(const QPoint &pos);
    QPoint lastPos;
    int globPosX;
    int globPosY;
    int globWidth;
    int globHeight;
    float speed = 10;
    float sensivity = 3;
    bool isGameMode = false;

    void updateWindow();
    enum motionVector{forward, backward, right, left};
    void move(motionVector mVector,bool multiply);
public slots:
    void slotForwardMove();
    void slotBackwardMove();
    void slotRightMove();
    void slotLeftMove();
    void slotChangeGameMode();
signals:
    void signalChangeYCamRot(GLfloat);

};

#endif // GLWINDOW_H
