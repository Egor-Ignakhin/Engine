#include "glwindow.h"
#include <QColorDialog>
#include <QDebug>
#include "model.h"

GLWindow::GLWindow(QWidget* parent) : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
}
void GLWindow::initializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLWindow::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)width / height;
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i = 0; i < models.size();i++){
        models[i]->draw();
    }
}
void GLWindow::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = (GLfloat) (event->x() - lastPos.x()) / width();
    GLfloat dy = (GLfloat) (event->y() - lastPos.y()) / height();
    std::vector<GLfloat> curModelRot = curmodel->getRotation();
    if (event->buttons() & Qt::LeftButton) {
        curmodel->setRotation(curModelRot[0] + 180 * dy,curModelRot[1] + 180 * dx, curModelRot[2]);
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        curmodel->setRotation(curModelRot[0] + 180 * dy,curModelRot[1] , curModelRot[2] + 180 * dx);
        updateGL();
    }
    lastPos = event->pos();
}

void GLWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

    int face = faceAtPosition(event->pos());
    if (face != -1) {
        QColor color = QColorDialog::getColor( curmodel->faceColors[face],
                                               this);
        if (color.isValid()) {
            curmodel->faceColors[face] = color;
            updateGL();
        }
    }
}
int GLWindow::faceAtPosition(const QPoint &pos)
{
    const int MaxSize = 512;
    GLuint buffer[MaxSize];
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    /*gluPickMatrix((GLdouble)pos.x(), // <--
    (GLdouble) (viewport[3] -* pos.y()),
    5.0, 5.0, viewport);*/
    GLfloat x = (GLfloat)width() / height();
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    for(int i = 0; i < models.size();i++){
        models[i]->draw();
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    if (!glRenderMode(GL_RENDER))
        return -1;
    return buffer[3];
}
