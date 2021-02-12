#include <stdio.h>
#include <stdlib.h>

#include "392p_linkedDeq.h"

int insertFrontLinkedDeqChar(LinkedDeq* pDeq, char data) {
    DeqNode node = {0,};
    node.data = data;
    return insertFrontLinkedDeq(pDeq, node);
}

int insertRearLinkedDeqChar(LinkedDeq* pDeq, char data) {
    DeqNode node = {0,};
    node.data = data;
    return insertRearLinkedDeq(pDeq, node);
}

void displayLinkedDeq(LinkedDeq* pDeq) {
    DeqNode* pNode = NULL;
    int i = 0;

    if (pDeq != NULL) {
        printf("현재 노드 개수 : %d\n", pDeq->currentElementCount);
        pNode = pDeq->pFrontNode;
        while (pNode != NULL) {
            printf("[%d]-[%c]\n", i, pNode->data);
            i++;
            pNode = pNode->pRearLink;
        }
    }
}

int main(int argc, char* argv[]) {
    LinkedDeq* pDeq = NULL;
    DeqNode* pNode = NULL;

    pDeq = createLinkedDeq();
    if (pDeq != NULL) {
        insertFrontLinkedDeqChar(pDeq, 'A');
        insertFrontLinkedDeqChar(pDeq, 'B');
        insertFrontLinkedDeqChar(pDeq, 'C');
        insertFrontLinkedDeqChar(pDeq, 'D');
        insertFrontLinkedDeqChar(pDeq, 'E');
        displayLinkedDeq(pDeq);

        insertRearLinkedDeqChar(pDeq, 'X');
        insertRearLinkedDeqChar(pDeq, 'Y');
        insertRearLinkedDeqChar(pDeq, 'Z');
        displayLinkedDeq(pDeq);

        pNode = deleteRearLinkedDeq(pDeq);
        if (pNode != NULL) {
            printf("deleteRearLinkedDeq Value-[%c]\n", pNode->data);
            free(pNode);
        }
        displayLinkedDeq(pDeq);

        pNode = deleteFrontLinkedDeq(pDeq);
        if (pNode != NULL) {
            printf("deleteFrontLinkedDeq Value-[%c]\n", pNode->data);
        }
        displayLinkedDeq(pDeq);

        deleteLinkedDeq(pDeq);
    }
    return 0;
}
