#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "906p_avldef.h"
#include "908p_avllinkedstack.h"
#include "908p_avltree.h"

AvlTree* createAvlTree() {
    AvlTree* pReturn = NULL;

    pReturn = (AvlTree*)malloc(sizeof(AvlTree));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(AvlTree));
    } else {
        printf("Error, malloc(), createAvlTree()\n");
        return NULL;
    }
    return pReturn;
}

AvlTreeNode* searchAvl(AvlTree* pAvlTree, int key) {
    AvlTreeNode* pReturn = NULL;
    AvlTreeNode* pNode = NULL;

    if (pAvlTree == NULL) {
        return NULL;
    }
    pNode = pAvlTree->pRootNode;
    if (pNode == NULL) {
        return NULL;
    }

    while (pNode != NULL) {
        if (key == pNode->data.key) {
            pReturn = pNode;
            break;
        } else if (key < pNode->data.key) {
            pNode = pNode->pLeftChild;
        } else {
            pNode = pNode->pRightChild;
        }
    }
    return pReturn;
}

int insertNodeAvl(AvlTree* pAvlTree, AvlTreeNodeData element) {
    int ret = TRUE;
    AvlTreeNode* pParentNode = NULL;
    AvlTreeNode* pNewNode = NULL;
    LinkedStack* pStack = NULL;

    if (pAvlTree == NULL) {
        ret = FALSE;
        return ret;
    }

    pStack = createLinkedStack(); // 스택 생성
    if (pStack == NULL) {
        ret = FALSE;
        return ret;
    }

    pParentNode = pAvlTree->pRootNode;
    while (pParentNode!= NULL) {
        // 부모 노드를 찾는 각 경로에 해당하는 노드를 스택에 저장.
        // 균형 유지 연산에 필요.
        pushAvlTreeNode(pStack, pParentNode);
        if (element.key == pParentNode->data.key) {
            printf("Error, 중복된 키[%d]가 존재합니다, insertNodeAvl()\n",
                    element.key);
            ret = FALSE;
            return ret;
        } else if(element.key < pParentNode->data.key) {
            if (pParentNode->pLeftChild == NULL) {
                break;
            } else {
                pParentNode = pParentNode->pLeftChild;
            }
        } else {
            if (pParentNode->pRightChild == NULL) {
                break;
            } else {
                pParentNode = pParentNode->pRightChild;
            }
        }
    }

    pNewNode = (AvlTreeNode*)malloc(sizeof(AvlTreeNode));
    if (pNewNode != NULL) {
        memset(pNewNode, 0, sizeof(AvlTreeNode));
        pNewNode->data = element;
        pNewNode->height = 1;
    } else {
        printf("Error, malloc() insertNodeAvl()\n");
    }

    if (pParentNode == NULL) {
        pAvlTree->pRootNode = pNewNode;
    } else {
        if (pNewNode->data.key < pParentNode->data.key) {
            pParentNode->pLeftChild = pNewNode;
        } else {
            pParentNode->pRightChild = pNewNode;
        }
    }
    ret = TRUE;
    balanceAvlTree(pAvlTree, pStack);
    deleteLinkedStack(pStack);
    return ret;
}

void balanceAvlTree(AvlTree* pAvlTree, LinkedStack* pStack) {
    AvlTreeNode* pParentNode = NULL;
    AvlTreeNode* pNode = NULL;
    AvlTreeNode* pChildNode = NULL;
    AvlTreeNode* pNewNode = NULL;

    if (pAvlTree == NULL || pStack == NULL) {
        return;
    }

    // 스택에 트리 노드가 없을 때까지 루프.
    while (isLinkedStackEmpty(pStack) == FALSE) {
        pNode = popAvlTreeNode(pStack);
        if (pNode != NULL) {
            updateHeightAndBalanceAvl(pNode); // 높이와 균현 인수 값 재계산
            if (pNode->balance >= -1 && pNode->balance <= 1) {
                // 계산된 균형 인수 값이 -1과 1 사이라면 균형 상태
                continue;
            }

            if (pNode->balance > 1) {
                // LL 회전 또는 LR 회전 수행
                pChildNode = pNode->pLeftChild;
                if (pChildNode->balance > 0) {
                    pNewNode = rotateLLAvlTree(pNode);
                } else {
                    pNewNode = rotateLRAvlTree(pNode);
                }
            } else if (pNode->balance < -1) {
                // RR 회전 또는 RL 회전 수행
                pChildNode = pNode->pRightChild;
                if (pChildNode->balance < 0) {
                    pNewNode = rotateRRAvlTree(pNode);
                } else {
                    pNewNode = rotateRLAvlTree(pNode);
                }
            }

            pParentNode = peekAvlTreeNode(pStack);
            // 노드 pNode 를 루트 노드로 하여 균형 유지 연산을 수행하고,
            // 변경된 루트노드 pNewNode 를 반영
            if (pParentNode != NULL) {
                if (pParentNode->pLeftChild == pNode) {
                    pParentNode->pLeftChild = pNewNode;
                } else {
                    pParentNode->pRightChild = pNewNode;
                }
            } else {
                // 트리의 루트 노드가 변경된 경우
                pAvlTree->pRootNode = pNewNode;
            }
        }
    }
}

