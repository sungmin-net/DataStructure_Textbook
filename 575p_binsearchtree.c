#include <stdio.h>
#include <stdlib.h>

#include "573p_binsearchtree.h"

BinSearchTree* createBinSearchTree() {
    BinSearchTree* pReturn = NULL;
    pReturn = (BinSearchTree*)malloc(sizeof(BinSearchTree));
    if (pReturn != NULL) {
        pReturn->pRootNode = NULL;
    } else {
        printf("오류, 메모리할당, createBinSearchTree()\n");
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
            //  case1. 중복된 키가 발견된 경우
            printf("오류, 중복된 키 - [%d], insertElementBinSearchTree()",
                    element.key);
            ret = FALSE;
            return ret;
        } else if (element.key < pParentNode->key) {
            // case2. 현재 노드 키 값보다 작은 경우.
            // 왼쪽 서브 트리로 이동
            if (pParentNode->pLeftChild == NULL) {
                // 왼쪽 자식 노드가 NULL 이면, 새로운 노드를 삽입할 위치를 발견
                break;
            } else {
                // 왼쪽 자식 노드가 NULL 이 아니면, 계속 왼쪽 자식 노드로 이동
                pParentNode = pParentNode->pLeftChild;
            }
        } else {
            // case3. 현재 노드의 키 값보다 큰 경우.
            // 오른쪽 서브 트리로 이동
            if (pParentNode->pRightChild == NULL) {
                // 오른쪽 자식 노드가 NULL 이면, 새로운 노드를 삽입할 위치를
                // 발견
                break;
            } else {
                // 오른쪽 자식 노드가 NULL 이 아니면, 계속 오른쪽 자식 노드로
                // 이동
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
            // 새로 추가되는 노드의 부모 노드가 NULL 인 경우, 즉 루트 노드가
            // NULL 인 경우이며, 새로 추가되는 노드를 이진 탐색 트리의 루트
            // 노드가 된다.
            pBinSearchTree->pRootNode = pNewNode;
        } else {
            // 새로운 노드의 키 값과 부모 노드 pParentNode 의 키 값을 비교
            if (pNewNode->key < pParentNode->key) {
                // 부모노드의 키 값보다 작다면 왼쪽 자식 노드로 추가
                pParentNode->pLeftChild = pNewNode;
            } else {
                // 그렇지 않으면, 오른쪽 자식 노드로 추가
                pParentNode->pRightChild = pNewNode;
            }
        }
        ret = TRUE;
    } else {
        printf("오류, 메모리 할당, insertElementBinSearchTree()\n");
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
    // 삭제 대상 노드와 삭제 대상 노드의 부모 노드 찾기
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
            printf("오류, 존재하지 않는 키 - [%d], deleteElementBinSearchTree()\n",
                    key);
            ret = FALSE;
            return ret;
        }
    }
    if (pDelNode->pLeftChild == NULL && pDelNode->pRightChild == NULL) {
    	// 삭제 대상 노드의 자식 노드가 0개인 경우
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
    	// 삭제 대상 노드의 자식 노드가 2개인 경우
        pPredecessor = pDelNode;
        pSuccessor = pDelNode->pLeftChild;
        // 왼쪽 서브트리에서 가장 큰 키 값을 가지는 노드 찾기
        while (pSuccessor->pRightChild != NULL) {
        	// 왼쪽 서브트리의 오른 쪽 자식 노드를 따라 계속 이동
            pPredecessor = pSuccessor;
            pSuccessor = pSuccessor->pRightChild;
        }
        // pSuccessor 는 삭제할 노드를 대체할 대체 노드를 가리킨다.
        // 삭제할 노드 pDelNode 의 자식 노드를 대체 노드 pSuccessor 의
        // 자식 노드로 변경
        pPredecessor->pRightChild = pSuccessor->pLeftChild;
        pSuccessor->pLeftChild = pDelNode->pLeftChild;
        pSuccessor->pRightChild = pDelNode->pRightChild;
        if (pParentNode != NULL) {
            // 대체 노드 pSuccessor 를 기존 삭제 노드의 부모 노드 pParentNode 의
            // 새로운 자식 노드로 설정
            if (pParentNode->pLeftChild == pDelNode) {
                pParentNode->pLeftChild = pSuccessor;
            } else {
                pParentNode->pRightChild = pSuccessor;
            }
        } else {
            pBinSearchTree->pRootNode = pSuccessor;
            // 부모노드가 NULL 이면 루트 노드가 삭제되었다는 의미이므로
            // 이진 탐색 트리의 새로운 루트 노드로 설정
        }
    } else {
        // 삭제 대상 노드의 자식 노드가 1개인 경우를 처리
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

