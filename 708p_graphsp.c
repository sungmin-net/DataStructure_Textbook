#include <stdio.h>
#include <stdlib.h>

#include "708p_graphlinkedlist.h"
#include "707p_linkedgraph.h"
#include "708p_graphsp.h"

// Dijkstra 알고리즘
int* shortestPathDijkstra(LinkedGraph* pGraph, int startVertexId) {
    int* pReturn = NULL;
    int* pSelected = NULL;
    int nodeCount = 0;
    int maxNodeCount = 0;
    int i = 0;
    int j = 0;
    int weight = 0;
    int vertexId = 0;
    int y_w = 0;
    int y_v = 0;
    ListNode* pListNode = NULL;
    LinkedList* pEdgeList = NULL;

    if (pGraph == NULL) {
        printf("Graph is NULL\n");
        return FALSE;
    }
    maxNodeCount = getMaxVertexCountLinkedGraph(pGraph);
    nodeCount = getVertexCountLinkedGraph(pGraph);

    pReturn = (int*)malloc(sizeof(int) * maxNodeCount);
    pSelected = (int*)malloc(sizeof(int) * maxNodeCount);
    if (pReturn == NULL || pSelected == NULL) {
        printf("오류, 메모리할당, shortestPathDijkstra()\n");
        if (pReturn != NULL) {
            free(pReturn);
        }
        if (pSelected != NULL) {
            free(pSelected);
        }
    }

    // step 0. 초기화
    for (i = 0 ; i < maxNodeCount ; i++) {
        if (i == startVertexId) {
            pReturn[ i ] = 0;
        } else {
            if (pGraph->pVertex[ i ] == USED) {
                pSelected[ i ] = TRUE;
                pReturn[ i ] = getEdgeWeight(pGraph, startVertexId, i);
            } else {
                pSelected[ i ] = FALSE;
                pReturn[ i ] = MAX_INT;
            }
        }
    }

    for (i = 0 ; i < maxNodeCount ; i++) {
        printf("(%d, %d)->%d\n", startVertexId, i, pReturn[i]);
    }

    for (i = 0 ; i < nodeCount - 1 ; i++) {
        printf("[%d]-Iteration\n", i+1);

        // step-1.
        // 집합 S 중 최단거리를 가지는 정점(vertexId)을 선택
        vertexId = getMinDistance(pReturn, pSelected, maxNodeCount);
        pSelected[ vertexId ] = FALSE;

        // 선택된 정점(vertexId)에 인접한 정점들에 대해 거리 변경 조건 점검.
        pEdgeList = pGraph->ppAdjEdge[ vertexId ];
        pListNode = pEdgeList->headerNode.pLink;
        while (pListNode != NULL) {
            int toVertexId = pListNode->data.vertexId;
            int weight = pListNode->data.weight;

            // y_v + c_v, w 와 y_w 비교
            y_v = pReturn[ vertexId ];
            y_w = pReturn[ toVertexId ];    // 기존 최단거리
            if (y_v + weight < y_w) {       // 기존 최단거리와 새 최단거리y_v + weight 비교
                pReturn[ toVertexId ] = y_v + weight;
            }
            pListNode = pListNode->pLink;
        }
        for (j = 0 ; j < maxNodeCount ; j++) {
            printf("\t(%d,%d)->%d\n", startVertexId, j, pReturn[ j ]);
        }
    }
    free(pSelected);
    return pReturn;
}

int getMinDistance(int* distance, int* pSelected, int maxNodeCount) {
    int pReturn = 0;
    int min_distance = MAX_INT;
    int i = 0;

    for (i = 0 ; i < maxNodeCount ; i++) {
        if (pSelected[ i ] == TRUE && distance[ i ] < min_distance) {
            min_distance = distance[ i ];
            pReturn = i;
        }
    }
    return pReturn;
}

int getEdgeWeight(LinkedGraph* pGraph, int fromVertexId, int toVertexId) {
    int pReturn = MAX_INT;
    int position = 0;
    LinkedList* pEdgeList = NULL;
    ListNode* pListNode = NULL;

    if (pGraph != NULL) {
        pEdgeList = pGraph->ppAdjEdge[ fromVertexId ];
        if (pEdgeList != NULL) {
            position = findGraphNodePosition(pEdgeList, toVertexId);
            if (position >= 0) {
                pListNode = getLinkedListElement(pEdgeList, position);
                if (pListNode != NULL) {
                    pReturn = pListNode->data.weight;
                }
            }
        }
    }
    return pReturn;
}

// Floyd 알고리즘
int** shortestPathFloyd(LinkedGraph* pGraph) {
    int** ppReturn = NULL;
    int r = 0;
    int s = 0;
    int v = 0;
    int weight = 0;
    int maxNodeCount = 0;

    if (pGraph == NULL) {
        printf("Graph is NULL\n");
        return NULL;
    }
    maxNodeCount = getMaxVertexCountLinkedGraph(pGraph);
    printf("노드 개수 : %d\n", maxNodeCount);

    ppReturn = (int**) malloc(sizeof(int*) * maxNodeCount);
    if (ppReturn == NULL) {
        printf("오류, 메모리할당1, shortestPathFloyd()\n");
        return NULL;
    }

    for (r = 0 ; r < maxNodeCount ; r++) {
        ppReturn[ r ] = (int*)malloc(sizeof(int) * maxNodeCount);
        if (ppReturn[ r ] == NULL) {
            for (s = 0 ; s < r - 1 ; s++) {
                if (ppReturn[ s ] != NULL) {
                    free(ppReturn[ s ]);
                }
            }
            if (ppReturn != NULL) {
                free(ppReturn);
            }
            printf("오류, 메모리할당2, shortestPathFloyd()\n");
            return NULL;
        }
    }

    // 초기화. 배열 ppReturn 의 초기화
    for (r = 0 ; r < maxNodeCount ; r++) {
        for (s = 0 ; s < maxNodeCount ; s++) {
            if (r == s) {
                ppReturn[ r ][ s ] = 0;
            } else {
                ppReturn[ r ][ s ] = getEdgeWeight(pGraph, r, s);
            }
        }
    }
    printMatrix(ppReturn, maxNodeCount);

    // step1. 삼중 loop
    for (v = 0 ; v < maxNodeCount ; v++) {
        for (r = 0 ; r < maxNodeCount ; r++) {
            for (s = 0 ; s < maxNodeCount ; s++) {
                if (ppReturn[ r ][ v ] + ppReturn[ v ][ s ] < ppReturn[ r ][ s ]) {
                    ppReturn[ r ][ s ] = ppReturn[ r ][ v ] + ppReturn[ v ][ s ];
                }
            }
        }
        printf("[%d]-루프\n", v + 1);
        printMatrix(ppReturn, maxNodeCount);
    }
    return ppReturn;
}

void printMatrix(int** matrix, int maxNodeCount) {
    if (matrix == NULL) {
        printf("empty matrix, printMatrix() \n");
        return;
    }
    if (maxNodeCount == 0) {
        printf("maxNodeCount is 0, printMatrix()\n");
        return;
    }

    int r = 0;
    int s = 0;
    for (s = 0 ; s < maxNodeCount ; s++) {
        printf("\t%d", s);
    }
    printf("\n");
    for (r = 0 ; r < maxNodeCount ; r++) {
        printf("%d\t", r);
        for (s = 0 ; s < maxNodeCount ; s++) {
            printf("%d\t", matrix[ r ][ s ]);
        }
        printf("\n");
    }
}
