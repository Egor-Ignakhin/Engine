#include "cube.h"

Cube::Cube(Level* pLevel,QString name):Model(pLevel, name)
{
    faceColors[0] = Qt::red;
    faceColors[1] = Qt::green;
    faceColors[2] = Qt::blue;
    faceColors[3] = Qt::cyan;
    faceColors[4] = Qt::yellow;
    faceColors[5] = Qt::magenta;
}
void Cube::draw(){
    static const GLfloat coords[6] [4] [3] = {
        { { 1.0, -1.0, 1.0 }, { 1.0, -1.0, -1.0 },
        { 1.0, 1.0, -1.0 }, { 1.0, 1.0, 1.0 } },
        { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, 1.0 },
        { -1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 } },
        { { 1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 },
        { -1.0, 1.0, -1.0 }, { 1.0, 1.0, -1.0 } },
        { { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 },
        { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } },
        { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },
        { 1.0, -1.0, 1.0 }, { -1.0, -1.0, 1.0 } },
        { { -1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 },
        { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 } }
    };
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(transform.rotation().x, 1.0, 0.0, 0.0);
    glRotatef(transform.rotation().y, 0.0, 1.0, 0.0);
    glRotatef(transform.rotation().z, 0.0,  0.0, 1.0);
    glTranslatef(transform.position().x, transform.position().y,transform.position().z);
    glScalef(transform.scale().x, transform.scale().y, transform.scale().z);

    for (int i = 0; i < 6; ++i) {
        glLoadName(i);
        glBegin(GL_QUADS);
        pWindow->qglColor(faceColors[i]);

        for (int j = 0; j < 4; ++j) {
            glVertex3f(coords[i] [j] [0], coords[i] [j] [1],
            coords[i] [j] [2]);
        }
        glEnd();
    }
}
