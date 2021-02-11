#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "392p_linkedDeq.h"

LinkedDeq* createLinkedDeq() {
    LinkedDeq* pReturn = NULL;
    pReturn = (LinkedDeq*)malloc(sizeof(LinkedDeq));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(LinkedDeq));
    } else {
        printf("오류, 메모리 할당, createLinkedDeq()\n");
        return NULL;
    }
    return pReturn;
}

int insertFrontLinkedDeq(LinkedDeq* pDeq, DeqNode element) {
    int ret = FALSE;
    DeqNode* pNode = NULL;

    if (pDeq != NULL) {
        pNode = (DeqNode*)malloc(sizeof(DeqNode));
        if (pNode != NULL) {
            *pNode = element;
            pNode->pRearLink = NULL;
            pNode->pFrontLink = NULL;

            if (isLinkedDeqEmpty(pDeq) == TRUE) {
                // 공백 상태의 덱인 경우
                pDeq->pFrontNode = pNode;
                pDeq->pRearNode = pNode;
            } else {
                // 공백 상태가 아닌 덱의 경우
                pDeq->pFrontNode->pFrontLink = pNode;
                pNode->pRearLink = pDeq->pFrontNode;
                pDeq->pFrontNode = pNode;
            }
            pDeq->currentElementCount++;
            ret = TRUE;
        } else {
            printf("오류, 메모리 할당, insertFrontLinkedDeq()\n");
        }
    }
    return ret;
}

int insertRearLinkedDeq(LinkedDeq* pDeq, DeqNode element) {
    int ret = FALSE;
    DeqNode* pNode = NULL;

    if (pDeq != NULL) {
        pNode = (DeqNode*)malloc(sizeof(DeqNode));
        if (pNode != NULL) {
            *pNode = element;
            pNode->pRearLink = NULL;
            pNode->pFrontLink = NULL;
            if (isLinkedDeqEmpty(pDeq) == TRUE) {
                pDeq->pFrontNode = pNode;
                pDeq->pRearNode = pNode;
            } else {
                pDeq->pRearNode->pRearLink = pNode;
                pNode->pFrontLink = pDeq->pRearNode;
                pDeq->pRearNode = pNode;
            }
            pDeq->currentElementCount++;
            ret = TRUE;
        } else {
            printf("오류, 메모리할당, insertRearLinkedDeq()\n");
        }
    }
    return ret;
}

DeqNode* deleteFrontLinkedDeq(LinkedDeq* pDeq) {
    DeqNode* pReturn = NULL;
    if (pDeq != NULL) {
        if (isLinkedDeqEmpty(pDeq) == FALSE) {
            pReturn = pDeq->pFrontNode;
            pDeq->pFrontNode = pDeq->pFrontNode->pRearLink;
            pReturn->pRearLink = NULL;

            pDeq->currentElementCount--;
            if (isLinkedDeqEmpty(pDeq) == TRUE) {
                pDeq->pRearNode = NULL;
            } else {
                pDeq->pFrontNode->pFrontLink = NULL;
            }
        }
    }
    return pReturn;
}

DeqNode* peekFrontLinkedDeq(LinkedDeq* pDeq) {
    DeqNode* pReturn = NULL;
    if (pDeq != NULL) {
        if (isLinkedDeqEmpty(pDeq) == FALSE) {
            pReturn = pDeq->pFrontNode;
        }
    }
    return pReturn;
}

DeqNode* deleteRearLinkedDeq(LinkedDeq* pDeq) {
    DeqNode* pReturn = NULL;
    if (pDeq != NULL) {
        if (isLinkedDeqEmpty(pDeq) == FALSE) {
            pReturn = pDeq->pRearNode;
            pDeq->pRearNode = pDeq->pRearNode->pFrontLink;
            pReturn->pFrontLink = NULL;
            pDeq->currentElementCount--;
            if (isLinkedDeqEmpty(pDeq) == TRUE) {
                pDeq->pFrontNode = NULL;
            } else {
                pDeq->pRearNode->pRearLink = NULL;
            }
        }
    }
    return pReturn;
}

void deleteLinkedDeq(LinkedDeq* pDeq) {
    DeqNode* pNode = NULL;
    DeqNode* pDelNode = NULL;
    if (pDeq != NULL) {
        pNode = pDeq->pFrontNode;
        while (pNode != NULL) {
            pDelNode = pNode;
            pNode = pNode->pRearLink;
            free(pDelNode);
        }
        free(pDeq);
    }
}

int isLinkedDeqFull(LinkedDeq* pDeq) {
    return FALSE;
}

int isLinkedDeqEmpty(LinkedDeq* pDeq) {
    int ret = FALSE;
    if (pDeq != NULL) {
        if (pDeq->currentElementCount == 0) {
            ret = TRUE;
        }
    }
    return ret;
}
