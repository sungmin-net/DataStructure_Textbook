#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "632p_graphlinkedlist.h"
#include "633p_linkedgraph.h"

LinkedGraph* createLinkedGraph(int maxVertexCount) {
    int i = 0;
    LinkedGraph* pReturn = NULL;

    if (maxVertexCount > 0) {
        pReturn = (LinkedGraph*)malloc(sizeof(LinkedGraph));
        if (pReturn == NULL) {
            printf("오류, 메모리할당1, createLinkedGraph()\n");
            return NULL;
        }
        pReturn->graphType = GRAPH_UNDIRECTED;
        pReturn->maxVertexCount = maxVertexCount;
        pReturn->currentEdgeCount = 0;
        pReturn->currentVertexCount = 0;
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
    memset(pReturn->pVertex, NOT_USED, sizeof(int) * maxVertexCount);

    pReturn->ppAdjEdge = (LinkedList**)malloc(
            sizeof(LinkedList*) * maxVertexCount);
    if (pReturn->ppAdjEdge == NULL) {
        printf("오류, 메모리할당3, createLinkedGraph()\n");
        if (pReturn->pVertex != NULL) {
            free(pReturn->pVertex);
        }
        if (pReturn != NULL) {
            free(pReturn);
        }
        return NULL;
    }
    for (i = 0 ; i < maxVertexCount ; i++) {
        pReturn->ppAdjEdge[ i ] = createLinkedList();
        if (pReturn->ppAdjEdge[i] == NULL) {
            printf("오류, 메모리할당4, createLinkedGraph()\n");
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
    return pReturn;
}

LinkedGraph* createLinkedDirectedGraph(int maxVertexCount) {
    LinkedGraph* pReturn = NULL;
    pReturn = createLinkedGraph(maxVertexCount);
    if (pReturn != NULL) {
        pReturn->graphType = GRAPH_DIRECTED;
    }
    return pReturn;
}

int addVertexLinkedGraph(LinkedGraph* pGraph, int vertexId) {
    int ret = SUCCESS;

    if (pGraph != NULL) {
        if (vertexId < pGraph->maxVertexCount) {
            if (pGraph->pVertex[ vertexId ] == NOT_USED) {
                pGraph->pVertex[ vertexId ] = USED;
                pGraph->currentVertexCount++;
            } else {
                printf("오류, 노드추가1-[%d], addVertexLinkedGraph()\n",
                        vertexId);
                ret = FAIL;
            }
        } else {
            printf("오류, 노드추가2-[%d], addVertexLinkedGraph()\n",
                    vertexId);
            ret = FAIL;
        }
    }
    return ret;
}

int addEdgeLinkedGraph(LinkedGraph* pGraph, int fromVertexId, int toVertexId) {
    return addEdgeWithWeightLinkedGraph(pGraph, fromVertexId, toVertexId, USED);
}

int addLinkedListElementForVertex(LinkedList* pList, int position,
        GraphVertex vertex) {
    ListNode node = {0,};
    node.data = vertex;
    return addLinkedListElement(pList, position, node);
}

int addEdgeWithWeightLinkedGraph(LinkedGraph* pGraph, int fromVertexId,
        int toVertexId, int weight) {
    GraphVertex toNode = {0,};

    if (pGraph != NULL) {
        if (checkVertexValid(pGraph, fromVertexId) != SUCCESS) {
            return FAIL;
        }
        if (checkVertexValid(pGraph, toVertexId) != SUCCESS) {
            return FAIL;
        }

        toNode.vertexId = toVertexId;
        toNode.weight = weight;
        addLinkedListElementForVertex(
                pGraph->ppAdjEdge[ fromVertexId ],0, toNode);
        pGraph->currentEdgeCount++;

        if (pGraph->graphType == GRAPH_UNDIRECTED) {
            GraphVertex fromNode;
            fromNode.vertexId = fromVertexId;
            fromNode.weight = weight;
            addLinkedListElementForVertex(
                    pGraph->ppAdjEdge[ toVertexId ], 0, fromNode);
            pGraph->currentEdgeCount++;
        }
    }
    return SUCCESS;
}

int checkVertexValid(LinkedGraph* pGraph, int vertexId) {
    if (vertexId >= pGraph->maxVertexCount
            || pGraph->pVertex[ vertexId ] == NOT_USED) {
        printf("오류, 노드 ID[%d]\n", vertexId);
        return FAIL;
    }
    return SUCCESS;
}

int removeVertexLinkedGraph(LinkedGraph* pGraph, int vertexId) {
    int ret = SUCCESS;
    int i = 0;

    if (pGraph != NULL) {
        if (checkVertexValid(pGraph, vertexId) != SUCCESS) {
            return FAIL;
        }
        for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
            removeEdgeLinkedGraph(pGraph, vertexId, i);
            removeEdgeLinkedGraph(pGraph, i, vertexId);
        }
        pGraph->pVertex[ vertexId ] = NOT_USED;
    }
    return ret;
}

int removeEdgeLinkedGraph(LinkedGraph* pGraph, int fromVertexId,
        int toVertexId) {
    if (pGraph != NULL) {
        if (checkVertexValid(pGraph, fromVertexId) != SUCCESS) {
            return FAIL;
        }
        if (checkVertexValid(pGraph, toVertexId) != SUCCESS) {
            return FAIL;
        }
        deleteGraphNode(pGraph->ppAdjEdge[ fromVertexId ], toVertexId);
        if (pGraph->graphType == GRAPH_UNDIRECTED) {
            deleteGraphNode(pGraph->ppAdjEdge[ toVertexId ], fromVertexId);
        }
    }
    return SUCCESS;
}


void deleteGraphNode(LinkedList* pList, int delVertexId) {

    int position = findGraphNodePosition(pList, delVertexId);
    if (position >= 0) {
        removeLinkedListElement(pList, position);
    }
}

int findGraphNodePosition(LinkedList* pList, int vertexId) {
    int position = 0;
    ListNode* pNode = NULL;

    if (pList != NULL) {
        pNode = pList->headerNode.pLink;
        while (pNode != NULL) {
            if (pNode->data.vertexId == vertexId) {
                return position;
            }
            pNode = pNode->pLink;
            position++;
        }
    }
    return -1;
}

int getEdgeCountLinkedGraph(LinkedGraph* pGraph) {
    if (pGraph != NULL) {
        return pGraph->currentEdgeCount;
    }
    return 0;
}

int getVertexCountLinkedGraph(LinkedGraph* pGraph) {
    if (pGraph != NULL) {
        return pGraph->currentVertexCount;
    }
    return 0;
}

int getMaxVertexCountLinkedGraph(LinkedGraph* pGraph) {
    if (pGraph != NULL) {
        return pGraph->maxVertexCount;
    }
    return 0;
}

int getGraphTypeLinkedGraph(LinkedGraph* pGraph) {
    if (pGraph != NULL) {
        return pGraph->graphType;
    }
    return 0;
}

void displayLinkedGraph(LinkedGraph* pGraph) {
    int i = 0;
    int j = 0;
    int position = 0;
    ListNode* pNode = NULL;
    if (pGraph != NULL) {
        for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
            for (j = 0 ; j < pGraph->maxVertexCount ; j++) {
                position = findGraphNodePosition(pGraph->ppAdjEdge[ i ], j);
                if (position >= 0) {
                    pNode = getLinkedListElement(pGraph->ppAdjEdge[ i ],
                            position);
                    printf("%d ", pNode->data.weight);
                } else {
                    printf("0 ");
                }
            }
            printf("\n");
        }
    }
}

void deleteLinkedGraph(LinkedGraph* pGraph) {
    int i = 0;
    if (pGraph != NULL) {
        for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
            deleteLinkedList(pGraph->ppAdjEdge[ i ]);
        }
        if (pGraph->ppAdjEdge != NULL) {
            free(pGraph->ppAdjEdge);
        }
        if (pGraph->pVertex != NULL) {
            free(pGraph->pVertex);
        }
        free(pGraph);
    }
}

int isEmptyLinkedGraph(LinkedGraph* pGraph) {
    if (pGraph != NULL && pGraph->currentVertexCount > 0) {
        return FALSE;
    }
    return TRUE;
}
