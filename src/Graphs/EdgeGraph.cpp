//
// Created by werl on 11/11/16.
//

#include <cstdlib>
#include <fstream>
#include "../../inc/Graphs/EdgeGraph.h"
#include <QDebug>
#include <QSet>

EdgeGraph::EdgeGraph(char *filePath){
    read(filePath);
    edgeList = rawDataFromFile;
    createGraphData();
    setRandomColour();
}

EdgeGraph::EdgeGraph(vector<int *> newEdgeList) {
    edgeList = newEdgeList;
    createGraphData();
}

EdgeGraph::~EdgeGraph() {
    qDebug() << "delete EdgeGraph";
}
