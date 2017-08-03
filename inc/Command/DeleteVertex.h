//
// Created by william on 20/02/17.
//

#ifndef NETVIZGL_UPDATEGRAPH_H
#define NETVIZGL_UPDATEGRAPH_H

#include "Command.h"
#include "../Graphs/EdgeGraph.h"
#include "glwindow.h"

class DeleteVertex : public Command {
private:
    GLWindow *window;
public:
    DeleteVertex(GLWindow *window, int deletedNode)
        : window(window), deleteNode(deletedNode) {}
    ~DeleteVertex(){}
    int deleteNode;

    void execute() override {
        if (window->getGraph() && deleteNode >= 0 && deleteNode <= window->getGraph()->vertices.size()) {
            vector<int *> newEdgeList = window->getGraph()->edgeList;

            window->getGraph()->set.erase(deleteNode);
            window->getGraph()->vertices.erase(window->getGraph()->vertices.begin() + deleteNode);

            for (int i = 0; i < newEdgeList.size(); ++i) {
                if ((newEdgeList[i][0] == deleteNode ||
                     newEdgeList[i][1] == deleteNode)) {
                    newEdgeList.erase(newEdgeList.begin() + i);
                    i--;
                }
            }
            for (int i = 0; i < newEdgeList.size(); ++i) {
                if (newEdgeList[i][0] > deleteNode)
                    newEdgeList[i][0]--;
                if (newEdgeList[i][1] > deleteNode)
                    newEdgeList[i][1]--;
            }

            Graph *temp = window->getGraph();
            window->setGraph(new EdgeGraph(newEdgeList));
            GLdouble *colours = new GLdouble[3];

            for (int i = 0; i < window->getGraph()->vertices.size(); ++i) {
                window->getGraph()->vertices[i]->posX = temp->vertices[i]->posX;
                window->getGraph()->vertices[i]->posY = temp->vertices[i]->posY;
                window->getGraph()->vertices[i]->posZ = temp->vertices[i]->posZ;

                window->getGraph()->vertices[i]->setText(temp->vertices[i]->text);

                temp->vertices[i]->getColour(colours);
                window->getGraph()->vertices[i]->setColour(colours[0], colours[1], colours[2]);
            }
        }
    }
};

#endif //NETVIZGL_UPDATEGRAPH_H
