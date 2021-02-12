#include <stdio.h>
#include <stdlib.h>

#include "613p_arraygraph.h"

int main(int argc, char* argv[]) {
    int i = 0;
    ArrayGraph* pG1 = NULL;
    ArrayGraph* pG2 = NULL;
    ArrayGraph* pG3 = NULL;

    pG1 = createArrayGraph(6);
    pG2 = createArrayDirectedGraph(6);
    pG3 = createArrayDirectedGraph(6);

    if (pG1 != NULL && pG2 != NULL && pG3 != NULL) {
        for (i = 0 ; i < 6 ; i++) {
            addVertexArrayGraph(pG1, i);
            addVertexArrayGraph(pG2, i);
            addVertexArrayGraph(pG3, i);
        }
        addEdgeArrayGraph(pG1, 0, 1);
        addEdgeArrayGraph(pG1, 0, 2);
        addEdgeArrayGraph(pG1, 1, 2);
        addEdgeArrayGraph(pG1, 2, 3);
        addEdgeArrayGraph(pG1, 3, 4);
        addEdgeArrayGraph(pG1, 3, 5);
        addEdgeArrayGraph(pG1, 4, 5);

        addEdgeArrayGraph(pG2, 0, 1);
        addEdgeArrayGraph(pG2, 1, 2);
        addEdgeArrayGraph(pG2, 2, 0);
        addEdgeArrayGraph(pG2, 2, 1);
        addEdgeArrayGraph(pG2, 2, 3);
        addEdgeArrayGraph(pG2, 3, 2);
        addEdgeArrayGraph(pG2, 3, 4);
        addEdgeArrayGraph(pG2, 4, 5);
        addEdgeArrayGraph(pG2, 5, 3);

        addEdgeWithWeightArrayGraph(pG3, 0, 1, 4);
        addEdgeWithWeightArrayGraph(pG3, 1, 2, 1);
        addEdgeWithWeightArrayGraph(pG3, 2, 0, 2);
        addEdgeWithWeightArrayGraph(pG3, 2, 1, 3);
        addEdgeWithWeightArrayGraph(pG3, 2, 3, 2);
        addEdgeWithWeightArrayGraph(pG3, 3, 2, 1);
        addEdgeWithWeightArrayGraph(pG3, 3, 4, 1);
        addEdgeWithWeightArrayGraph(pG3, 4, 5, 1);
        addEdgeWithWeightArrayGraph(pG3, 5, 3, 2);

        printf("G1 : Undirected\n");
        displayArrayGraph(pG1);
        printf("G2 : Directed\n");
        displayArrayGraph(pG2);
        printf("G3 : Directed Weighted\n");
        displayArrayGraph(pG3);
    }
    return 0;
}


