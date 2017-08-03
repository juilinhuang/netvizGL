//
// Created by werl on 11/11/16.
//

#include <sys/time.h>
#include <cstdlib>
#include <zconf.h>
#include <fstream>
#include "../../inc/Graphs/AdjacencyGraph.h"
#include <QDebug>

AdjacencyGraph::AdjacencyGraph(char *filePath) {
    read(filePath);
    for (int i = 0; i < rawDataFromFile.size(); ++i) {
        for (int j = 0; j < rawDataFromFile.size(); ++j) {
            if(rawDataFromFile[i][j] == 0 || i == j)
                continue;
            int *e = new int[2];
            e[0] = i;
            e[1] = j;
            edgeList.push_back(e);
        }
    }
    createGraphData();
    setRandomColour();
}

AdjacencyGraph::~AdjacencyGraph() {
    qDebug() << "delete AdjacencyGraph";
}

