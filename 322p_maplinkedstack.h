#ifndef _LINKED_STACK_
#define _LINKED_STACK_
#include "318p_mapdef.h"

typedef struct StackNodeType {
    MapPosition data;
    struct StackNodeType* pLink;
} StackNode;

typedef struct LinkedStackType {
    int currentElementCount ;   // 현재 원소의 개수
    StackNode* pTopElement;     // Top 노드의 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLinkedStack(LinkedStack* pStack, StackNode element);
StackNode* popLinkedStack(LinkedStack* pStack);
StackNode* peekLinkedStack(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
int isLinkedStackFull(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE    1
#define FALSE   0

#endif
