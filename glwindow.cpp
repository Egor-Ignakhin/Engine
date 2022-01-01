#include "glwindow.h"
#include "level.h"
#include "CoreTime.h"
#include <QColorDialog>
#include <QDebug>
#include "model.h"
#include <GL/glu.h>
#include <QApplication>
#include "math.h"

GLWindow::GLWindow(QWidget* parent) : QGLWidget(parent), camRotation(0,0,0)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));    
    setFocusPolicy(Qt::StrongFocus);
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
    updateWindow();
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width(), height());
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = width() / height();
    glOrtho(-150, 150, -112, 112, -2000.0, 2000.0);//glOrtho(hor+, hor-, up+ , up-, nearPlane, farPlane);
    gluPerspective(60.0, aspect, 0.01, 2000.0);//fov,aspect
    glMatrixMode(GL_MODELVIEW);

    for(int i = 0; i < currentLvl->models.size();i++){
        currentLvl->models[i]->draw();
    }
}

void GLWindow::keyPressEvent(QKeyEvent* event){        
    if(event->key() == Qt::Key_Escape){
        if(isGameMode){
            slotChangeGameMode();
        }
    }
    if(event->key() == Qt::Key_W){
       keyPress_W = true;
    }
    if(event->key() == Qt::Key_A){
       keyPress_A = true;
    }
    if(event->key() == Qt::Key_S){
       keyPress_S = true;
    }
    if(event->key() == Qt::Key_D){
       keyPress_D = true;
    }
}

void GLWindow::keyReleaseEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_W){
        keyPress_W = false;
    }
    if(event->key() == Qt::Key_A){
       keyPress_A = false;
    }
    if(event->key() == Qt::Key_S){
       keyPress_S = false;
    }
    if(event->key() == Qt::Key_D){
       keyPress_D = false;
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
    for(int i = 0; i < currentLvl->models.size();i++){
        currentLvl->models[i]->draw();
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    if (!glRenderMode(GL_RENDER))
        return -1;
    return buffer[3];
}

void GLWindow::update(){
    if(isGameMode){        
        QPoint currentPos = cursor().pos();//текущая позиция
        cursor().setPos((globWidth + globPosX) / 2, (globHeight + globPosY) / 2);//set in center window

        if(currentPos.x() > globPosX && currentPos.y() < globWidth &&// intersect cursor
                currentPos.x() > globPosY && currentPos.y() < globHeight){


            float dx = (currentPos.x() - (globWidth + globPosX) / 2);
            float dy = (currentPos.y() - (globHeight + globPosY) / 2);

            rotateCamera(horizontal, dx * sensivity);//поворот относительно смещения
            rotateCamera(vertical, dy * sensivity);//поворот относительно смещения
        }
    }
    //qDebug() << keyPress_W;
    if(keyPress_W){
        move(forward, true);
    }
    if(keyPress_A){
        move(left, true);
    }
    if(keyPress_S){
        move(backward, false);
    }
    if(keyPress_D){
        move(right, false);
    }
    updateGL();
}

void GLWindow::changeLevel(Level* l){
    currentLvl = l;
}

void GLWindow::rotateCamera(axis ax , float multiply){
    multiply *= CoreTime::GetDeltaTime();
    if(ax == horizontal){
        camRotation.y += multiply;
        for(int i = 0; i< currentLvl->models.size(); i++){
            Vector3 mRot = currentLvl->models[i]->transform.rotation();
            mRot.y += multiply;
            currentLvl->models[i]->transform.setRotation(mRot);
        }
    }
    else{ // vertical
        camRotation.x += multiply;
        for(int i = 0; i< currentLvl->models.size(); i++){
            Vector3 mRot = currentLvl->models[i]->transform.rotation();
            mRot.x += multiply;
            currentLvl->models[i]->transform.setRotation(mRot);
        }
    }
     emit signalChangeCamRot(camRotation);
}
void GLWindow::updateWindow(){
    globPosX = mapToGlobal(pos()).x();
    globPosY = mapToGlobal(pos()).y();
    globWidth = mapToGlobal(QPoint(width(), height())).x();
    globHeight = mapToGlobal(QPoint(width(), height())).y();
}

void GLWindow::move(motionVector mVector,bool multiply){
    //multiply *= CoreTime::deltaTime;
    for(int i = 0; i< currentLvl->models.size();i++){
        Vector3 mPos = currentLvl->models[i]->transform.position();
        if(mVector == forward || mVector == backward){
            mPos.z +=  cos(camRotation.y * M_PI / 180) * speed * (multiply ? 1 : -1);
            mPos.x +=  sin(camRotation.y * M_PI / 180) * -speed * (multiply ? 1 : -1);
        }
        else{
            mPos.z +=  sin(camRotation.y * M_PI / 180) * speed * (multiply ? 1 : -1);
            mPos.x +=  cos(camRotation.y * M_PI / 180) * -speed * (multiply ? -1 : 1);
        }
        currentLvl->models[i]->transform.setPosition(mPos);
    }
}
void GLWindow::slotChangeGameMode(){
    isGameMode = !isGameMode;
    setMouseTracking(isGameMode);

    if(isGameMode){                  
        //ShowCursor(FALSE);
    }
    else{
        //ShowCursor(TRUE);
    }
    cursor().setPos((globWidth + globPosX) / 2, (globHeight + globPosY) / 2);//set in center window
}
