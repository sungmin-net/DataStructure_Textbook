#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "613p_arraygraph.h"

ArrayGraph* createArrayGraph(int maxVertexCount) {
    int i = 0;
    int j = 0;
    ArrayGraph* pReturn = NULL;
    if (maxVertexCount >0) {
        pReturn = (ArrayGraph*)malloc(sizeof(ArrayGraph));
        if (pReturn == NULL) {
            printf("오류, 메모리할당1, createArrayGraph()\n");
            return NULL;
        }
        pReturn->graphType = GRAPH_UNDIRECTED;
        pReturn->maxVertexCount = maxVertexCount;
    } else {
        printf("오류, 최대 노드 개수는 0보다 커야 합니다.\n");
        return NULL;
    }

    pReturn->pVertex = (int*)malloc(sizeof(int) * maxVertexCount);
    if (pReturn->pVertex == NULL) {
        printf("오류, 메모리할당2, createArrayGraph()\n");
        if (pReturn != NULL) {
            free(pReturn);
        }
        return NULL;
    }

    pReturn->ppAdjEdge = (int**)malloc(sizeof(int*) * maxVertexCount);
    if (pReturn->ppAdjEdge == NULL) {
        printf("오류, 메모리할당3, createArrayGraph()\n");
        if (pReturn->pVertex != NULL) {
            free(pReturn->pVertex);
        }
        if (pReturn != NULL) {
            free(pReturn);
        }
    }

    for (i = 0 ; i < maxVertexCount ; i++) {
        pReturn->ppAdjEdge[i] = (int*)malloc(sizeof(int) * maxVertexCount);
        if (pReturn->ppAdjEdge[i] == NULL) {
            printf("오류, 메모리할당4, createArrayGraph()\n");
            for (j = 0 ; j < i - 1 ; j++) {
                if (pReturn->ppAdjEdge[j] != NULL) {
                    free(pReturn->ppAdjEdge[j]);
                }
            }
            if (pReturn->ppAdjEdge != NULL) {
                free(pReturn->ppAdjEdge);
            }
            if (pReturn->pVertex != NULL) {
                free(pReturn->pVertex);
            }
            if (pReturn != NULL) {
                free(pReturn);
            }
            return NULL;
        }
    }
    memset(pReturn->pVertex, NOT_USED, sizeof(int) * maxVertexCount);
    for (i = 0 ; i < maxVertexCount ; i++) {
        memset(pReturn->ppAdjEdge[i], 0, sizeof(int) * maxVertexCount);
    }
    return pReturn;
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount) {
    ArrayGraph* pReturn = NULL;
    pReturn = createArrayGraph(maxVertexCount);
    if (pReturn != NULL) {
        pReturn->graphType = GRAPH_DIRECTED;
    }
    return pReturn;
}

int addVertexArrayGraph(ArrayGraph* pGraph, int vertexId) {
    int ret = SUCCESS;

    if (pGraph != NULL) {
        if (vertexId < pGraph->maxVertexCount) {
            if (pGraph->pVertex[ vertexId ] == NOT_USED) {
                pGraph->pVertex[ vertexId ] = USED;
                pGraph->currentVertexCount++;
            } else {
                printf("오류, 이미 존재하는 노드 [%d], addVertexArrayGraph()\n",
                        vertexId);
                ret = FAIL;
            }
        } else {
            printf("오류, 최대 노드 개수 초과 [%d], addVertexArrayGraph()\n",
                    vertexId);
            ret = FAIL;
        }
    }
    return ret;
}

int addEdgeWithWeightArrayGraph(ArrayGraph* pGraph, int fromVertexId,
        int toVertexId, int weight) {
    int ret = SUCCESS;

    if (pGraph != NULL) {
        if (checkVertexValid(pGraph, fromVertexId) != SUCCESS) {
            ret = FAIL;
            return ret;
        }

        if (checkVertexValid(pGraph, toVertexId) != SUCCESS) {
            ret = FAIL;
            return ret;
        }
        pGraph->ppAdjEdge[ fromVertexId ][ toVertexId ] = weight;

        if (pGraph->graphType == GRAPH_UNDIRECTED) {
            pGraph->ppAdjEdge[ toVertexId ][ fromVertexId ] = weight;
        }
    }
    return ret;
}

int checkVertexValid(ArrayGraph* pGraph, int vertexId) {
    int ret = SUCCESS;

    if (vertexId >= pGraph->maxVertexCount
            || pGraph->pVertex[ vertexId ] == NOT_USED) {
        printf("오류, 노드 정보 [%d]\n", vertexId);
        ret = FAIL;
    }
    return ret;
}

int addEdgeArrayGraph(ArrayGraph* pGraph, int fromVertexId, int toVertexId) {
    return addEdgeWithWeightArrayGraph(pGraph, fromVertexId, toVertexId, USED);
}

int removeEdgeArrayGraph(ArrayGraph* pGraph, int fromVertexId, int toVertexId) {
    int ret = SUCCESS;

    if (pGraph != NULL) {
        if (checkVertexValid(pGraph, fromVertexId) != SUCCESS) {
            ret = FAIL;
            return ret;
        }

        if (checkVertexValid(pGraph, toVertexId) != SUCCESS) {
            ret = FAIL;
            return ret;
        }

        pGraph->ppAdjEdge[ fromVertexId ][ toVertexId ] = 0;

        if (pGraph->graphType == GRAPH_UNDIRECTED) {
            pGraph->ppAdjEdge[ toVertexId ][ fromVertexId ] = 0;
        }
    }
    return ret;
}

int removeVertexArrayGraph(ArrayGraph* pGraph, int vertexId) {
    int ret = SUCCESS;
    int i = 0;

    if (pGraph != NULL) {
        if (checkVertexValid(pGraph, vertexId) != SUCCESS) {
            ret = FAIL;
            return ret;
        }
        for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
            removeEdgeArrayGraph(pGraph, vertexId, i);
            removeEdgeArrayGraph(pGraph, i, vertexId);
        }
        pGraph->pVertex[ vertexId ] = NOT_USED;
    }
    return ret;
}

void displayArrayGraph(ArrayGraph* pGraph) {
    int i = 0;
    int j = 0;
    if (pGraph != NULL) {
        for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
            for (j = 0 ; j < pGraph->maxVertexCount ; j++) {
                printf("%d ", pGraph->ppAdjEdge[ i ][ j ]);
            }
            printf("\n");
        }
    }
}

void deleteArrayGraph(ArrayGraph* pGraph) {
    int i = 0;
    if (pGraph != NULL) {
        for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
            free(pGraph->ppAdjEdge[ i ]);
        }
        free(pGraph->ppAdjEdge);
        free(pGraph->pVertex);
        free(pGraph);
    }
}

int isEmptyArrayGraph(ArrayGraph* pGraph) {
    int ret = TRUE;
    if (pGraph != NULL) {
        if (pGraph->currentVertexCount > 0) {
            ret = FALSE;
        }
    }
    return ret;
}

