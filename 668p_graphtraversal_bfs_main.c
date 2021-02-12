#include <stdio.h>
#include <stdlib.h>
#include "665p_graphlinkedlist.h"
#include "665p_linkedgraph.h"
#include "665p_graphtraversal.h"

int main(int argc, char* argv[]) {
    int i = 0;
    LinkedGraph* pG1 = NULL;

    // �׷��� ����
    pG1 = createLinkedGraph(8);
    if (pG1 != NULL) {
        // �׷��� �ʱ�ȭ, ���� �߰�
        for (i = 0 ; i < 8 ; i++) {
            addVertexLinkedGraph(pG1, i);
        }

        // �׷��� �ʱ�ȭ, ���� �߰�
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

        // BFS �׷��� Ž��
        printf("\nBFS traversal:\n");
        traversalBreadthFirstSearch(pG1, 0);

        // �׷��� ����
        deleteLinkedGraph(pG1);
    }
    return 0;
}

