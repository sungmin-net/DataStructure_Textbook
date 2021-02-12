#include <stdio.h>
#include <stdlib.h>
#include "689p_graphlinkedlist.h"
#include "689p_linkedstack.h"
#include "689p_linkedgraph.h"
#include "690p_graphmst.h"

// Prime 알고리즘
LinkedGraph* mstPrim(LinkedGraph* pGraph, int startVertexId) {

    if (pGraph == NULL) {
        printf("Graph is NULL\n");
        return NULL;
    }

    LinkedGraph* pReturn = NULL;
    int i = 0;
    int nodeCount = 0;
    int mstNodeCount = 0;
    int maxNodeCount = 0;
    int fromVertexId = 0;
    GraphEdge minWeightEdge = {0,};


    nodeCount = getVertexCountLinkedGraph(pGraph);
    maxNodeCount = getMaxVertexCountLinkedGraph(pGraph);

    pReturn = createLinkedGraph(maxNodeCount);
    if (pReturn == NULL) {
        return NULL;
    }

    addVertexLinkedGraph(pReturn, startVertexId);

    while ((mstNodeCount = getVertexCountLinkedGraph(pReturn)) < nodeCount) {
        minWeightEdge.vertexIdFrom = 0;
        minWeightEdge.vertexIdTo = 0;
        minWeightEdge.weight = MAX_INT;

        for (i = 0 ; i < maxNodeCount ; i++) {
            if (pReturn->pVertex[ i ] == USED) {
                fromVertexId = i;
                getMinWeightEdge(pGraph, pReturn, fromVertexId, &minWeightEdge);
            }
        }
        printf("[%d], 최소 가중치 : (%d, %d)->%d\n",
                mstNodeCount, minWeightEdge.vertexIdFrom,
                minWeightEdge.vertexIdTo, minWeightEdge.weight);
        addVertexLinkedGraph(pReturn, minWeightEdge.vertexIdTo);
        addEdgeWithWeightLinkedGraph(pReturn, minWeightEdge.vertexIdFrom,
                minWeightEdge.vertexIdTo, minWeightEdge.weight);
    }
    return pReturn;
}

int checkEdge(LinkedGraph* pGraph, int fromVertexId, int toVertexId) {
    int ret = FALSE;
    LinkedList* pEdgeList = NULL;
    int position = 0;

    if (pGraph != NULL) {
        pEdgeList = pGraph->ppAdjEdge[ fromVertexId ];
        position = findGraphNodePosition(pEdgeList, toVertexId);
        if (position >= 0) {
            ret = TRUE;
        }
    }
    return ret;
}

// 정점과 부속된 모든 간선들 중,
// 가중치가 가장 작으면서 순환을 발생시키지 않는 간선을 선택
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST,
        int fromVertexId, GraphEdge* pMinWeightEdge) {
    ListNode* pListNode = NULL;
    int isCycle = 0;
    int isAlready = 0;
    LinkedList* pEdgeList = pGraph->ppAdjEdge[ fromVertexId ];

    // pListNode : V(T)에 부속된 간선들 중 하나를 선택
    pListNode = pEdgeList->headerNode.pLink;
    while (pListNode != NULL) {
        int vertexId = pListNode->data.vertexId;
        int weight = pListNode->data.weight;

        // 최소값인지 점검.
        if (pListNode->data.weight < pMinWeightEdge->weight) {
            // 기존의 E(T) 에 속한 간선인지 점검
            isAlready = checkEdge(pMST, fromVertexId, vertexId);
            if (isAlready == FALSE) {
                isCycle = checkCycle(pMST, fromVertexId, vertexId);
            }
            // 기존에 이미 E(T)에 속한 간선이 아니면서,
            // 순환을 발생시키지 않는 최소 가중치 간선을 선택
            if (isAlready == FALSE && isCycle == FALSE) {
                pMinWeightEdge->vertexIdFrom = fromVertexId;
                pMinWeightEdge->vertexIdTo = vertexId;
                pMinWeightEdge->weight = weight;
            }
        }
        pListNode = pListNode->pLink;
    }
}

int pushLinkedStackForDepthFirstSearch(LinkedStack* pStack, int nodeId) {
    StackNode node = {0,};
    node.data = nodeId;
    return pushLinkedStack(pStack, node);
}

// 간선 추가로 인해 순환이 발생하는 지 검사
// 기존에 경로가 있다면, 순환이 발생한다.
// 기존의 깊이우선탐색(DFS)를 사용
int checkCycle(LinkedGraph* pGraph, int fromVertexId, int toVertexId) {

    if (pGraph == NULL) {
        return FALSE;
    }

    int pReturn = FALSE;
    int i = 0;
    int vertexId = 0;
    LinkedStack* pStack = NULL;
    StackNode* pStackNode = NULL;
    ListNode* pListNode = NULL;
    int* pVisited = NULL;

    pStack = createLinkedStack();
    if (pStack == NULL) {
        return FALSE;
    }

    pVisited = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
    if (pVisited == NULL) {
        printf("Error, malloc, checkCycle()\n");
        deleteLinkedStack(pStack);
        return FALSE;
    }

    // 초기화
    for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
        pVisited[ i ] = FALSE;
    }

    pVisited[ fromVertexId ] = TRUE;
    pushLinkedStackForDepthFirstSearch(pStack, fromVertexId);

    while (isLinkedStackEmpty(pStack) == FALSE) {
        pStackNode = popLinkedStack(pStack);
        if (pStackNode != NULL) {
            vertexId = pStackNode->data;
            if (vertexId == toVertexId) {
                printf("(%d, %d)-기존 경로가 존재합니다.\n", fromVertexId,
                        toVertexId);
                pReturn = TRUE;
                break;
            }
            pListNode = pGraph->ppAdjEdge[ vertexId ]->headerNode.pLink;
            while (pListNode != NULL) {
                int vertexId = pListNode->data.vertexId;
                if (pVisited[ vertexId ] == FALSE) {
                    pVisited[ vertexId ] = TRUE;
                    pushLinkedStackForDepthFirstSearch(pStack, vertexId);
                }
                pListNode = pListNode->pLink;
            }
        }
    }
    free(pVisited);
    deleteLinkedStack(pStack);
    return pReturn;
}



