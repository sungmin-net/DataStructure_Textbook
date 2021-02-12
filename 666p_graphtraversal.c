#include <stdio.h>
#include <stdlib.h>
#include "665p_graphlinkedlist.h"
#include "665p_linkedgraph.h"
#include "665p_linkedqueue.h"
#include "665p_graphtraversal.h"

int enqueueLinkedQueueForBreadthFirstSearch(LinkedQueue* pQueue, int nodeId) {
    QueueNode node = {0,};
    node.data = nodeId;
    return enqueueLinkedQueue(pQueue, node);
}

void traversalBreadthFirstSearch(LinkedGraph* pGraph, int startVertexId) {
    int i = 0;
    int vertexId = 0;
    QueueNode* pTop = NULL;
    LinkedQueue* pQueue = NULL;
    QueueNode* pQueueNode = NULL;
    ListNode* pListNode =NULL;
    int* pVisited = NULL;

    if (pGraph == NULL) {
        return;
    }

    pQueue = createLinkedQueue();
    if (pQueue == NULL) {
        return;
    }

    pVisited = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
    if (pVisited == NULL) {
        printf("Error, malloc(), traversalBreadthFirstSearch()\n");
        return;
    }

    // 방문 여부 초기화
    for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
        pVisited[ i ] = FALSE;
    }
    pVisited[ startVertexId ] = TRUE;
    enqueueLinkedQueueForBreadthFirstSearch(pQueue, startVertexId);

    while (isLinkedQueueEmpty(pQueue) == FALSE) {
        pQueueNode = dequeueLinkedQueue(pQueue); // 큐에서 새 탐색 노드를 디큐
        if (pQueueNode != NULL) {
            vertexId = pQueueNode->data;
            printf("[%d]-visited\n", vertexId);

            pListNode = pGraph->ppAdjEdge[ vertexId ]->headerNode.pLink;
            while (pListNode != NULL) {
                int vertexId = pListNode->data.vertexId;
                if (pVisited[ vertexId ] == FALSE) {
                    pVisited[ vertexId ] = TRUE;
                    enqueueLinkedQueueForBreadthFirstSearch(pQueue, vertexId);
                }
                pListNode = pListNode->pLink;
            }
        }
    }
    free(pVisited);
    deleteLinkedQueue(pQueue);
}



