//
// Created by werl on 23/09/16.
//
#include <QDebug>
#include <iostream>
#include "inc/vertex.h"


Vertex::Vertex(GLdouble offsetx, GLdouble offsety, GLdouble offsetz) {
    selected = false;
    //  font = new FTGLPixmapFont("../Fonts/arial.ttf");
    //  if (font->Error())
    //    fprintf(stderr, "Err");
    //  font->FaceSize(12);

    pos = new GLdouble[3];

    forceX = 0, forceY = 0, forceZ = 0;
    velocityX = 0, velocityY = 0, velocityZ = 0;
    posX = offsetx, posY = offsety, posZ = offsetz;
    colourR = 0, colourB = 0, colourG = 0;

    vertices = new GLdouble[rings * sectors * 3];
    colours = new GLdouble[rings * sectors * 3];
    indices = new GLuint[(rings-1) * (sectors-1) * 4];

    update();

    text = new char[64];
    strcpy(text, "");
}

Vertex::~Vertex() {
    delete indices;
    delete vertices;
    delete colours;
}

void Vertex::update() {
    mtx.lock();

    const GLfloat RINGS = (float) 1.0 / (rings - 1);
    const GLfloat SECTORS = (float) 1.0 / (sectors - 1);
    int r, s, vertIndex = 0;
    indIndex = 0;
    for (r = 0; r < rings; r++) {
        for (s = 0; s < sectors; s++) {

            GLdouble x = posX + cos(2 * M_PI * s * SECTORS) * sin(M_PI * r * RINGS);
            GLdouble y = posY + sin(-M_PI_2 + M_PI * r * RINGS);
            GLdouble z = posZ + sin(2 * M_PI * s * SECTORS) * sin(M_PI * r * RINGS);

            vertices[vertIndex++] = x * radius;
            vertices[vertIndex++] = y * radius;
            vertices[vertIndex++] = z * radius;
        }
    }

    for (r = 0; r < rings - 1; r++){
        for (s = 0; s < sectors - 1; s++) {
            indices[indIndex++] = r * sectors + s;
            indices[indIndex++] = r * sectors + (s + 1);
            indices[indIndex++] = (r + 1) * sectors + (s + 1);
            indices[indIndex++] = (r + 1) * sectors + s;
        }
    }

    mtx.unlock();

}

void Vertex::draw() {
    mtx.lock();

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_DOUBLE, 0, this->vertices);

    if (selected) {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glColorPointer(3, GL_DOUBLE, 0, NULL);
        glDrawElements(GL_QUADS, this->indIndex, GL_UNSIGNED_INT, this->indices);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPolygonOffset(-3.5f, -3.5f);
    glColorPointer(3, GL_DOUBLE, 0, colours);
    glDrawElements(GL_QUADS, this->indIndex, GL_UNSIGNED_INT, this->indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glPolygonOffset(0, 0);

    mtx.unlock();
}

void Vertex::drawText() {
    if (!strlen(text) < 1) {
        glPixelTransferf(GL_RED_BIAS, -1.0f);
        glPixelTransferf(GL_GREEN_BIAS, -1.0f);
        glPixelTransferf(GL_BLUE_BIAS, -1.0f);

        getScreenPosition(pos);
        //    font->Render(text, -1, FTPoint(pos[0], pos[1], pos[2]));
    }
}

void Vertex::setColour(GLdouble R, GLdouble G, GLdouble B) {
    colourR = R;
    colourG = G;
    colourB = B;

    int colIndex = 0;

    for (int r = 0; r < rings; r++) {
        for (int s = 0; s < sectors; s++) {
            colours[colIndex++] = colourR;
            colours[colIndex++] = colourG;
            colours[colIndex++] = colourB;
        }
    }
}

GLdouble *Vertex::getColour(GLdouble *colours) {
    colours[0] = colourR;
    colours[1] = colourG;
    colours[2] = colourB;
}

bool Vertex::isPointerOver(double x, double y, int width, int height) {
    GLdouble proj[16];
    GLdouble model[16];
    GLint view[4];
    GLdouble center[3];
    GLdouble edge[3];

    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetIntegerv(GL_VIEWPORT, view);

    gluProject(posX * 0.01, // posX * 0.01
               posY * 0.01,
               posZ * 0.01,
               model,
               proj,
               view,
               center,
               center + 1,
               center + 2);

    gluProject(vertices[15],
            vertices[16],
            vertices[17],
            model,
            proj,
            view,
            edge,
            edge + 1,
            edge + 2);

    double maxMouseDistance =
            sqrt(((center[0] - edge[0]) * (center[0] - edge[0])) +
            ((center[1] - edge[1]) * (center[1] - edge[1])));

    double pointerDistance = sqrt(((center[0] - x) * (center[0] - x))
            + ((center[1] - (height - y))
            * (center[1] - (height - y))));

    return pointerDistance < maxMouseDistance;
}

double Vertex::getDepth() {
    GLdouble proj[16];
    GLdouble model[16];
    GLint view[4];
    GLdouble center[3];

    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetIntegerv(GL_VIEWPORT, view);

    gluProject(posX * 0.01,
               posY * 0.01,
               posZ * 0.01,
               model,
               proj,
               view,
               center,
               center + 1,
               center + 2);

    return center[2];
}

void *Vertex::getScreenPosition(GLdouble *pos) {
    GLdouble proj[16];
    GLdouble model[16];
    GLint view[4];

    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetIntegerv(GL_VIEWPORT, view);

    gluProject(posX * 0.01,
               posY * 0.01,
               posZ * 0.01,
               model,
               proj,
               view,
               pos,
               pos + 1,
               pos + 2);
}

void Vertex::setPositionFromScreen(double x, double y) {
    GLdouble proj[16];
    GLdouble model[16];
    GLint view[4];

    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetIntegerv(GL_VIEWPORT, view);

    GLdouble obj[3];

    gluUnProject(x,
                 y,
                 -1,
                 model,
                 proj,
                 view,
                 obj,
                 obj + 1,
                 obj + 2);

    posX = obj[0] * 100;
    posY = obj[1] * 100;
}

//void Vertex::attachPoint(Vertex *p) {
//    attachedPoints.push_back(p);
//    Edge *l = new Edge(posX * 0.1, posY * 0.1, posZ * 0.1,
//                       p->posX * 0.1, p->posY * 0.1, p->posZ * 0.1);
//    l->base = this;
//    l->connect = p;
//    edges.push_back(l);
//}

void Vertex::setText(const char *t) {
    strcpy(text, t);
}

string Vertex::getName() const
{
    return name;
}

void Vertex::setName(const string &value)
{
    name = value;
}
