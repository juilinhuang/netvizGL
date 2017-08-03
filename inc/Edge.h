//
// Created by werl on 29/09/16.
//

#ifndef NETVIZGL_LINE_H
#define NETVIZGL_LINE_H

#include <GL/glu.h>
#include "Vertex.h"

class Edge {
public:
    static const double scale;
    GLdouble posX1, posY1, posZ1;
    GLdouble posX2, posY2, posZ2;
    GLdouble *vertices;
    GLfloat *colours;
    Vertex *base, *connect;

    Edge(Vertex *base,Vertex *connect);
    ~Edge();

    void update();
    void draw();
    void drawText();
    void setColour(GLfloat r, GLfloat g, GLfloat b, GLfloat r2, GLfloat g2, GLfloat b2);

//  FTPixmapFont *font;
    char *text;
    void setText(const char *t);
};

#endif //NETVIZGL_LINE_H
