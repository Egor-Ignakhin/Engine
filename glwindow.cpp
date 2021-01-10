#include "glwindow.h"
#include <QColorDialog>
#include <QDebug>
#include "model.h"
#include <GL/glu.h>
#include "vector3.h"
#include <QApplication>

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

    globPosX = mapToGlobal(pos()).x();
    globPosY = mapToGlobal(pos()).y();
    globWidth = mapToGlobal(QPoint(width, height)).x();
    globHeight = mapToGlobal(QPoint(width, height)).y();
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double aspect = width() / height();
    glViewport(0, 0, width(), height());
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-150, 150, -112, 112, -150, 1500);//glOrtho(hor+, hor-, up+ , up-, nearPlane, farPlane);
    gluPerspective(60.0, aspect, 1.0, 2000.0);//fov,aspect
    glMatrixMode(GL_MODELVIEW);

    for(int i = 0; i < models.size();i++){
        models[i]->draw();
    }
}

void GLWindow::mousePressEvent(QMouseEvent *event){
    lastPos = event->pos();
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
    /* GLfloat dx = (GLfloat) (event->x() - lastPos.x()) / width();
        GLfloat dy = (GLfloat) (event->y() - lastPos.y()) / height();
        Vector3 newRot = curmodel->getRotation();
        if (event->buttons() & Qt::LeftButton) {
            newRot.x += 180 * dy;
            newRot.y += 180 * dx;
        } else if (event->buttons() & Qt::RightButton) {
            newRot.x += 180 * dy;
            newRot.z += 180 * dx;
        }
        curmodel->setRotation(newRot);*/

    static int count;
    int posW = cursor().pos().x();
    int posH = cursor().pos().y();

    if(posW > globPosX && posW < globWidth &&// intersect cursor
            posH > globPosY && posH < globHeight){


        int difference = posW - (globWidth + globPosX)/2;
        if(difference > 0){

            qDebug()<<"> 0"<<count++;
            rotateCamera(true);
        }
        else if (difference < 0){
            rotateCamera(false);
            qDebug()<<"< 0"<<count++;
        }

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
    gluPickMatrix((GLdouble)pos.x(),
    (GLdouble) (viewport[3] - pos.y()),
    5.0, 5.0, viewport);

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

void GLWindow::update(){
  updateGL();
}
void GLWindow::rotateCamera(bool right){
for(int i =0; i< models.size();i++){
    Vector3 mRot = models[i]->getRotation();
    models[i]->setRotation(Vector3(mRot.x,mRot.y + (right ? 1 : -1),mRot.z));
}
}
