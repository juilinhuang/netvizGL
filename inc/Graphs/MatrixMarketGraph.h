//
// Created by william on 30/01/17.
//

#ifndef NETVIZGL_MATRIXMARKETGRAPH_H
#define NETVIZGL_MATRIXMARKETGRAPH_H

#include "Graph.h"

class MatrixMarketGraph : public Graph {
public:
    MatrixMarketGraph(char *filePath);
    ~MatrixMarketGraph() override;

private:
    void read(char *filePath);
};

#endif //NETVIZGL_MATRIXMARKETGRAPH_H
