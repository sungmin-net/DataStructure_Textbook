#include <stdio.h>
#include <stdlib.h>

#include "573p_binsearchtree.h"

BinSearchTree* createBinSearchTree() {
    BinSearchTree* pReturn = NULL;
    pReturn = (BinSearchTree*)malloc(sizeof(BinSearchTree));
    if (pReturn != NULL) {
        pReturn->pRootNode = NULL;
    } else {
        printf("����, �޸��Ҵ�, createBinSearchTree()\n");
    }
    return pReturn;
}

int insertElementBinSearchTree(BinSearchTree* pBinSearchTree,
        BinSearchTreeNode element) {
    int ret = TRUE;
    BinSearchTreeNode* pParentNode = NULL;
    BinSearchTreeNode* pNewNode = NULL;
    if (pBinSearchTree == NULL) {
        ret = FALSE;
        return ret;
    }
    pParentNode = pBinSearchTree->pRootNode;
    while (pParentNode != NULL) {
        if (element.key == pParentNode->key) {
            // case1. �ߺ��� Ű�� �߰ߵ� ���
            printf("����, �ߺ��� Ű - [%d], insertElementBinSearchTree()\n",
                    element.key);
            ret = FALSE;
            return ret;
        } else if (element.key < pParentNode->key) {
            // case2. ���� ��� Ű ������ ���� ���.
            // ���� ���� Ʈ���� �̵�
            if (pParentNode->pLeftChild == NULL) {
                // ���� �ڽ� ��尡 NULL �̸�, ���ο� ��带 ������ ��ġ�� �߰�
                break;
            } else {
                // ���� �ڽ� ��尡 NULL �� �ƴϸ�, ��� ���� �ڽ� ���� �̵�
                pParentNode = pParentNode->pLeftChild;
            }
        } else {
            // case3. ���� ����� Ű ������ ū ���.
            // ������ ���� Ʈ���� �̵�
            if (pParentNode->pRightChild == NULL) {
                // ������ �ڽ� ��尡 NULL �̸�, ���ο� ��带 ������ ��ġ��
                // �߰�
                break;
            } else {
                // ������ �ڽ� ��尡 NULL �� �ƴϸ�, ��� ������ �ڽ� ����
                // �̵�
                pParentNode = pParentNode->pRightChild;
            }
        }
    }
    pNewNode = (BinSearchTreeNode*)malloc(sizeof(BinSearchTreeNode));
    if (pNewNode != NULL) {
        *pNewNode = element;
        pNewNode->pLeftChild = NULL;
        pNewNode->pRightChild = NULL;
        if (pParentNode == NULL) {
            // ���� �߰��Ǵ� ����� �θ� ��尡 NULL �� ���, �� ��Ʈ ��尡
            // NULL �� ����̸�, ���� �߰��Ǵ� ��带 ���� Ž�� Ʈ���� ��Ʈ
            // ��尡 �ȴ�.
            pBinSearchTree->pRootNode = pNewNode;
        } else {
            // ���ο� ����� Ű ���� �θ� ��� pParentNode �� Ű ���� ��
            if (pNewNode->key < pParentNode->key) {
                // �θ����� Ű ������ �۴ٸ� ���� �ڽ� ���� �߰�
                pParentNode->pLeftChild = pNewNode;
            } else {
                // �׷��� ������, ������ �ڽ� ���� �߰�
                pParentNode->pRightChild = pNewNode;
            }
        }
        ret = TRUE;
    } else {
        printf("����, �޸� �Ҵ�, insertElementBinSearchTree()\n");
        ret = FALSE;
    }
    return ret;
}

