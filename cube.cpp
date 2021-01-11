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
    glRotatef(rotation.x, 1.0, 0.0, 0.0);
    glRotatef(rotation.y, 0.0, 1.0, 0.0);
    glRotatef(rotation.z, 0.0,  0.0, 1.0);
    glTranslatef(position.x,position.y,position.z);
    glScalef(scale.x, scale.y, scale.z);

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
