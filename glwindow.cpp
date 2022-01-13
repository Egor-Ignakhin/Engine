#include "glwindow.h"
#include "level.h"
#include "CoreTime.h"
#include <QColorDialog>
#include <QDebug>
#include "model.h"
#include <GL/glu.h>
#include <QApplication>
#include "math.h"

const static float pi=3.141593, k=pi/180; // глобальная переменная

GLfloat VertexArray[12][3]; // декларируем массив вершин
GLfloat ColorArray[12][3];  // декларируем массив цветов вершин
GLubyte IndexArray[20][3];  // декларируем массив индексов вершин

GLWindow::GLWindow(QWidget* parent) : QGLWidget(parent), camRotation(0,0,0)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));    
    setFocusPolicy(Qt::StrongFocus);

    qDebug() << "Создание " << typeid(*this).name();
}
void GLWindow::initializeGL()
{
    // цвет для очистки буфера изображения - будет просто фон окна
       qglClearColor(Qt::white);
       glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
       glShadeModel(GL_FLAT);    // отключает режим сглаживания цветов
       // устанавливаем режим, когда строятся только внешние поверхности
       glEnable(GL_CULL_FACE);

    getVertexArray(); // определить массив вершин
       getColorArray();  // определить массив цветов вершин
       getIndexArray();  // определить массив индексов вершин

       glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
          glEnableClientState(GL_COLOR_ARRAY);  // активизация массива цветов вершин
}

void GLWindow::getVertexArray() // определить массив вершин
{
   GLfloat R=0.75; // радиус сферы

   // начальные значения для икосаэдра
   GLfloat a=4*R/sqrt(10+2*sqrt(5)); // сторона икосаэдра
   GLfloat alpha=acos((1-a*a/2/R/R)); // первый угол поворота по тэта
   // cos(alpha)=(1-a*a/2/R/R)

   // вычисляем точки икосаэдра
   //0 точка
   VertexArray[0][0]=0;   // x
   VertexArray[0][1]=0;   // y
   VertexArray[0][2]=R;   // z

   //1 точка
   VertexArray[1][0]=R*sin(alpha)*sin(0);
   VertexArray[1][1]=R*sin(alpha)*cos(0);
   VertexArray[1][2]=R*cos(alpha);

   //2 точка
   VertexArray[2][0]=R*sin(alpha)*sin(72*k);
   VertexArray[2][1]=R*sin(alpha)*cos(72*k);
   VertexArray[2][2]=R*cos(alpha);

   //3 точка
   VertexArray[3][0]=R*sin(alpha)*sin(2*72*k);
   VertexArray[3][1]=R*sin(alpha)*cos(2*72*k);
   VertexArray[3][2]=R*cos(alpha);

   //4 точка
   VertexArray[4][0]=R*sin(alpha)*sin(3*72*k);
   VertexArray[4][1]=R*sin(alpha)*cos(3*72*k);
   VertexArray[4][2]=R*cos(alpha);

   //5 точка
   VertexArray[5][0]=R*sin(alpha)*sin(4*72*k);
   VertexArray[5][1]=R*sin(alpha)*cos(4*72*k);
   VertexArray[5][2]=R*cos(alpha);

   //6 точка
   VertexArray[6][0]=R*sin(pi-alpha)*sin(-36*k);
   VertexArray[6][1]=R*sin(pi-alpha)*cos(-36*k);
   VertexArray[6][2]=R*cos(pi-alpha);

   //7 точка
   VertexArray[7][0]=R*sin(pi-alpha)*sin(36*k);
   VertexArray[7][1]=R*sin(pi-alpha)*cos(36*k);
   VertexArray[7][2]=R*cos(pi-alpha);

   //8 точка
   VertexArray[8][0]=R*sin(pi-alpha)*sin((36+72)*k);
   VertexArray[8][1]=R*sin(pi-alpha)*cos((36+72)*k);
   VertexArray[8][2]=R*cos(pi-alpha);

   //9 точка
   VertexArray[9][0]=R*sin(pi-alpha)*sin((36+2*72)*k);
   VertexArray[9][1]=R*sin(pi-alpha)*cos((36+2*72)*k);
   VertexArray[9][2]=R*cos(pi-alpha);

   //10 точка
   VertexArray[10][0]=R*sin(pi-alpha)*sin((36+3*72)*k);
   VertexArray[10][1]=R*sin(pi-alpha)*cos((36+3*72)*k);
   VertexArray[10][2]=R*cos(pi-alpha);

   //11 точка
   VertexArray[11][0]=0;
   VertexArray[11][1]=0;
   VertexArray[11][2]=-R;
}

void GLWindow::getColorArray() // определить массив цветов вершин
{
   for (int i=0; i<12; i++)
   {
      ColorArray[i][0]=0.1f*(qrand()%11); // R - красная составляющая
      ColorArray[i][1]=0.1f*(qrand()%11); // G - зелёная составляющая
      ColorArray[i][2]=0.1f*(qrand()%11); // B - синяя составляющая
      // qrand()%11 - псевдослучайное число от 0 до 10
   }
}

