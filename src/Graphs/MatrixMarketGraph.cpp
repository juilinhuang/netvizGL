//
// Created by william on 30/01/17.
//

#include <zconf.h>
#include "../../inc/Graphs/MatrixMarketGraph.h"
#include "../../inc/Graphs/mmio.h"
#include "../../src/Graphs/mmio.c"
#include <QDebug>

MatrixMarketGraph::MatrixMarketGraph(char *filePath) {
    read(filePath);
    createGraphData();
    setRandomColour();
}

MatrixMarketGraph::~MatrixMarketGraph() {
    qDebug() << "delete MatrixMarketGraph";
}

// Taken from the example @ http://math.nist.gov/MatrixMarket/mmio-c.html
void MatrixMarketGraph::read(char *filePath) {
    int ret_code;
    MM_typecode matcode;
    FILE *f;
    int rows, cols, edgs;
    int *I, *J;

    if ((f = fopen(filePath, "r")) == NULL) {
//        fprintf(stderr, "File not Opened");
        return;
    }

    if (mm_read_banner(f, &matcode) != 0) {
//        printf("\nCould not process Matrix Market banner.\n");
        exit(1);
    }

    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */
    //  if (!mm_is_coordinate(matcode) || mm_is_integer(matcode)) {
    if (!mm_is_coordinate(matcode) || !mm_is_pattern(matcode) || !mm_is_symmetric(matcode)) {
//        printf("Sorry, this application only supports graphs that are:");
//        printf("Matrix Market type: [%s][%s][%s]\n", MM_COORDINATE_STR, MM_PATTERN_STR, MM_SYMM_STR);
//        printf("and not: [%s]\n", MM_INT_STR);
        exit(1);
    }

    /* find out size of sparse matrix .... */
    ret_code = mm_read_mtx_crd_size(f, &rows, &cols, &edgs);

    if (ret_code != 0)
        exit(1);

    /* reseve memory for matrices */
    I = (int *) malloc(edgs * sizeof(int));
    J = (int *) malloc(edgs * sizeof(int));

    for (int i = 0; i < edgs; i++) {
        fscanf(f, "%d %d\n", &I[i], &J[i]);
        I[i]--;  /* adjust from 1-based to 0-based */
        J[i]--;
        if(I[i] == J[i])
            continue;
        int *e = new int[2];
        e[0] = I[i];
        e[1] = J[i];
        edgeList.push_back(e);
    }
    fclose(f);

    mm_write_banner(stdout, matcode);
    mm_write_mtx_crd_size(stdout, rows, cols, edgs);
}


