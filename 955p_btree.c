#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "955p_btreedef.h"
#include "955p_btreelinkedstack.h"
#include "953p_btree.h"

BTree* createBTree() {
    BTree* pReturn = NULL;
    pReturn = (BTree*)malloc(sizeof(BTree));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(BTree));
    } else {
        printf("오류, 메모리할당 createBTree()\n");
        return NULL;
    }
    return pReturn;
}

BTreeNodeData* searchBTree(BTree* pBTree, int key) {
    BTreeNodeData* pReturn = NULL;
    BTreeNode* pCurrentNode = NULL;
    int i = 0;

    if (pBTree != NULL) {
        pCurrentNode = pBTree->pRootNode;
        // B트리의 루트 노드부터 시작하여, 더이상 다음 노드가 없을 때까지
        // 루프를 돌면서 검색
        while (pCurrentNode != NULL) {
            for (i = 0 ; i < pCurrentNode->elementCount ; i++) {
                int parentKey = pCurrentNode->element[ i ].key;
                if (key == parentKey) {
                    // 검색이 성공한 경우
                    pReturn = &pCurrentNode->element[ i ];
                    return pReturn;
                } else if (key < parentKey) {
                    // 검색 키 값이 현재 비교 대상 키 값 parentKey 보다
                    // 작은 경우, 루프를 빠져나와 현재 자료의 서브트리로 이동
                    break;
                }
            }
            // 현재 노드의 서브트리로 내려가서 검색을 계속 수행
            pCurrentNode = pCurrentNode->pChildren[ i ];

        }
    }
    return pReturn;
}

int pushBTreeNode(LinkedStack* pStack, BTreeNode* data) {
    StackNode node = {0,};
    node.data = data;
    return pushLinkedStack(pStack, node);
}

int insertNodeBTree(BTree* pBTree, BTreeNodeData element) {
    int i = 0;
    BTreeNode* pParentNode = NULL;
    BTreeNode* pCurrentNode = NULL;
    LinkedStack* pStack = NULL;

    if (pBTree == NULL) {
        return FALSE;
    }

    pStack = createLinkedStack(); // 균형 유지 연산에 사용
    if (pStack == NULL) {
        return FALSE;
    }

    // insert 할 leaf node 찾기
    pCurrentNode = pBTree->pRootNode;
    while (pCurrentNode != NULL) {
        pParentNode = pCurrentNode;
        pushBTreeNode(pStack, pParentNode);

        for (i = 0 ; i < pCurrentNode->elementCount ; i++) {
            int parentKey = pCurrentNode->element[ i ].key;
            if (element.key == parentKey) {
                printf("오류, 중복된 키-[%d], insertNodeBTree()\n",
                        element.key);
                deleteLinkedStack(pStack);
                return FALSE;
            } else if (element.key < parentKey) {
                break;
            }
        }
        pCurrentNode = pCurrentNode->pChildren[ i ];
    }

    // 실제 노드 추가
    if (pParentNode == NULL) { // RootNode 가 아직 없는 경우.
        pBTree->pRootNode = createBTreeNode(element);
    } else {
        insertNodeElementBTree(pParentNode, element, NULL);
        splitNodeBTree(pBTree, pStack);
    }
    deleteLinkedStack(pStack);
    return TRUE;
}

