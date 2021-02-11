#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "237p_arraystack.h"

ArrayStack* createArrayStack(int size) {
    if (size <= 0) {
        printf("Error, size must greater than zero.\n");
        return NULL;
    }

    ArrayStack* pReturn = (ArrayStack*) malloc(sizeof(ArrayStack));
    if (pReturn == NULL) {
        printf("Error, malloc()#1, createArrayStack()\n");
        return NULL;
    }
    memset(pReturn, 0, sizeof(ArrayStack));
    pReturn->pElement = (ArrayStackNode*)malloc(sizeof(ArrayStackNode)
            * size);
    if (pReturn->pElement == NULL) {
        printf("Error, malloc()#2, createArrayStack()\n");
        free(pReturn);
        return NULL;
    }
    pReturn->maxElementCount = size;
    return pReturn;
}

int pushArrayStack(ArrayStack* pStack, ArrayStackNode element) {
    if (pStack == NULL) {
        printf("Error, ArrayStack is null, pushArrayStack()\n");
        return FAILED;
    }

    if (isArrayStackFull(pStack) == TRUE) {
        printf("Error, stack is full, pushArrayStack()\n");
        return FAILED;
    }
    pStack->pElement[pStack->currentElementCount] = element;
    pStack->currentElementCount++;

    return SUCCEEDED;
}

ArrayStackNode* popArrayStack(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("Error, ArrayStack is null, popArrayStack()\n");
        return NULL;
    }
    if (isArrayStackEmpty(pStack) == TRUE) {
        printf("Error, ArrayStack is empty, popArrayStack()\n");
        return NULL;
    }

    ArrayStackNode* pReturn = (ArrayStackNode*)malloc(sizeof(ArrayStackNode));
    if (pReturn == NULL) {
        printf("Error, malloc(), popArrayStack()\n");
        return NULL;
    }

    *pReturn = pStack->pElement[pStack->currentElementCount - 1];
    pStack->currentElementCount--;

    return pReturn;
}

ArrayStackNode* peekArrayStack(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("Error, ArrayStack is null, peekArrayStack()\n");
        return NULL;
    }

    if (isArrayStackEmpty(pStack) == TRUE) {
        printf("Error, ArrayStack is empty, peekArrayStack()\n");
        return NULL;
    }

    return &(pStack->pElement[ pStack->currentElementCount - 1 ]);
}

void deleteArrayStack(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("Error, ArrayStack is null, deleteArrayStack()\n");
        return;
    }

    if (pStack->pElement != NULL) {
        free(pStack->pElement);
    }
    free(pStack);
}

int isArrayStackFull(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("Error, ArrayStack is null, isArrayStackFull()\n");
        return FAILED;
    }
    if (pStack->currentElementCount == pStack->maxElementCount) {
        return TRUE;
    }
    return FALSE;
}

int isArrayStackEmpty(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("Error, ArrayStack is null, isArrayStackEmpty()\n");
        return FAILED;
    }
    if (pStack->currentElementCount == 0) {
        return TRUE;
    }
    return FALSE;
}


