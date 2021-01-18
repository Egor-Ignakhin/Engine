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
    glOrtho(-100, 100, -100, 100, -200.0, 2000.0);//glOrtho(hor+, hor-, up+ , up-, nearPlane, farPlane);
    gluPerspective(60.0, aspect, 0, 2000.0);//fov,aspect
    glMatrixMode(GL_MODELVIEW);

    for(int i = 0; i < currentLvl->models.size();i++){
        currentLvl->models[i]->draw();
    }
}

void GLWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
   // int face = faceAtPosition(event->pos());
    //if (face != -1) {
      //  QColor color = QColorDialog::getColor( curmodel->faceColors[face],
       //                                        this);
        //if (color.isValid()) {
          //  curmodel->faceColors[face] = color;
        //}
    //}
}
bool GLWindow::eventFilter(QObject* obj, QEvent* event){

  /*  else if(event->type() == QEvent::Leave){
        if(isGameMode){
            cursor().setPos((globWidth + globPosX) / 2, (globHeight + globPosY) / 2);
        }
    }*/
    return false;
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
        QPoint currentPos = cursor().pos();//текущая позиция
        cursor().setPos((globWidth + globPosX) / 2, (globHeight + globPosY) / 2);//set in center window

        if(currentPos.x() > globPosX && currentPos.y() < globWidth &&// intersect cursor
                currentPos.x() > globPosY && currentPos.y() < globHeight){


            float dx = (currentPos.x() - (globWidth + globPosX) / 2) * 0.1f;
            float dy = (currentPos.y() - (globHeight + globPosY) / 2) * 0.1f;

            rotateCamera(horizontal, dx * sensivity);//поворот относительно смещения
            rotateCamera(vertical, dy * sensivity);//поворот относительно смещения
        }
    }

    updateGL();
    /*
                                                                                        GLfloat dy = (GLfloat) (event->y() - lastPos.y()) / height();
                                                                                        Vector3 newRot = curmodel->getRotation();
                                                                                        if (event->buttons() & Qt::LeftButton) {
                                                                                            newRot.x += 180 * dy;
                                                                                            newRot.y += 180 * dx;
                                                                                        } else if (event->buttons() & Qt::RightButton) {
                                                                                            newRot.x += 180 * dy;
                                                                                            newRot.z += 180 * dx;
                                                                                        }curmodel->setRotation(newRot);*/
}

void GLWindow::changeLevel(Level* l){
    currentLvl = l;
}

void GLWindow::rotateCamera(axis ax , float multiply){
    multiply *= CoreTime::deltaTime;
    if(ax == horizontal){
        camRotation.y += multiply;
        for(int i = 0; i< currentLvl->models.size(); i++){
            Vector3 mRot = currentLvl->models[i]->getRotation();
            mRot.y += multiply;
            currentLvl->models[i]->setRotation(mRot);
        }
    }
    else{ // vertical
        camRotation.x += multiply;
        for(int i = 0; i< currentLvl->models.size(); i++){
            Vector3 mRot = currentLvl->models[i]->getRotation();
            mRot.x += multiply;
            currentLvl->models[i]->setRotation(mRot);
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
    multiply *= CoreTime::deltaTime;
    for(int i = 0; i< currentLvl->models.size();i++){
        Vector3 mPos = currentLvl->models[i]->getPosition();
        if(mVector == forward || mVector == backward){
            mPos.z +=  cos(camRotation.y * M_PI / 180) * speed * (multiply ? 1 : -1);
            mPos.x +=  sin(camRotation.y * M_PI / 180) * -speed * (multiply ? 1 : -1);
        }
        else{
            mPos.z +=  sin(camRotation.y * M_PI / 180) * speed * (multiply ? 1 : -1);
            mPos.x +=  cos(camRotation.y * M_PI / 180) * -speed * (multiply ? -1 : 1);
        }
        currentLvl->models[i]->setPosition(mPos);
    }
    //qDebug() <<  "z is " +  QString::number(cos(camRotation.y * M_PI / 180) * speed);
    //qDebug() << "x is " +  QString::number(sin(camRotation.y * M_PI / 180) * speed);
    //qDebug() <<mVector << multiply;
}
void GLWindow::slotChangeGameMode(){       
    isGameMode = !isGameMode;
    setMouseTracking(isGameMode);

    if(isGameMode){                  
        ShowCursor(FALSE);
    }
    else{
        ShowCursor(TRUE);        
    }
    cursor().setPos((globWidth + globPosX) / 2, (globHeight + globPosY) / 2);//set in center window
}
