#include "509p_bintree.h"

#include <stdio.h>
#include <stdlib.h>

BinTree* makeBinTree(BinTreeNode rootNode) {
    BinTree* pReturn = NULL;
    pReturn = (BinTree*)malloc(sizeof(BinTree));
    if (pReturn != NULL) {
        pReturn->pRootNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        if (pReturn->pRootNode != NULL) {
            *(pReturn->pRootNode) = rootNode;
            pReturn->pRootNode->pLeftChild = NULL;
            pReturn->pRootNode->pRightChild = NULL;
        } else {
            printf("�޸��Ҵ�2, makeBinTree()\n");
            free(pReturn);
            pReturn = NULL;
        }
    } else {
        printf("�޸��Ҵ�1, makeBinTree()\n");
    }
    return pReturn;
}

BinTreeNode* getLeftChildNodeBinTree(BinTreeNode* pParentNode) {
    return pParentNode->pLeftChild;
}

BinTreeNode* getRightChildNodeBinTree(BinTreeNode* pParentNode) {
    return pParentNode->pRightChild;
}

BinTreeNode* insertLeftChildNodeBinTree(BinTreeNode* pParentNode,
        BinTreeNode element) {
    BinTreeNode* pReturn = NULL;
    if (pParentNode != NULL) {
        if (pParentNode->pLeftChild == NULL) {
            pParentNode->pLeftChild = (BinTreeNode*)malloc(sizeof(BinTreeNode));
            if (pParentNode->pLeftChild != NULL) {
                *(pParentNode->pLeftChild) = element;
                pParentNode->pLeftChild->pLeftChild = NULL;
                pParentNode->pLeftChild->pRightChild = NULL;
                pReturn = pParentNode->pLeftChild;
            } else {
                printf("����, �޸��Ҵ�, insertLeftChildNodeBinTree()\n");
            }
        } else {
            printf("����, �̹� ��尡 �����մϴ�. insertLeftChildNodeBinTree()\n");
        }
    }
    return pReturn;
}

BinTreeNode* insertRightChildNodeBinTree(BinTreeNode* pParentNode,
        BinTreeNode element) {
    BinTreeNode* pReturn = NULL;
    if (pParentNode != NULL) {
        if (pParentNode->pRightChild == NULL) {
            pParentNode->pRightChild = (BinTreeNode*)malloc(sizeof(BinTreeNode));
            if (pParentNode->pRightChild != NULL) {
                *(pParentNode->pRightChild) = element;
                pParentNode->pRightChild->pLeftChild = NULL;
                pParentNode->pRightChild->pRightChild = NULL;
                pReturn = pParentNode->pRightChild;
            } else {
                printf("����, �޸��Ҵ�, insertRightChildNodeBinTree()\n");
            }
        } else {
            printf("����, �̹� ��尡 �����մϴ�. insertRightChildNodeBinTree()\n");
        }
    }
    return pReturn;
}

BinTreeNode* getRootNodeBinTree(BinTree* pBinTree) {
    BinTreeNode* pReturn = NULL;
    if (pBinTree != NULL) {
        pReturn = pBinTree->pRootNode;
    }
    return pReturn;
}

void deleteBinTree(BinTree* pBinTree) {
    if (pBinTree != NULL) {
        deleteBinTreeNode(pBinTree->pRootNode);
        free(pBinTree);
    }
}

void deleteBinTreeNode(BinTreeNode* pNode) {
    if (pNode != NULL) {
        deleteBinTreeNode(pNode->pLeftChild);
        deleteBinTreeNode(pNode->pRightChild);
        free(pNode);
    }
}



