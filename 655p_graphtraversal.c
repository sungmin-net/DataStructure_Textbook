#include <stdio.h>
#include <stdlib.h>
#include "654p_graphlinkedlist.h"
#include "654p_linkedgraph.h"
#include "655p_graphtraversal.h"
#include "654p_linkedstack.h"

int pushLinkedStackForDepthFirstSearch(LinkedStack* pStack, int nodeId) {
    StackNode node = {0,};
    node.data = nodeId;
    return pushLinkedStack(pStack, node);
}

void traversalDepthFirstSearch(LinkedGraph* pGraph, int startVertexId) {
    int i = 0;
    int vertexId = 0;
    LinkedStack* pStack = NULL;
    StackNode* pStackNode = NULL;
    ListNode* pListNode = NULL;
    int* pVisited = NULL;

    if (pGraph == NULL) {
        return;
    }

    pStack = createLinkedStack();
    if (pStack == NULL) {
        return;
    }

    pVisited = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
    if (pVisited == NULL) {
        printf("오류, 메모리 할당, traversalDepthFirstStack()\n");
        return;
    }

    // 방문 여부 초기화
    for (i = 0 ; i < pGraph->maxVertexCount ; i++) {
        pVisited[i] = FALSE;
    }

    // 탐색 시작 노드를 방문으로 처리하고 스택에 푸시
    pVisited[ startVertexId ] = TRUE;
    pushLinkedStackForDepthFirstSearch(pStack, startVertexId);

    // 스택에 더 방문할 노드가 없을 때까지 루프
    while (isLinkedStackEmpty(pStack) == FALSE) {
        pStackNode = popLinkedStack(pStack); // 스택에서 새 탐색 노드를 팝
        if (pStackNode != NULL) {
            vertexId = pStackNode->data;
            printf("[%d] - 방문\n", vertexId);

            pListNode = pGraph->ppAdjEdge[ vertexId ]->headerNode.pLink;
            while (pListNode != NULL) {
                // 현재 탐색 노드와 연결된 모든 노드를 스택에 푸시.
                // 단, 기존에 이미 방문했는 지를 점검.
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
}

