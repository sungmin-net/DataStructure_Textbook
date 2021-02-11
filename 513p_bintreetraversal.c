#include <stdio.h>
#include <stdlib.h>
#include "509p_bintree.h"
#include "511p_bintreelinkedqueue.h"
#include "511p_bintreelinkedstack.h"
#include "512p_bintreetraversal.h"

int pushLinkedStackBinTreeNode(LinkedStack* pStack, BinTreeNode* pNode) {
    StackNode node = {0,};
    node.data = pNode;
    return pushLinkedStack(pStack, node);
}

int enqueueLinkedQueueBinTreeNode(LinkedQueue* pQueue, BinTreeNode* pNode) {
    QueueNode node = {0,};
    node.data = pNode;
    return enqueueLinkedQueue(pQueue, node);
}

void preorderTraversalBinTree(BinTree* pBinTree) {
    LinkedStack* pStack = NULL;
    StackNode* pStackNode = NULL;
    BinTreeNode* pRootNode = NULL;
    BinTreeNode* pLeftChildNode = NULL;
    BinTreeNode* pRightChildNode = NULL;

    if (pBinTree == NULL) {
        return;
    }

    pRootNode = getRootNodeBinTree(pBinTree);
    if (pRootNode == NULL) {
        return;
    }
    pStack = createLinkedStack();
    if (pStack == NULL) {
        return;
    }
    pushLinkedStackBinTreeNode(pStack, pRootNode);
    while(1) {
        if (isLinkedStackEmpty(pStack) == TRUE) {
            break;
        } else {
            pStackNode = popLinkedStack(pStack);
            if (pStackNode != NULL) {
                pRootNode = pStackNode->data;
                printf("%c ", pRootNode->data);
                pLeftChildNode = getLeftChildNodeBinTree(pRootNode);
                pRightChildNode = getRightChildNodeBinTree(pRootNode);
                if (pRightChildNode != NULL) {
                    pushLinkedStackBinTreeNode(pStack, pRightChildNode);
                }
                if (pLeftChildNode != NULL) {
                    pushLinkedStackBinTreeNode(pStack, pLeftChildNode);
                }
                free(pStackNode);
            }
        }
    }
    deleteLinkedStack(pStack);
}

void inorderTraversalBinTree(BinTree* pBinTree) {
    LinkedStack* pStack = NULL;
    StackNode* pStackNode = NULL;
    BinTreeNode* pRootNode = NULL;
    BinTreeNode* pNode = NULL;

    if (pBinTree == NULL) {
        return;
    }
    pRootNode = getRootNodeBinTree(pBinTree);
    if (pRootNode == NULL) {
        return;
    }
    pStack = createLinkedStack();
    if (pStack == NULL) {
        return;
    }
    pNode = pRootNode;
    while(1) {
        for(;pNode != NULL;pNode = getLeftChildNodeBinTree(pNode)) {
            pushLinkedStackBinTreeNode(pStack, pNode);
        }
        if (isLinkedStackEmpty(pStack) == TRUE) {
            break;
        } else {
            pStackNode = popLinkedStack(pStack);
            if (pStackNode != NULL) {
                pNode = pStackNode->data;
                printf("%c ", pNode->data);
                pNode = getRightChildNodeBinTree(pNode);
                free(pStackNode);
            }
        }
    }
    deleteLinkedStack(pStack);
}

void levelorderTraversalBinTree(BinTree* pBinTree) {
    LinkedQueue* pQueue = NULL;
    QueueNode* pQueueNode = NULL;
    BinTreeNode* pRootNode = NULL;
    BinTreeNode* pLeftChildNode = NULL;
    BinTreeNode* pRightChildNode = NULL;

    if (pBinTree == NULL) {
        return;
    }

    pRootNode = getRootNodeBinTree(pBinTree);
    if (pRootNode == NULL) {
        return;
    }
    pQueue = createLinkedQueue();
    if (pQueue == NULL) {
        return;
    }
    enqueueLinkedQueueBinTreeNode(pQueue, pRootNode);
    while (1) {
        if (isLinkedQueueEmpty(pQueue) == TRUE) {
            break;
        } else {
            pQueueNode = dequeueLinkedQueue(pQueue);
            if (pQueueNode != NULL) {
                pRootNode = pQueueNode->data;
                if (pRootNode != NULL) {
                    printf("%c ", pRootNode->data);
                }
                pLeftChildNode = getLeftChildNodeBinTree(pRootNode);
                pRightChildNode = getRightChildNodeBinTree(pRootNode);
                if (pLeftChildNode != NULL) {
                    enqueueLinkedQueueBinTreeNode(pQueue, pLeftChildNode);
                }
                if (pRightChildNode != NULL) {
                    enqueueLinkedQueueBinTreeNode(pQueue, pRightChildNode);
                }
                free(pQueueNode);
            }
        }
    }
    deleteLinkedQueue(pQueue);
}


