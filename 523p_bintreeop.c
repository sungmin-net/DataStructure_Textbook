#include <stdio.h>
#include <stdlib.h>
#include "522p_bintree.h"
#include "523p_bintreeop.h"

BinTree* copyBinTree(BinTree* pSource) {
    BinTree* pReturn = NULL;
    if (pSource != NULL) {
        pReturn = (BinTree*)malloc(sizeof(BinTree));
        if (pReturn != NULL) {
            pReturn->pRootNode = copyBinTreeNode(pSource->pRootNode);
        } else {
            printf("오류, 메모리 할당, copyBinTree()\n");
        }
    }
    return pReturn;
}

BinTreeNode* copyBinTreeNode(BinTreeNode* pSourceNode) {
    BinTreeNode* pReturn = NULL;
    if (pSourceNode != NULL) {
        pReturn = (BinTreeNode*)malloc(sizeof (BinTreeNode));
        if (pReturn != NULL) {
            *pReturn = *pSourceNode;
            pReturn->pLeftChild = copyBinTreeNode(
                    getLeftChildNodeBinTree(pSourceNode));
            pReturn->pRightChild = copyBinTreeNode(
                    getRightChildNodeBinTree(pSourceNode));
        } else {
            printf("오류, 메모리할당, copyBinTreeNode()\n");
        }
    }
    return pReturn;
}

int isEqualBinTree(BinTree* pFirst, BinTree* pSecond) {
    int ret = FALSE;
    if (pFirst == NULL && pSecond == NULL) {
        ret = TRUE;
    } else if (pFirst != NULL && pSecond != NULL &&
            isEqualBinTreeNode(pFirst->pRootNode, pSecond->pRootNode) == TRUE) {
        ret = TRUE;
    }
    return ret;
}

int isEqualBinTreeNode(BinTreeNode* pFirst, BinTreeNode* pSecond) {
    int ret = FALSE;
    if (pFirst == NULL && pSecond == NULL) {
        ret = TRUE;
    } else if (pFirst != NULL && pSecond != NULL &&
            pFirst->data == pSecond->data &&
            isEqualBinTreeNode(pFirst->pLeftChild, pSecond->pLeftChild) == TRUE &&
            isEqualBinTreeNode(pFirst->pRightChild, pSecond->pRightChild) == TRUE) {
        ret = TRUE;
    }
    return ret;
}

int getNodeCountBinTree(BinTree* pSource) {
    int ret = 0;
    if (pSource != NULL) {
        ret = getNodeCountBinTreeNode(pSource->pRootNode);
    }
    return ret;
}

int getNodeCountBinTreeNode(BinTreeNode* pSource) {
    int ret = 0;
    if (pSource != NULL) {
        ret = getNodeCountBinTreeNode(pSource->pLeftChild)
                + getNodeCountBinTreeNode(pSource->pRightChild) + 1;
    }
    return ret;
}

int getLeafNodeCountBinTree(BinTree* pSource) {
    int ret = 0;
    if (pSource != NULL) {
        ret = getLeafNodeCountBinTreeNode(pSource->pRootNode);
    }
    return ret;
}

int getLeafNodeCountBinTreeNode(BinTreeNode* pSource) {
    int ret = 0;
    if (pSource != NULL) {
        if (pSource->pLeftChild == NULL && pSource->pRightChild == NULL) {
            ret = 1;
        } else {
            ret = getLeafNodeCountBinTreeNode(pSource->pLeftChild) +
                    getLeafNodeCountBinTreeNode(pSource->pRightChild);
        }
    }
    return ret;
}

int getHeightBinTree(BinTree* pSource) {
    int ret = 0;
    if (pSource != NULL) {
        ret = getHeightBinTreeNode(pSource->pRootNode);
    }
    return ret;
}

int getHeightBinTreeNode(BinTreeNode* pSource) {
    int ret = 0;
    if (pSource != NULL) {
        if (pSource->pLeftChild == NULL && pSource->pRightChild == NULL) {
            ret = 1;
        } else {
            int leftChildHeight = getHeightBinTreeNode(pSource->pLeftChild);
            int rightChildHeight = getHeightBinTreeNode(pSource->pRightChild);
            if (leftChildHeight >= rightChildHeight) {
                ret = 1 + leftChildHeight;
            } else {
                ret = 1 + rightChildHeight;
            }
        }
    }
    return ret;
}

void displayBinTree(BinTree* pTree) {
    if (pTree != NULL) {
        displayBinTreeNode(pTree->pRootNode, 0, 'O');
    } else {
        printf("트리가 NULL 입니다.\n");
    }
}

void displayBinTreeNode(BinTreeNode* pNode, int level, char type) {
    int i = 0;
    for (i = 0 ; i < level ; i++) {
        printf("    ");
    }

    if (pNode != NULL) {
        printf("-[%i,%c]%c\n", level, type, pNode->data);
        displayBinTreeNode(pNode->pLeftChild, level + 1, 'L');
        displayBinTreeNode(pNode->pRightChild, level + 1, 'R');
    } else {
        printf("NULL\n");
    }
}
