#include "testmodel.h"

TestModel::TestModel(Level* pLevel, QString name):Model(pLevel, name)
{

}

void TestModel::draw(){





   static const GLfloat coords[4] [2] =
   {
       { -1.0, 1.0 }, { 1.0, 1.0 },
       { 1.0, -1.0 }, { -1.0, -1.0}
   };
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef(transform.rotation().x, 1.0, 0.0, 0.0);
   glRotatef(transform.rotation().y, 0.0, 1.0, 0.0);
   glTranslatef(transform.position().x, transform.position().y, 0);
   glScalef(transform.scale().x, transform.scale().y, 1);


       glLoadName(0);
       glBegin(GL_QUADS);
       QColor modelColor = Qt::blue;
       pWindow->qglColor(modelColor);

       for (int i = 0; i < 4; ++i) {
           glVertex2d(coords[i] [0], coords[i] [1]);
       }
       glEnd();

}
