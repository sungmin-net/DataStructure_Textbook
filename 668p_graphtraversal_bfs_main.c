#include <stdio.h>
#include <stdlib.h>
#include "665p_graphlinkedlist.h"
#include "665p_linkedgraph.h"
#include "665p_graphtraversal.h"

int main(int argc, char* argv[]) {
    int i = 0;
    LinkedGraph* pG1 = NULL;

    // 그래프 생성
    pG1 = createLinkedGraph(8);
    if (pG1 != NULL) {
    	// 그래프 초기화, 정점 추가
        for (i = 0 ; i < 8 ; i++) {
            addVertexLinkedGraph(pG1, i);
        }

        // 그래프 초기화, 간선 추가
        addEdgeLinkedGraph(pG1, 0, 1);
        addEdgeLinkedGraph(pG1, 0, 2);
        addEdgeLinkedGraph(pG1, 1, 3);
        addEdgeLinkedGraph(pG1, 1, 4);
        addEdgeLinkedGraph(pG1, 2, 5);
        addEdgeLinkedGraph(pG1, 2, 6);
        addEdgeLinkedGraph(pG1, 3, 7);
        addEdgeLinkedGraph(pG1, 4, 5);

        printf("G1:\n");
        displayLinkedGraph(pG1);

        // BFS 그래프 탐색
        printf("\nBFS traversal:\n");
        traversalBreadthFirstSearch(pG1, 0);

        // 그래프 삭제
        deleteLinkedGraph(pG1);
    }
    return 0;
}

