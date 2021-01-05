#include "cube.h"

Cube::Cube(GLWindow* parent,QString name):Model(parent,name)
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
        { { +1.0, -1.0, +1.0 }, { +1.0, -1.0, -1.0 },
        { +1.0, +1.0, -1.0 }, { +1.0, +1.0, +1.0 } },
        { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, +1.0 },
        { -1.0, +1.0, +1.0 }, { -1.0, +1.0, -1.0 } },
        { { +1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 },
        { -1.0, +1.0, -1.0 }, { +1.0, +1.0, -1.0 } },
        { { -1.0, -1.0, +1.0 }, { +1.0, -1.0, +1.0 },
        { +1.0, +1.0, +1.0 }, { -1.0, +1.0, +1.0 } },
        { { -1.0, -1.0, -1.0 }, { +1.0, -1.0, -1.0 },
        { +1.0, -1.0, +1.0 }, { -1.0, -1.0, +1.0 } },
        { { -1.0, +1.0, +1.0 }, { +1.0, +1.0, +1.0 },
        { +1.0, +1.0, -1.0 }, { -1.0, +1.0, -1.0 } }
    };
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glTranslatef(positionX,positionY,positionZ);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    glScalef(scaleX,scaleY,scaleZ);
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