void splitNodeBTree(BTree* pBTree, LinkedStack* pStack) {
    StackNode* pParentStackNode = NULL;
    StackNode* pCurrentStackNode = NULL;
    BTreeNode* pCurrentBTreeNode = NULL;
    BTreeNode* pNewBTreeNode = NULL;
    BTreeNodeData pivotElement = {0,};
    int pivotIndex = BTREE_ORDER / 2;
    int i = 0;
    if (pStack == NULL) {
        return;
    }
    pCurrentStackNode = popLinkedStack(pStack);
    while (pCurrentStackNode != NULL) {
        pCurrentBTreeNode = pCurrentStackNode->data;
        if (pCurrentBTreeNode->elementCount >= BTREE_ORDER) {
            pNewBTreeNode = (BTreeNode*)malloc(sizeof(BTreeNode));
            if (pNewBTreeNode != NULL) {
                memset(pNewBTreeNode, 0, sizeof(BTreeNode));
            } else {
                printf("오류, 메모리할당, splitNodeBTree()\n");
                break;
            }
            pivotElement = pCurrentBTreeNode->element[ pivotIndex ];
            memset(&pCurrentBTreeNode->element[ pivotIndex ], 0,
                    sizeof(BTreeNodeData));
            for(i = pivotIndex + 1 ; i < BTREE_ORDER ; i++) {
                pNewBTreeNode->element[ i - pivotIndex - 1 ] =
                        pCurrentBTreeNode->element[ i ];
                pNewBTreeNode->pChildren[i - pivotIndex - 1 ] =
                        pCurrentBTreeNode->pChildren[ i ];

                memset(&pCurrentBTreeNode->element[ i ], 0,
                        sizeof(BTreeNodeData));
                pCurrentBTreeNode->pChildren[ i ] = NULL;
            }
            pNewBTreeNode->pChildren[i - pivotIndex - 1 ] =
                                     pCurrentBTreeNode->pChildren[ i ];
            pCurrentBTreeNode->pChildren[ i ] = NULL;
            pNewBTreeNode->elementCount = BTREE_ORDER - pivotIndex - 1;
            pCurrentBTreeNode->elementCount = pivotIndex;

            pParentStackNode = popLinkedStack(pStack);
            if (pParentStackNode != NULL) {
                insertNodeElementBTree(pParentStackNode->data, pivotElement,
                        pNewBTreeNode);
            } else {
                // 트리 전체 depth 를 1 증가
                pBTree->pRootNode = createBTreeNode(pivotElement);
                pBTree->pRootNode->pChildren[ 0 ] = pCurrentBTreeNode;
                pBTree->pRootNode->pChildren[ 1 ] = pNewBTreeNode;
            }
        }

        if (pCurrentStackNode != NULL) {
            free(pCurrentStackNode);
        }
        pCurrentStackNode = pParentStackNode;
        pParentStackNode = NULL;
    }

    if (pCurrentStackNode != NULL) {
        free(pCurrentStackNode);
    }
    if (pParentStackNode != NULL) {
        free(pParentStackNode);
    }
}

BTreeNode* createBTreeNode(BTreeNodeData element) {
    BTreeNode* pReturn = NULL;
    pReturn = (BTreeNode*)malloc(sizeof(BTreeNode));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(BTreeNode));
        pReturn->element[ 0 ] = element;
        pReturn->elementCount = 1;
    } else {
        printf("Error, malloc(), createBTreeNode()\n");
    }
    return pReturn;
}

void insertNodeElementBTree(BTreeNode* pCurrentNode, BTreeNodeData element,
        BTreeNode* pRightChildNode) {
    int i = 0;
    for (i = pCurrentNode->elementCount - 1; i >= 0 ; i--) {
        int tempKey = pCurrentNode->element[ i ].key;
        if (element.key < tempKey) {
            pCurrentNode->element[ i + 1 ] = pCurrentNode->element[ i ];
            pCurrentNode->pChildren[ i + 2 ] = pCurrentNode->pChildren[ i + 1 ];
        } else {
            break;
        }
    }
    pCurrentNode->element[ i + 1 ] = element;
    pCurrentNode->pChildren[ i + 2 ] = pRightChildNode;
    pCurrentNode->elementCount++;
}

int deleteNodeBTree(BTree* pBTree, int key) {
    int ret = FALSE;
    int i = 0;
    int isFound = FALSE;
    BTreeNode* pParentNode = NULL;
    BTreeNode* pCurrentNode = NULL;
    LinkedStack* pStack = NULL;

    if (pBTree == NULL) {
        return FALSE;
    }

    pStack = createLinkedStack(); // 균형 유지 연산용 스택
    if (pStack == NULL) {
        return FALSE;
    }

    // 삭제할 노드 찾기
    pCurrentNode = pBTree->pRootNode;
    while (pCurrentNode != NULL && isFound == FALSE) {
        pParentNode = pCurrentNode;
        pushBTreeNode(pStack, pParentNode);
        for (i = 0 ; i < pCurrentNode->elementCount ; i++) {
            int parentKey = pCurrentNode->element[ i ].key;
            if (key == parentKey) {
                isFound = TRUE;
                break;
            } else if (key < parentKey) {
                break;
            }
        }
        pCurrentNode = pCurrentNode->pChildren[ i ];
    }

    // 대상 노드 삭제
    if (isFound == TRUE) {
        if (isLeafNode(pParentNode) == FALSE) {
            pParentNode = replaceLeafNodeBTree(pBTree, pParentNode, i, pStack);
        } else {
            deleteKeyBTree(pParentNode, i);
        }
        if (pParentNode->elementCount < (BTREE_ORDER / 2)) {
            balanceBTree(pBTree, pStack);
        }
        ret = TRUE;
    } else {
        printf("오류, 검색키-[%d]가 발견되지 않았습니다. deleteNodeBTree()\n",
                key);
    }
    deleteLinkedStack(pStack);
    return ret;
}