int pushAvlTreeNode(LinkedStack* pStack, AvlTreeNode* data) {
    StackNode node = {0,};
    node.data = data;
    return pushLinkedStack(pStack, node);
}

AvlTreeNode* popAvlTreeNode(LinkedStack* pStack) {
    AvlTreeNode* pReturn = NULL;
    if (isLinkedStackEmpty(pStack) == FALSE) {
        StackNode* pNode = popLinkedStack(pStack);
        if (pNode != NULL) {
            pReturn = pNode->data;
            free(pNode);    // pop 된 노드는 메모리를 해제
        }
    }
    return pReturn;
}

AvlTreeNode* peekAvlTreeNode(LinkedStack* pStack) {
    AvlTreeNode* pReturn = NULL;
    if (isLinkedStackEmpty(pStack) == FALSE) {
        StackNode* pNode = peekLinkedStack(pStack);
        if (pNode != NULL) {
            pReturn = pNode->data;
        }
    }
    return pReturn;
}

/*        [P]               [A]
         /  \               /  \
       [A]   [B]     =>   [C]   [P]
       / \                       / \
     [C]  [D]                  [D] [B]
*/
AvlTreeNode* rotateLLAvlTree(AvlTreeNode* pParentNode) {
    AvlTreeNode* pLeftNode = NULL;
    if (pParentNode != NULL) {
        pLeftNode/*A*/ = pParentNode->pLeftChild;
        pParentNode->pLeftChild = pLeftNode/*A*/->pRightChild/*D*/;
        pLeftNode->pRightChild = pParentNode/*P*/;

        updateHeightAndBalanceAvl(pParentNode);
        updateHeightAndBalanceAvl(pLeftNode);
    }
    return pLeftNode;
}

/*        [P]               [B]
         /  \              /  \
       [A]   [B]     =>  [P]   [D]
             / \         / \
          [C]  [D]     [A] [C]
*/
AvlTreeNode* rotateRRAvlTree(AvlTreeNode* pParentNode) {
    AvlTreeNode* pRightNode = NULL;
    if (pParentNode != NULL) {
        pRightNode/*B*/ = pParentNode->pRightChild;
        pParentNode->pRightChild = pRightNode/*B*/->pLeftChild/*C*/;
        pRightNode->pLeftChild = pParentNode/*P*/;

        updateHeightAndBalanceAvl(pParentNode);
        updateHeightAndBalanceAvl(pRightNode);
    }
    return pRightNode;
}

/*        [P]               [D]
         /  \              /   \
       [A]   [B]     =>  [A]    [P]
       / \               / \    / \
    [C]  [D]           [C] [E][F] [B]
         / \
        [E][F]
*/
AvlTreeNode* rotateLRAvlTree(AvlTreeNode* pParentNode) {
    AvlTreeNode* pReturn = NULL;
    AvlTreeNode* pLeftNode = NULL;

    if (pParentNode != NULL) {
        pLeftNode = pParentNode->pLeftChild;
        pParentNode->pLeftChild = rotateRRAvlTree(pLeftNode); // A에서 RR
        pReturn = rotateLLAvlTree(pParentNode); // P에서 LL
    }
    return pReturn;
}

/*        [P]               [C]
         /  \              /   \
       [A]   [B]     =>  [P]    [B]
             / \         / \    / \
           [C]  [D]    [A] [E][F] [D]
           / \
         [E][F]
*/
AvlTreeNode* rotateRLAvlTree(AvlTreeNode* pParentNode) {
    AvlTreeNode* pReturn = NULL;
    AvlTreeNode* pRightNode = NULL;

    if (pParentNode != NULL) {
        pRightNode = pParentNode->pRightChild;
        pParentNode->pRightChild = rotateLLAvlTree(pRightNode); //  B에서 LL
        pReturn = rotateRRAvlTree(pParentNode); // P에서 RR
    }
    return pReturn;
}

void updateHeightAndBalanceAvl(AvlTreeNode* pNode) {
    int leftHeight = 0;
    int rightHeight = 0;
    if (pNode != NULL) {
        if (pNode->pLeftChild != NULL) {
            leftHeight = pNode->pLeftChild->height;
        }
        if (pNode->pRightChild != NULL) {
            rightHeight = pNode->pRightChild->height;
        }

        if (leftHeight > rightHeight) {
            pNode->height = leftHeight + 1;
        } else {
            pNode->height = rightHeight + 1;
        }
        pNode->balance = leftHeight - rightHeight;
    }
}

