#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "254p_linkedstack.h"
#include "270p_stackutil.h"

char* reverseString(char* pSource) {

    if (pSource == NULL) {
        printf("Error, pSource is null, reverseString()\n");
        return NULL;
    }

    int size = strlen(pSource);
    if (size == 0) {
        printf("Error, pSource size is 0, reverseString()\n");
        return NULL;
    }

    char* pReturn = (char*)malloc(sizeof(char) * (size + 1));
    if (pReturn == NULL) {
        printf("Error, malloc(), reverseString()\n");
        return NULL;
    }


    // 스택 생성
    LinkedStack* pStack = createLinkedStack();
    if (pStack == NULL) {
        printf("Error, createLinkedStack() failed, reverseString()\n");
        free(pReturn);
        return NULL;
    }

    int i = 0;
    StackNode node;
    for (i = 0 ; i < size ; i++) {
        node.data = pSource[i];
        pushLinkedStack(pStack, node);
    }

    StackNode* pNode = NULL;
    for (i = 0 ; i < size ; i++) {
        pNode = popLinkedStack(pStack);
        if (pNode != NULL) {
            pReturn[i] = pNode->data;
            free(pNode);
        }
    }
    pReturn[i] = '\0';
    deleteLinkedStack(pStack);

    return pReturn;
}

int checkBracketMatching(char* pSource) {
    if (pSource == NULL) {
        printf("Error, pSource is null, checkBracketMatching()\n");
        return FAILED;
    }

    int size = strlen(pSource);
    if (size == 0) {
        printf("Error, pSource size is 0, checkBracketMatching()\n");
        return FAILED;
    }

    LinkedStack* pStack = createLinkedStack();
    if (pStack == NULL) {
        printf("Error, createLinkedStack() failed, checkBracketMatching()\n");
        return FAILED;
    }

    int ret = TRUE;
    char symbol = '\0';
    char checkSymbol = '\0';
    StackNode* pNode = NULL;
    StackNode node;
    int i = 0;
    for (i = 0; i < size && ret == TRUE; i++) {
        symbol = pSource[i];
        switch (symbol) {
            case '(':
                // fall-through
            case '[':
                // fall-through
            case '{':
                node.data = symbol;
                pushLinkedStack(pStack, node);
                break;
            case ')':
                // fall-through
            case ']':
                // fall-through
            case '}':
                pNode = popLinkedStack(pStack);
                if (pNode == NULL) {
                    ret = FALSE;
                    break;
                } else {
                    checkSymbol = pNode->data;
                    // 팝된 문자 checkSymbol 이 앞서 읽어 들인 여는 괄호
                    // symbol 과 맞는 닫는 괄호인지를 점검
                    if ((symbol == ')' && checkSymbol == '(')
                            || (symbol == ']' && checkSymbol == '[')
                            || (symbol == '}' && checkSymbol == '{')) {
                        // right. do nothing.
                    } else {
                        ret = FALSE;
                    }
                    free(pNode); // pop 된 노드의 메모리 해제
                }
                break;
        } // end-of-switch
    } // end-of-for
    if (isLinkedStackEmpty(pStack) == FALSE) {
        // 스택에 남아 있는 노드가 있으면 오류. 여는 괄호와 닫는
        // 괄호의 개수가 맞지 않는 경우이다.
        ret = FALSE;
    }
    deleteLinkedStack(pStack);
    return ret;
}
