//
// Created by william on 21/02/17.
//

#ifndef NETVIZGL_SELECTVERTEX_H
#define NETVIZGL_SELECTVERTEX_H

#include <QDebug>
#include <algorithm>
#include "Command.h"
#include "glwidget.h"

class SelectVertex : public Command{
private:
    GLWindow *window;
public:
    SelectVertex(GLWindow *window) : window(window) {
        //        fprintf(stdout, "%s\n", window->getPath());
    }

    ~SelectVertex(){
        delete window;
    }

    void execute() override {
        vector<Vertex *> pointerOver;
        vector<double> depthValues;
        window->setSelectedNode(NULL);
        if (window->getGraph()) {
            for (int i = 0; i < window->getGraph()->numVertices; ++i) {
                if (window->getGraph()->vertices[i]->isPointerOver(window->getMouseX(),
                                                                   window->getMouseY(),
                                                                   window->getWidth(),
                                                                   window->getHeight())) {
                    pointerOver.push_back(window->getGraph()->vertices[i]);
                }
                if(window->getGraph()->vertices[i]->selected){
                    window->getGraph()->vertices[i]->selected = false;
                }
                window->getGraph()->vertices[i]->vertexNumber = i;
            }
        }

        if (pointerOver.size() == 0) {
            return;
        }

        for (int i = 0; i < pointerOver.size(); i++) {
            depthValues.push_back(pointerOver[i]->getDepth());
        }

        double closest = *std::min_element(depthValues.begin(), depthValues.end());

        double *cols = new double[3];
        for (int i = 0; i < pointerOver.size(); i++) {
            if (closest == depthValues[i]) {
                pointerOver[i]->selected = true;
                window->setSelectedVertexNumber(pointerOver[i]->vertexNumber);
                window->setSelectedNode(pointerOver[i]);
            }
        }
    }
};

#endif //NETVIZGL_SELECTVERTEX_H