int deleteNodeAvl(AvlTree* pAvlTree, int key) {
    int ret = TRUE;
    AvlTreeNode* pDelNode = NULL;
    AvlTreeNode* pParentNode = NULL;

    AvlTreeNode* pPredecessor = NULL;
    AvlTreeNode* pSuccessor = NULL;

    AvlTreeNode* pChild = NULL;
    LinkedStack* pStackMain = NULL;
    LinkedStack* pStackSub = NULL;

    if (pAvlTree == NULL) {
        ret = FALSE;
        return ret;
    }

    // 균형 유지를 위한 스택 생성
    pStackMain = createLinkedStack();
    pStackSub = createLinkedStack();
    if (pStackMain == NULL || pStackSub == NULL) {
        ret = FALSE;
        return ret;
    }

    pParentNode = NULL;
    pDelNode = pAvlTree->pRootNode;
    while (pDelNode != NULL) {
        // 삭제 노드를 찾는 경로에 있는 부모 노드들을 pStackMain 에 저장
        if (key == pDelNode->data.key) {
            break;
        }
        pParentNode = pDelNode;
        pushAvlTreeNode(pStackMain, pParentNode);
        if (key < pDelNode->data.key) {
            pDelNode = pDelNode->pLeftChild;
        } else {
            pDelNode = pDelNode->pRightChild;
        }
    }
    if (pDelNode == NULL) {
        printf("오류, 검색 키[%d]인 자료가 없습니다. deleteNodeAvl()\n", key);
        ret = FALSE;
        return ret;
    }

    if (pDelNode->pLeftChild == NULL && pDelNode->pRightChild == NULL) {
        // 1. 삭제 대상 노드의 자식 노드가 없을 때.
        if (pParentNode != NULL) {
            if (pParentNode->pLeftChild == pDelNode) {
                pParentNode->pLeftChild = NULL;
            } else {
                pParentNode->pRightChild = NULL;
            }
        } else {
            pAvlTree->pRootNode = NULL;
        }
    } else if (pDelNode->pLeftChild != NULL && pDelNode->pRightChild != NULL) {
        // 2. 삭제 대상 노드의 자식 노드가 2개 일 때
        // 추가 스택 pStackSub로 노드 삭제 이후 트리 구조 변경의 균형 유지
        // 삭제 대상 노드를 대체할 노드를 찾아야 함.
        pPredecessor = NULL;
        pSuccessor = pDelNode->pLeftChild;
        pushAvlTreeNode(pStackSub, pSuccessor);

        while (pSuccessor->pRightChild != NULL) {
            pPredecessor = pSuccessor;
            pSuccessor = pSuccessor->pRightChild;
            pushAvlTreeNode(pStackSub, pSuccessor);
        }
        pushAvlTreeNode(pStackMain, popAvlTreeNode(pStackSub));

        if (pPredecessor != NULL) {
            pPredecessor->pRightChild = pSuccessor->pLeftChild;
            pSuccessor->pLeftChild = pDelNode->pLeftChild;
            pushAvlTreeNode(pStackSub, pPredecessor->pRightChild);
        }
        pSuccessor->pRightChild = pDelNode->pRightChild;
        if (pParentNode != NULL) {
            if (pParentNode->pLeftChild == pDelNode) {
                pParentNode->pLeftChild = pSuccessor;
            } else {
                pParentNode->pRightChild = pSuccessor;
            }
        } else {
            pAvlTree->pRootNode = pSuccessor;
        }
    } else {
        // 삭제 대상 노드의 자식 노드가 1개 일 때
        if (pDelNode->pLeftChild != NULL) {
            pChild = pDelNode->pLeftChild;
        } else {
            pChild = pDelNode->pRightChild;
        }

        if (pParentNode != NULL) {
            if (pParentNode->pLeftChild == pDelNode) {
                pParentNode->pLeftChild = pChild;
            } else {
                pParentNode->pRightChild = pChild;
            }
        } else {
            pAvlTree->pRootNode = pChild;
        }
    }
    free(pDelNode);

    // 균형 유지 연산
    balanceAvlTree(pAvlTree, pStackSub);
    balanceAvlTree(pAvlTree, pStackMain);

    // 스택 제거
    deleteLinkedStack(pStackMain);
    deleteLinkedStack(pStackSub);

    return ret;
}

void deleteAvlTree(AvlTree* pAvlTree) {
    if (pAvlTree != NULL) {
        deleteAvlTreeNode(pAvlTree->pRootNode);
        free(pAvlTree);
    }
}

void deleteAvlTreeNode(AvlTreeNode* pAvlTreeNode) {
    if (pAvlTreeNode != NULL) {
        deleteAvlTreeNode(pAvlTreeNode->pLeftChild);
        deleteAvlTreeNode(pAvlTreeNode->pRightChild);
        free(pAvlTreeNode);
    }
}

void displayAvlTree(AvlTree* pTree) {
    displayAvlTreeInternal(pTree->pRootNode, 0, ' ');
}

void displayAvlTreeInternal(AvlTreeNode* pTreeNode, int level, char type) {
    int i = 0;
    for (i = 0 ; i < level ; i++) {
        printf("    ");
    }
    if (pTreeNode != NULL) {
        printf("-[%i, %i, %c], %d-%s\n", pTreeNode->height, pTreeNode->balance,
                type, pTreeNode->data.key, pTreeNode->data.aValue);

        displayAvlTreeInternal(pTreeNode->pLeftChild, level + 1, 'L');
        displayAvlTreeInternal(pTreeNode->pRightChild, level + 1,  'R');
    } else {
        printf("\n");
    }
}