void balanceBTree(BTree* pBTree, LinkedStack* pStack) {
    StackNode* pParentStackNode = NULL;
    StackNode* pCurrentStackNode = NULL;
    BTreeNode* pParentBTreeNode = NULL;
    BTreeNode* pCurrentBTreeNode = NULL;

    int index = 0;

    if (pStack == NULL) {
        return;
    }
    pCurrentStackNode = popLinkedStack(pStack);
    if (pCurrentStackNode == NULL) {
        return;
    }

    pCurrentBTreeNode = pCurrentStackNode->data;
    if (pCurrentBTreeNode->elementCount >= (BTREE_ORDER / 2)) {
        free(pCurrentStackNode);
        return;
    }

    pParentStackNode = popLinkedStack(pStack);
    if (pParentStackNode == NULL) {
        free(pCurrentStackNode);
        return;
    }

    pParentBTreeNode = pParentStackNode->data;
    index = getIndexInfo(pParentBTreeNode, pCurrentBTreeNode);

    if (index < pParentBTreeNode->elementCount &&
            pParentBTreeNode->pChildren[ index + 1 ]->elementCount >=
            (BTREE_ORDER / 2 + 1)) {
        // 오른쪽에서 빌려옴
        borrowRightNodeBTree(pParentBTreeNode, pCurrentBTreeNode, index,
                pParentBTreeNode->pChildren[ index + 1 ]);
    } else if (index > 0 &&
            pParentBTreeNode->pChildren[ index - 1 ]->elementCount >=
            (BTREE_ORDER / 2 + 1)) {
        // 왼쪽에서 빌려옴
        borrowLeftNodeBTree(pParentBTreeNode, pCurrentBTreeNode, index,
                pParentBTreeNode->pChildren[ index - 1 ]);
    } else {
        // 병합
        mergeNodeBTree(pBTree, pStack, pParentBTreeNode, pCurrentBTreeNode,
                index);
    }

    if (pCurrentStackNode != NULL) {
        free(pCurrentStackNode);
    }
    if (pParentStackNode != NULL) {
        free(pParentStackNode);
    }
}

void borrowRightNodeBTree(BTreeNode* pParentNode, BTreeNode* pCurrentNode,
        int index, BTreeNode* pRightNode) {
    int elementCount = 0;
    if (pParentNode == NULL || pCurrentNode == NULL || pRightNode == NULL) {
        return;
    }

    // ParentNode 에서 자료 한 개 가져오기
    elementCount = pCurrentNode->elementCount;
    pCurrentNode->element[ elementCount ] = pParentNode->element[ index ];
    pCurrentNode->elementCount++;

    // 오른쪽 노드의 가장 왼쪽 자료 가져오기.
    pParentNode->element[ index ] = pRightNode->element[ 0 ];

    // 오른쪽 노드 왼쪽으로 한칸씩 shift.
    deleteKeyBTree(pRightNode, 0);
}

void borrowLeftNodeBTree(BTreeNode* pParentNode, BTreeNode* pCurrentNode,
        int index, BTreeNode* pLeftNode) {
    int elementCount = 0;
    BTreeNodeData leftElement = {0,};
    BTreeNodeData parentElement = {0,};

    if (pParentNode == NULL || pCurrentNode == NULL || pLeftNode == NULL) {
        return;
    }

    // 왼쪽 노드의 가장 오른쪽 자료를 부모 노드로 이동.
    elementCount = pLeftNode->elementCount;
    leftElement = pLeftNode->element[ elementCount - 1 ];
    parentElement = pParentNode->element[ index - 1 ];
    deleteKeyBTree(pLeftNode, elementCount - 1);

    pParentNode->element[ index - 1 ] = leftElement;

    // 부모 노드의 자료를 오른쪽 노드의 가장 왼쪽으로 삽입
    insertNodeElementBTree(pCurrentNode, parentElement, NULL);
}

