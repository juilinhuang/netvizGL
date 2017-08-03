//
// Created by werl on 11/11/16.
//

#ifndef NETVIZGL_EDGEGRAPH_H
#define NETVIZGL_EDGEGRAPH_H

#include "Graph.h"
#include <QtCore>

class EdgeGraph : public Graph {
public:
    EdgeGraph(char *filePath);
    EdgeGraph(vector<int *> newEdgeList);
    virtual ~EdgeGraph();
};

#endif //NETVIZGL_EDGEGRAPH_H
