#ifndef _LINKED_DEQ_
#define _LINKED_DEQ_

typedef struct DeqNodeType {
    char data;
    struct DeqNodeType* pFrontLink;
    struct DeqNodeType* pRearLink;
} DeqNode;

typedef struct linkedDeqtype {
    int currentElementCount;
    DeqNode* pFrontNode;
    DeqNode* pRearNode;
} LinkedDeq;

LinkedDeq* createLinkedDeq();
int insertFrontLinkedDeq(LinkedDeq* pDeq, DeqNode element);
int insertRearLinkedDeq(LinkedDeq* pDeq, DeqNode element);
DeqNode* deleteFrontLinkedDeq(LinkedDeq* pDeq);
DeqNode* deleteRearLinkedDeq(LinkedDeq* pDeq);
DeqNode* peekFrontLinkedDeq(LinkedDeq* pDeq);
DeqNode* peekRearLinkedDeq(LinkedDeq* pDeq);
void deleteLinkedDeq(LinkedDeq* pDeq);
int isLinkedDeqFull(LinkedDeq* pDeq);
int isLinkedDeqEmpty(LinkedDeq* pDeq);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE    1
#define FALSE   0

#endif

