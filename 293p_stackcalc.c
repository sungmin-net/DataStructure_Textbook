#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "290p_exprdef.h"
#include "292p_exprlinkedstack.h"
#include "292p_stackcalc.h"

int pushLinkedStackExprToken(LinkedStack* pStack, ExprToken data) {
    StackNode node = {0,};
    node.data = data;
    return pushLinkedStack(pStack, node);
}

void calcExpr(ExprToken* pExprTokens, int tokenCount) {
    if (pExprTokens == NULL) {
        printf("Error, pExprTokens is null, calcExpr()\n");
        return;
    }

    LinkedStack* pStack = createLinkedStack();
    if (pStack == NULL) {
        printf("error, createLinkedStack() failed., calcExpr()\n");
        return;
    }

    StackNode* pNode1 = NULL;
    StackNode* pNode2 = NULL;
    Precedence tokenType;
    int i = 0;
    for (i = 0; i < tokenCount; i++) {
        tokenType = pExprTokens[i].type;
        if (tokenType == operand) {
            pushLinkedStackExprToken(pStack, pExprTokens[i]);
        } else {
            pNode2 = popLinkedStack(pStack);
            if (pNode2 != NULL) {
                pNode1 = popLinkedStack(pStack);
                if (pNode1 != NULL) {
                    float op1 = pNode1->data.value;
                    float op2 = pNode2->data.value;
                    ExprToken newToken;
                    newToken.type = operand;
                    switch (tokenType) {
                    case plus:
                        newToken.value = op1 + op2;
                        break;
                    case minus:
                        newToken.value = op1 - op2;
                        break;
                    case times:
                        newToken.value = op1 * op2;
                        break;
                    case divide:
                        newToken.value = op1 / op2;
                        break;
                    }
                    pushLinkedStackExprToken(pStack, newToken);
                    free(pNode1);
                }
                free(pNode2);
            }
        } // end of else
    } // end of for
    // ������ ���� ó�� ��� ���� ���ÿ��� pop �Ѵ�.
    pNode1 = popLinkedStack(pStack);
    if (pNode1 != NULL) {
        printf("���� ��� ���[%f]\n", pNode1->data.value);
        free(pNode1);
    } else {
        printf("����, ������ ������ �ֽ��ϴ�.\n");
    }
    deleteLinkedStack(pStack);
}

void convertInfixToPostfix(ExprToken* pExprTokens, int tokenCount) {
    if (pExprTokens == NULL) {
        printf("Error, pExprTokens is NULL, convertInfixToPostfix()\n");
        return;
    }
    LinkedStack* pStack = createLinkedStack();
    if (pStack == NULL) {
        printf("Error, createLinkedStack() failed, convertInfixToPostfix()\n");
        return;
    }

    StackNode* pNode = NULL;
    Precedence tokenType;
    Precedence inStackTokenType;
    int i = 0;
    for (i = 0 ; i < tokenCount ; i++) {
        tokenType = pExprTokens[i].type;
        switch(tokenType) {
        case operand:
            printf("%f\n", pExprTokens[i].value);
            break;
        case rparen:
            pNode = popLinkedStack(pStack);
            while (pNode != NULL && pNode->data.type != lparen) {
                printToken(pNode->data);
                free(pNode);
                pNode = popLinkedStack(pStack);
            }
            if (pNode != NULL) {
                free(pNode);
            }
            break;
        default:
            while (isLinkedStackEmpty(pStack) == FALSE) {
                inStackTokenType = peekLinkedStack(pStack)->data.type;
                if (outStackPrecedence(tokenType)
                        <= inStackPrecedence(inStackTokenType)) {
                    pNode = popLinkedStack(pStack);
                    if (pNode != NULL) {
                        printToken(pNode->data);
                        free(pNode);
                    }
                } else {
                    break;
                }
            }
            pushLinkedStackExprToken(pStack, pExprTokens[i]);
            break;
        } // end of switch
    } // end of for

    while (isLinkedStackEmpty(pStack) == FALSE) {
        pNode = popLinkedStack(pStack);
        if (pNode != NULL) {
            printToken(pNode->data);
            free(pNode);
        }
    }
    deleteLinkedStack(pStack);
}

int inStackPrecedence(Precedence oper) {
    switch(oper) {
    case lparen :
        return 0;
    case rparen :
        return 4;
    case times :
        // fall-through
    case divide :
        return 2;
    case plus :
    case minus :
        return 1;
    }
    return -1;
}

int outStackPrecedence(Precedence oper) {
    switch (oper) {
    case lparen :
        return 5;
    case rparen :
        return 4;
    case times :
        // fall-through
    case divide :
        return 2;
    case plus :
        // fall-through
    case minus :
        return 1;
    }
    return -1;
}

void printToken(ExprToken element) {
    switch (element.type) {
    case lparen :
        printf("(\n");
        break;
    case rparen :
        printf(")\n");
        break;
    case plus :
        printf("+\n");
        break;
    case minus :
        printf("-\n");
        break;
    case times :
        printf("*\n");
        break;
    case divide :
        printf("/\n");
        break;
    case operand :
        printf("%f\n", element.value);
        break;
    }
}









