#ifndef _ARRAY_STACK_
#define _ARRAY_STACK_

typedef struct ArrayStackNodeType {
    char data;
} ArrayStackNode;

typedef struct ArrayStackType {
    int maxElementCount;        // 최대 원소 개수
    int currentElementCount;    // 현재 원소의 개수
    ArrayStackNode* pElement;   // 노드 저장을 위한 1차원 array
} ArrayStack;

ArrayStack* createArrayStack(int maxElementCount);
int pushArrayStack(ArrayStack* pStack, ArrayStackNode element);
ArrayStackNode* popArrayStack(ArrayStack* pStack);
ArrayStackNode* peekArrayStack(ArrayStack* pStack);
void deleteArrayStack(ArrayStack* pStack);
int isArrayStackFull(ArrayStack* pStack);
int isArrayStackEmpty(ArrayStack* pStack);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_
#define TRUE        0
#define FALSE       1
#define FAILED      (-1)
#define SUCCEEDED   1
#endif