void GLWindow::getIndexArray()   // определить массив индексов
{
   // 0 треугольник
   IndexArray[0][0]=0; // индекс (номер) 1-ой вершины
   IndexArray[0][1]=2; // индекс (номер) 2-ой вершины
   IndexArray[0][2]=1; // индекс (номер) 3-ей вершины

   // 1 треугольник
   IndexArray[1][0]=0;
   IndexArray[1][1]=3;
   IndexArray[1][2]=2;

   // 2 треугольник
   IndexArray[2][0]=0;
   IndexArray[2][1]=4;
   IndexArray[2][2]=3;

   // 3 треугольник
   IndexArray[3][0]=0;
   IndexArray[3][1]=5;
   IndexArray[3][2]=4;

   // 4 треугольник
   IndexArray[4][0]=0;
   IndexArray[4][1]=1;
   IndexArray[4][2]=5;

   // 5 треугольник
   IndexArray[5][0]=6;
   IndexArray[5][1]=1;
   IndexArray[5][2]=7;

   // 6 треугольник
   IndexArray[6][0]=7;
   IndexArray[6][1]=1;
   IndexArray[6][2]=2;

   // 7 треугольник
   IndexArray[7][0]=7;
   IndexArray[7][1]=2;
   IndexArray[7][2]=8;

   // 8 треугольник
   IndexArray[8][0]=8;
   IndexArray[8][1]=2;
   IndexArray[8][2]=3;

   // 9 треугольник
   IndexArray[9][0]=8;
   IndexArray[9][1]=3;
   IndexArray[9][2]=9;

   // 10 треугольник
   IndexArray[10][0]=9;
   IndexArray[10][1]=3;
   IndexArray[10][2]=4;

   // 11 треугольник
   IndexArray[11][0]=9;
   IndexArray[11][1]=4;
   IndexArray[11][2]=10;

   // 12 треугольник
   IndexArray[12][0]=10;
   IndexArray[12][1]=4;
   IndexArray[12][2]=5;

   // 13 треугольник
   IndexArray[13][0]=10;
   IndexArray[13][1]=5;
   IndexArray[13][2]=6;

   // 14 треугольник
   IndexArray[14][0]=6;
   IndexArray[14][1]=5;
   IndexArray[14][2]=1;

   // 15 треугольник
   IndexArray[15][0]=7;
   IndexArray[15][1]=11;
   IndexArray[15][2]=6;

   // 16 треугольник
   IndexArray[16][0]=8;
   IndexArray[16][1]=11;
   IndexArray[16][2]=7;

   // 17 треугольник
   IndexArray[17][0]=9;
   IndexArray[17][1]=11;
   IndexArray[17][2]=8;

   // 18 треугольник
   IndexArray[18][0]=10;
   IndexArray[18][1]=11;
   IndexArray[18][2]=9;

   // 19 треугольник
   IndexArray[19][0]=6;
   IndexArray[19][1]=11;
   IndexArray[19][2]=10;
}

void GLWindow::resizeGL(int width, int height)
{
    updateWindow();

    glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
      glLoadIdentity();            // присваивает проекционной матрице единичную матрицу

      // отношение высоты окна виджета к его ширине
      GLfloat ratio=(GLfloat)height/(GLfloat)width;

      // мировое окно
      if (width>=height)
         // параметры видимости ортогональной проекции
         glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
      else
         glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);
      // плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)

      // параметры видимости перспективной проекции
      // glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
      // плоскости отсечения (левая, правая, верхняя, нижняя, ближняя, дальняя)

      // поле просмотра
      glViewport(0, 0, (GLint)width, (GLint)height);
}

void GLWindow::paintGL()
{
    // очистка буфера изображения и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // устанавливаем положение и ориентацию матрице моделирования
    glMatrixMode(GL_MODELVIEW);

    // загружаем единичную матрицу моделирования
    glLoadIdentity();

    // последовательные преобразования
       glScalef(1, 1, 1);        // масштабирование
       glTranslatef(0.0f, 0, 0.0f);    // трансляция
       glRotatef(0, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X
       glRotatef(0, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
       glRotatef(0, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z

    /*glViewport(0, 0, width(), height());
    glClearColor(0, 0, 0, 0);
    double aspect = width() / height();
    glOrtho(-150, 150, -112, 112, -2000.0, 2000.0);//glOrtho(hor+, hor-, up+ , up-, nearPlane, farPlane);
    gluPerspective(60.0, aspect, 0.01, 2000.0);//fov,aspect */

       drawAxis();   // рисование осей координат

       drawFigure(); // нарисовать фигуру

    for(int i = 0; i < currentLvl->models.size();i++){
        currentLvl->models[i]->draw();
    }
}

void GLWindow::drawAxis() // построить оси координат
{
   // устанавливаем ширину линии приближенно в пикселях
   glLineWidth(3.0f);
   // до вызова команды ширина равна 1 пикселю по умолчанию

   // устанавливаем цвет последующих примитивов
   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   // ось x красного цвета
   glBegin(GL_LINES); // построение линии
      glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
      glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      // ось y зеленого цвета
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      // ось z синего цвета
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}

void GLWindow::drawFigure() // построить фигуру
{
   // указываем, откуда нужно извлечь данные о массиве вершин
   glVertexPointer(3, GL_FLOAT, 0, VertexArray);
   // указываем, откуда нужно извлечь данные о массиве цветов вершин
   glColorPointer(3, GL_FLOAT, 0, ColorArray);
   // используя массивы вершин и индексов, строим поверхности
   glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_BYTE, IndexArray);
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

GLWindow::~GLWindow(){
    qDebug() << "Удаление " << typeid(*this).name();
}