int deleteElementBinSearchTree(BinSearchTree* pBinSearchTree, int key) {
    int ret = TRUE;
    BinSearchTreeNode* pDelNode = NULL;
    BinSearchTreeNode* pParentNode = NULL;
    BinSearchTreeNode* pPredecessor = NULL;
    BinSearchTreeNode* pSuccessor = NULL;
    BinSearchTreeNode* pChildNode = NULL;

    if (pBinSearchTree == NULL) {
        ret = FALSE;
        return ret;
    }
    pParentNode = NULL;
    pDelNode = pBinSearchTree->pRootNode;
    // ���� ��� ���� ���� ��� ����� �θ� ��� ã��
    while (pDelNode != NULL) {
        if (key == pDelNode->key) {
            break;
        }
        pParentNode = pDelNode;
        if (key < pDelNode->key) {
            pDelNode = pDelNode->pLeftChild;
        } else {
            pDelNode = pDelNode->pRightChild;
        }
        if (pDelNode == NULL) {
            printf("����, �������� �ʴ� Ű - [%d], deleteElementBinSearchTree()\n",
                    key);
            ret = FALSE;
            return ret;
        }
    }
    if (pDelNode->pLeftChild == NULL && pDelNode->pRightChild == NULL) {
        // ���� ��� ����� �ڽ� ��尡 0���� ���
        if (pParentNode != NULL) {
            if (pParentNode->pLeftChild == pDelNode) {
                pParentNode->pLeftChild = NULL;
            } else {
                pParentNode->pRightChild = NULL;
            }
        } else {
            pBinSearchTree->pRootNode = NULL;
        }
    } else if (pDelNode->pLeftChild != NULL && pDelNode->pRightChild != NULL) {
        // ���� ��� ����� �ڽ� ��尡 2���� ���
        pPredecessor = pDelNode;
        pSuccessor = pDelNode->pLeftChild;
        // ���� ����Ʈ������ ���� ū Ű ���� ������ ��� ã��
        while (pSuccessor->pRightChild != NULL) {
             // ���� ����Ʈ���� ���� �� �ڽ� ��带 ���� ��� �̵�
            pPredecessor = pSuccessor;
            pSuccessor = pSuccessor->pRightChild;
        }
        // pSuccessor �� ������ ��带 ��ü�� ��ü ��带 ����Ų��.
        // ������ ��� pDelNode �� �ڽ� ��带 ��ü ��� pSuccessor ��
        // �ڽ� ���� ����
        pPredecessor->pRightChild = pSuccessor->pLeftChild;
        pSuccessor->pLeftChild = pDelNode->pLeftChild;
        pSuccessor->pRightChild = pDelNode->pRightChild;
        if (pParentNode != NULL) {
            // ��ü ��� pSuccessor �� ���� ���� ����� �θ� ��� pParentNode ��
            // ���ο� �ڽ� ���� ����
            if (pParentNode->pLeftChild == pDelNode) {
                pParentNode->pLeftChild = pSuccessor;
            } else {
                pParentNode->pRightChild = pSuccessor;
            }
        } else {
            pBinSearchTree->pRootNode = pSuccessor;
            // �θ��尡 NULL �̸� ��Ʈ ��尡 �����Ǿ��ٴ� �ǹ��̹Ƿ�
            // ���� Ž�� Ʈ���� ���ο� ��Ʈ ���� ����
        }
    } else {
        // ���� ��� ����� �ڽ� ��尡 1���� ��츦 ó��
        if (pDelNode->pLeftChild != NULL) {
            pChildNode = pDelNode->pLeftChild;
        } else {
            pChildNode = pDelNode->pRightChild;
        }

        if (pParentNode != NULL) {
            if (pParentNode->pLeftChild == pDelNode) {
                pParentNode->pLeftChild = pChildNode;
            } else {
                pParentNode->pRightChild = pChildNode;
            }
        } else {
            pBinSearchTree->pRootNode = pChildNode;
        }
    }
    free(pDelNode);
    return ret;
}

BinSearchTreeNode* searchBinSearchTree(BinSearchTree* pBinSearchTree, int key) {
    BinSearchTreeNode* pReturn = NULL;

    if (pBinSearchTree == NULL) {
        return NULL;
    }
    pReturn = pBinSearchTree->pRootNode;
    while (pReturn != NULL) {
        if (key == pReturn->key) {
            break;
        } else if (key < pReturn->key) {
            pReturn = pReturn->pLeftChild;
        } else {
            pReturn = pReturn->pRightChild;
        }
    }
    return pReturn;
}

void deleteBinSearchTree(BinSearchTree* pBinSearchTree) {
    if (pBinSearchTree != NULL) {
        deleteBinSearchTreeInternal(pBinSearchTree->pRootNode);
        free(pBinSearchTree);
    }
}

void deleteBinSearchTreeInternal(BinSearchTreeNode* pTreeNode) {
    if (pTreeNode != NULL) {
        deleteBinSearchTreeInternal(pTreeNode->pLeftChild);
        deleteBinSearchTreeInternal(pTreeNode->pRightChild);
        free(pTreeNode);
    }
}