void mergeNodeBTree(BTree* pBTree, LinkedStack* pStack,
        BTreeNode* pParentBTreeNode, BTreeNode* pCurrentBTreeNode, int index) {
    StackNode* pParentStackNode = NULL;
    BTreeNode* pParentNode = NULL;
    BTreeNode* pLeftNode = NULL;
    BTreeNode* pRightNode = NULL;
    BTreeNodeData parentElement = {0,};
    int i = 0;
    int pivotIndex = 0;

    if (pBTree == NULL || pStack == NULL || pParentBTreeNode == NULL ||
            pCurrentBTreeNode == NULL) {
        return;
    }

    if (index < pParentBTreeNode->elementCount) {
        // 오른쪽 노드와 병합
        pLeftNode = pCurrentBTreeNode;
        pRightNode = pParentBTreeNode->pChildren[ index + 1];
        pivotIndex = index;
        parentElement = pParentBTreeNode->element[ pivotIndex ];
    } else {
        // 왼쪽 노드와 병합
        pLeftNode = pParentBTreeNode->pChildren[ index - 1];
        pRightNode = pCurrentBTreeNode;
        pivotIndex = index - 1;
        parentElement = pParentBTreeNode->element[ pivotIndex ];
    }

    // 왼쪽 노드에 부모 자료 추가
    insertNodeElementBTree(pLeftNode, parentElement, pRightNode->pChildren[0]);

    // 왼쪽 노드에 오른쪽 노드 자료들 추가
    for (i = 0 ; i < pRightNode->elementCount ; i++) {
        insertNodeElementBTree(pLeftNode, pRightNode->element[ i ],
                pRightNode->pChildren[ i + 1 ]);
    }
    deleteKeyBTree(pParentBTreeNode, pivotIndex);
    free(pRightNode);

    if (pParentBTreeNode->elementCount < (BTREE_ORDER / 2)) {
        int index = 0;
        pParentStackNode = popLinkedStack(pStack);
        if (pParentStackNode != NULL) {
            pParentNode = pParentStackNode->data;
            index = getIndexInfo(pParentNode, pParentBTreeNode);
            mergeNodeBTree(pBTree, pStack, pParentNode, pParentBTreeNode,
                    index);
            free(pParentStackNode);
        } else {
            if (pParentBTreeNode->elementCount == 0) {
                free(pBTree->pRootNode);
                pBTree->pRootNode = pLeftNode;
            }
        }
    }
}

BTreeNode* replaceLeafNodeBTree(BTree* pBTree, BTreeNode* pDelNode, int index,
        LinkedStack* pStack) {
    BTreeNode* pReturn = NULL;
    BTreeNodeData leafNodeElement = {0,};
    BTreeNode* pChildNode = NULL;
    BTreeNode* pParentNode = pDelNode;
    int elementCount = index;

    if (pBTree == NULL || pDelNode == NULL) {
        return pReturn;
    }

    do {
        pChildNode = pParentNode->pChildren[ elementCount ];
        pushBTreeNode(pStack, pChildNode);

        elementCount = pChildNode->elementCount;
        pParentNode = pChildNode;
    } while (pChildNode->pChildren[ elementCount ] != NULL);

    leafNodeElement = pChildNode->element[ elementCount - 1 ];
    pDelNode->element[ index ] = leafNodeElement;
    deleteKeyBTree(pChildNode, elementCount - 1);

    pReturn = pChildNode;
    return pReturn;
}

int isLeafNode(BTreeNode* pParentNode) {
    if (pParentNode != NULL && pParentNode->pChildren[ 0 ] == NULL) {
        return TRUE;
    }
    return FALSE;
}

int getIndexInfo(BTreeNode* pParentNode, BTreeNode* pCurrentNode) {
    int ret = 0;
    int i = 0;

    if (pParentNode != NULL) {
        for (i = 0 ; i <= pParentNode->elementCount ; i++) {
            if (pParentNode->pChildren[ i ] == pCurrentNode) {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

void deleteKeyBTree(BTreeNode* pNode, int index) {
    int i = 0;
    if (pNode != NULL) {
        for (i = index + 1 ; i < pNode->elementCount ; i++) {
            pNode->element[ i - 1 ] = pNode->element[ i ];
            pNode->pChildren[ i ] = pNode->pChildren[ i + 1 ];
        }
        memset(&pNode->element[ pNode->elementCount - 1 ], 0,
                sizeof(BTreeNodeData));
        pNode->pChildren[ pNode->elementCount ] = NULL;
        pNode->elementCount--;
    }
}

void displayBTree(BTree* pBTree) {
    if (pBTree != NULL) {
        displayBTreeNode(pBTree->pRootNode);
    }
}

void displayBTreeNode(BTreeNode* pNode) {
    int i = 0;
    static int x = 0;
    if (pNode != NULL) {
        x += 2;
        for (i = 2 ; i < x ; i++) {
            printf("    ");
        }
        for (i = 0 ; i < pNode->elementCount ; i++) {
            printf("(%d, %c) ", pNode->element[ i ].key,
                    pNode->element[ i ].value);
        }
        printf("\n");
        for (i = 0 ; i < pNode->elementCount + 1 ; i++) {
            displayBTreeNode(pNode->pChildren[ i ]);
        }
        x -= 2;
    }
}

void deleteBTree(BTree* pBTree) {
    if (pBTree != NULL) {
        deleteBTreeNode(pBTree->pRootNode);
        free(pBTree);
    }
}

void deleteBTreeNode(BTreeNode* pBTreeNode) {
    int i = 0;
    if (pBTreeNode != NULL) {
        for (i = 0 ; i <= pBTreeNode->elementCount ; i++) {
            deleteBTreeNode(pBTreeNode->pChildren[ i ]);
        }
        free(pBTreeNode);
    }
}


