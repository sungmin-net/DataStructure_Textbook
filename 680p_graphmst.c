#include <stdio.h>
#include <stdlib.h>
#include "678p_graphlinkedlist.h"
#include "678p_linkedstack.h"
#include "679p_linkedgraph.h"
#include "678p_grapharrayheap.h"
#include "680p_graphmst.h"

LinkedGraph* mstKruskal(LinkedGraph* pGraph) {

    if (pGraph == NULL) {
        printf("Graph is NULL\n");
        return NULL;
    }

    LinkedGraph* pReturn = NULL;
    int i = 0;
    int maxNodeCount = 0;
    int currentNodeCount = 0;
    int edgeCount = 0;
    int isCycle = FALSE;
    ArrayHeap* pMinHeap = NULL;
    HeapNode* pHeapNode = NULL;

    maxNodeCount = getMaxVertexCountLinkedGraph(pGraph);
    currentNodeCount = getVertexCountLinkedGraph(pGraph);
    edgeCount = getEdgeCountLinkedGraph(pGraph);

    pReturn = createLinkedGraph(maxNodeCount);
    if (pReturn == NULL) {
        return NULL;
    }
    pMinHeap = sortEdges(pGraph);
    if (pMinHeap == NULL) {
        return NULL;
    }

    for (i = 0; i < edgeCount; i++) {
        pHeapNode = extractArrayMinHeapNode(pMinHeap);

        if (pHeapNode != NULL) {
            isCycle = checkCycle(pReturn, pHeapNode->fromVertexId,
                    pHeapNode->toVertexId);
            if (isCycle == FALSE) {
                if (pReturn->pVertex[pHeapNode->fromVertexId] != USED) {
                    addVertexLinkedGraph(pReturn, pHeapNode->fromVertexId);
                }
                if (pReturn->pVertex[pHeapNode->toVertexId] != USED) {
                    addVertexLinkedGraph(pReturn, pHeapNode->toVertexId);
                }
                addEdgeWithWeightLinkedGraph(pReturn, pHeapNode->fromVertexId,
                        pHeapNode->toVertexId, pHeapNode->key);
                printf("[%d], 최소 가중치 : (%d, %d)->%d\n", i,
                        pHeapNode->fromVertexId, pHeapNode->toVertexId,
                        pHeapNode->key);
            }

            free(pHeapNode);

            if (getVertexCountLinkedGraph(pReturn) == currentNodeCount) {
                break;
            }
        }
    }
    return pReturn;
}

ArrayHeap* sortEdges(LinkedGraph* pGraph) {
    int i = 0;
    int edgeCount = 0;
    ArrayHeap* pReturn = NULL;
    ListNode* pListNode = NULL;
    LinkedList* pEdgeList = NULL;

    if (pGraph == NULL) {
        printf("Graph is NULL\n");
        return pReturn;
    }

    edgeCount = getEdgeCountLinkedGraph(pGraph);
    if (edgeCount == 0) {
        printf("오류, 간선 개수가 0개\n");
        return pReturn;
    }

    pReturn = createArrayHeap(edgeCount);
    if (pReturn == NULL) {
        return pReturn;
    }

    for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
        if (pGraph->pVertex[ i ] == USED) {
            pEdgeList = pGraph->ppAdjEdge[ i ];
            pListNode = pEdgeList->headerNode.pLink;
            while (pListNode != NULL) {
                int vertexId = pListNode->data.vertexId;
                int weight = pListNode->data.weight;

                // 무방향 그래프라면, 동일간 간선이 2개 리턴되므로,
                // 시작노드 id 가 종료노드 id 보다 작은 경우에만 리턴되도록 한다.
                // 즉, 간선 1개만 리턴되도록 한다.
                if (pGraph->graphType == GRAPH_DIRECTED ||
                        (pGraph->graphType == GRAPH_UNDIRECTED &&
                                i < vertexId)) {
                    HeapNode heapNode = {0,};
                    heapNode.fromVertexId = i;
                    heapNode.toVertexId = vertexId;
                    heapNode.key = weight;
                    insertArrayMinHeapNode(pReturn, heapNode);
                }
                pListNode = pListNode->pLink;
            }
        }
    }
    return pReturn;
}

int pushLinkedStackForDepthFirstSearch(LinkedStack* pStack, int nodeId) {
    StackNode node = {0,};
    node.data = nodeId;
    return pushLinkedStack(pStack, node);
}

int checkCycle(LinkedGraph* pGraph, int fromVertexId, int toVertexId) {
    if (pGraph == NULL) {
        return FALSE;
    }

    int pReturn = FALSE;
    int i = 0 ;
    int vertexId = 0;
    LinkedStack* pStack = NULL;
    StackNode* pStackNode = NULL;
    ListNode* pListNode = NULL;
    int* pVisited = NULL;

    pStack = createLinkedStack();
    if (pStack == NULL) {
        return pReturn;
    }

    pVisited = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
    if (pVisited == NULL) {
        printf("Error, malloc checkCycle()\n");
        deleteLinkedStack(pStack);
        return pReturn;
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
                printf("(%d,%d)-기존 경로가 존재합니다.\n", fromVertexId,
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



