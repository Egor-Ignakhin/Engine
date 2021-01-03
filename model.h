#ifndef MODEL_H
#define MODEL_H

#include <QGLWidget>
#include <QMouseEvent>
class Model : public QGLWidget
{
    Q_OBJECT
public:
    Model(QWidget *parent = 0);
    void setRotation(GLfloat* x,GLfloat* y,GLfloat* z);
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    void draw();
    int faceAtPosition(const QPoint &pos);
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[6];
    QPoint lastPos;
};
#endif // MODEL_H
