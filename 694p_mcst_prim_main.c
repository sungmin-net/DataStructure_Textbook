#include <stdio.h>
#include <stdlib.h>
#include "689p_graphlinkedlist.h"
#include "689p_linkedgraph.h"
#include "690p_graphmst.h"

int main(int argc, char* argv[]) {
    int i = 0;
    LinkedGraph* pG1 = NULL;
    LinkedGraph* pMST1 = NULL;

    // �׷��� ����
    pG1 = createLinkedGraph(6);
    if (pG1 != NULL) {
        // �׷��� �ʱ�ȭ : ����߰�
        for (i = 0 ; i < 6 ; i++) {
            addVertexLinkedGraph(pG1, i);
        }

        // �׷����ʱ�ȭ : �����߰�
        addEdgeWithWeightLinkedGraph(pG1, 0, 1, 4);
        addEdgeWithWeightLinkedGraph(pG1, 0, 2, 3);
        addEdgeWithWeightLinkedGraph(pG1, 1, 2, 2);
        addEdgeWithWeightLinkedGraph(pG1, 2, 3, 1);
        addEdgeWithWeightLinkedGraph(pG1, 3, 4, 1);
        addEdgeWithWeightLinkedGraph(pG1, 3, 5, 5);
        addEdgeWithWeightLinkedGraph(pG1, 4, 5, 6);

        printf("G1:\n");
        displayLinkedGraph(pG1);

        // Prim �˰������� MST ����
        // ���۳�带 1�� ��
        printf("\nPrim MST:\n");
        pMST1 = mstPrim(pG1, 1);
        displayLinkedGraph(pMST1);

        // �׷��� ����
        deleteLinkedGraph(pG1);
        deleteLinkedGraph(pMST1);
    }
    return 0;
}
