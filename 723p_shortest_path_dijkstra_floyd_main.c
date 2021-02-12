#include <stdio.h>
#include <stdlib.h>

#include "708p_graphlinkedlist.h"
#include "707p_linkedgraph.h"
#include "708p_graphsp.h"

int main(int argc, char** argv) {
    int i = 0;
    LinkedGraph* pG = NULL;
    int* pResult = NULL;
    int** ppMatrix = NULL;

    // 그래프 생성
    pG = createLinkedGraph(6);
    if (pG != NULL) {
        // 그래프 초기화, 노드 추가
        for (i = 0 ; i < 6 ; i++) {
            addVertexLinkedGraph(pG, i);
        }

        // 그래프 초기화 : 간선 추가
        addEdgeWithWeightLinkedGraph(pG, 0, 1, 1);
        addEdgeWithWeightLinkedGraph(pG, 0, 2, 4);
        addEdgeWithWeightLinkedGraph(pG, 1, 2, 2);
        addEdgeWithWeightLinkedGraph(pG, 2, 3, 1);
        addEdgeWithWeightLinkedGraph(pG, 3, 4, 8);
        addEdgeWithWeightLinkedGraph(pG, 3, 5, 3);
        addEdgeWithWeightLinkedGraph(pG, 4, 5, 4);

        printf("G1:\n");
        displayLinkedGraph(pG);

        printf("\nDijkstra:\n");
        pResult = shortestPathDijkstra(pG, 0);

        printf("\nFloyd:\n");
        ppMatrix = shortestPathFloyd(pG);

        // 그래프 삭제
        if (pResult != NULL) {
            free(pResult);
        }
        if (ppMatrix != NULL) {
            int r = 0;
            int maxNodeCount = getMaxVertexCountLinkedGraph(pG);
            for (r = 0 ; r < maxNodeCount ; r++) {
                if (ppMatrix[ r ] != NULL) {
                    free(ppMatrix[ r ]);
                }
            }
            free(ppMatrix);
        }
        deleteLinkedGraph(pG);
    }
}
