#include <stdio.h>
#include <stdlib.h>

#include "632p_graphlinkedlist.h"
#include "633p_linkedgraph.h"

int main(int argc, char* arg[]) {
    int i = 0;
    LinkedGraph* pG1 = NULL;
    LinkedGraph* pG2 = NULL;
    LinkedGraph* pG3 = NULL;

    // 그래프 생성
    pG1 = createLinkedGraph(6);
    pG2 = createLinkedDirectedGraph(6);
    pG3 = createLinkedDirectedGraph(6);
    if (pG1 != NULL && pG2 != NULL && pG3 != NULL) {
        // 그래프 초기화 : 정점 추가
        for (i = 0 ; i < 6 ; i++) {
            addVertexLinkedGraph(pG1, i);
            addVertexLinkedGraph(pG2, i);
            addVertexLinkedGraph(pG3, i);
        }

        // 그래프 초기화 : 간선 추가
        addEdgeLinkedGraph(pG1, 0, 1);
        addEdgeLinkedGraph(pG1, 0, 2);
        addEdgeLinkedGraph(pG1, 1, 2);
        addEdgeLinkedGraph(pG1, 2, 3);
        addEdgeLinkedGraph(pG1, 3, 4);
        addEdgeLinkedGraph(pG1, 3, 5);
        addEdgeLinkedGraph(pG1, 4, 5);

        addEdgeLinkedGraph(pG2, 0, 1);
        addEdgeLinkedGraph(pG2, 1, 2);
        addEdgeLinkedGraph(pG2, 2, 0);
        addEdgeLinkedGraph(pG2, 2, 2);
        addEdgeLinkedGraph(pG2, 2, 3);
        addEdgeLinkedGraph(pG2, 3, 2);
        addEdgeLinkedGraph(pG2, 3, 4);
        addEdgeLinkedGraph(pG2, 4, 5);
        addEdgeLinkedGraph(pG2, 5, 3);

        addEdgeWithWeightLinkedGraph(pG3, 0, 1, 4);
        addEdgeWithWeightLinkedGraph(pG3, 1, 2, 1);
        addEdgeWithWeightLinkedGraph(pG3, 2, 0, 2);
        addEdgeWithWeightLinkedGraph(pG3, 2, 1, 3);
        addEdgeWithWeightLinkedGraph(pG3, 2, 3, 2);
        addEdgeWithWeightLinkedGraph(pG3, 3, 2, 1);
        addEdgeWithWeightLinkedGraph(pG3, 3, 4, 1);
        addEdgeWithWeightLinkedGraph(pG3, 4, 5, 1);
        addEdgeWithWeightLinkedGraph(pG3, 5, 3, 2);

        // 그래프 정보 출력
        printf("G1 : 무방향 그래프\n");
        displayLinkedGraph(pG1);
        printf("G2 : 방향 그래프\n");
        displayLinkedGraph(pG2);
        printf("G3 : 방향 가중치 그래프\n");
        displayLinkedGraph(pG3);

        // �׷��� ����
        deleteLinkedGraph(pG1);
        deleteLinkedGraph(pG2);
        deleteLinkedGraph(pG3);
    }
    return 0;
}
