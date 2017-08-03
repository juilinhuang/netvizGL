#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "../Graphs/Graph.h"
#include "Command.h"

/*!
 \brief

*/
class GLWindow{

public:

    /*!
     \brief

     \return int
    */
    virtual int getWidth() = 0;
    /*!
     \brief

     \return int
    */
    virtual int getHeight() = 0;

    /*!
     \brief

     \return Graph
    */
    Graph *getGraph() const
    {
        return graph;
    }
    /*!
     \brief

     \param g
    */
    void setGraph(Graph *g)
    {
        graph = g;
    }
    /*!
     \brief

     \return char
    */
    char *getPath() const
    {
        return path;
    }
    /*!
     \brief

     \param p
    */
    void setPath(char *p)
    {
        path = p;
    }
    /*!
     \brief

     \return GLdouble
    */
    GLdouble getMouseX() const
    {
        return mouseX;
    }
    /*!
     \brief

     \return GLdouble
    */
    GLdouble getMouseY() const
    {
        return mouseY;
    }
    /*!
     \brief

     \return Vertex
    */
    Vertex *getSelectedNode() const
    {
        return selectedNode;
    }
    /*!
     \brief

     \param v
    */
    void setSelectedNode(Vertex *v)
    {
        selectedNode = v;
    }
    /*!
     \brief

     \return GLdouble
    */
    GLdouble getMouseDiffX() const
    {
        return mouseDiffX;
    }
    /*!
     \brief

     \return GLdouble
    */
    GLdouble getMouseDiffY() const
    {
        return mouseDiffY;
    }
    /*!
     \brief

     \return GLdouble
    */
    GLdouble getTranslateZ() const
    {
        return translateZ;
    }
    /*!
     \brief

     \return int
    */
    int getSelectedVertexNumber() const
    {
        return selectedVertexNumber;
    }
    /*!
     \brief

     \param sv
    */
    void setSelectedVertexNumber(int sv)
    {
        selectedVertexNumber = sv;
    }

protected:
    Command *c; /*!< TODO: describe */
    Command *sv; /*!< TODO: describe */
    Command *dragv; /*!< TODO: describe */
    Command *deletev; /*!< TODO: describe */

    GLdouble pitch, yaw, bank; /*!< TODO: describe */
    GLdouble translateX, translateY, translateZ; /*!< TODO: describe */
    GLdouble mouseX; /*!< TODO: describe */
    GLdouble mouseY; /*!< TODO: describe */
    GLdouble mouseDiffX; /*!< TODO: describe */
    GLdouble mouseDiffY; /*!< TODO: describe */
    bool isMouseLeftDown, isMouseMiddleDown, isMouseRightDown; /*!< TODO: describe */
    bool isKeyCtrlDown; /*!< TODO: describe */


    Graph *graph; /*!< TODO: describe */
    Vertex *selectedNode; /*!< TODO: describe */
    Edge *selectedEdge;
    int selectedVertexNumber; /*!< TODO: describe */
    char* path; /*!< TODO: describe */

};

#endif // GLWINDOW_H
