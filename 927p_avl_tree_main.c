#include <stdio.h>
#include <stdlib.h>

#include "906p_avldef.h"
#include "908p_avllinkedstack.h"
#include "908p_avltree.h"

int main(int argc, char** argv) {
    AvlTree* pTree = NULL;

    AvlTreeNodeData eB = {9, "키 값이 9"};
    AvlTreeNodeData eG = {3, "키 값이 3"};
    AvlTreeNodeData eE = {1, "키 값이 1"};
    AvlTreeNodeData eC = {10, "키 값이 10"};
    AvlTreeNodeData eL = {12, "키 값이 12"};
    AvlTreeNodeData eH = {6, "키 값이 6"};
    AvlTreeNodeData eI = {4, "키 값이 4"};
    AvlTreeNodeData eF = {5, "키 값이 5"};

    pTree = createAvlTree();
    if (pTree != NULL) {
        printf("1)\n");
        insertNodeAvl(pTree, eB);
        displayAvlTree(pTree);

        printf("\n2)\n");
        insertNodeAvl(pTree, eG);
        displayAvlTree(pTree);

        printf("\n3) LL 회전 발생\n");
        insertNodeAvl(pTree, eE);
        displayAvlTree(pTree);

        printf("\n4)\n");
        insertNodeAvl(pTree, eC);
        displayAvlTree(pTree);

        printf("\n5) RR 회전 발생\n");
        insertNodeAvl(pTree, eL);
        displayAvlTree(pTree);

        printf("\n6) RL 회전 발생\n");
        insertNodeAvl(pTree, eH);
        displayAvlTree(pTree);

        printf("\n7)\n");
        insertNodeAvl(pTree, eI);
        displayAvlTree(pTree);

        printf("\n8) LR 회전 발생\n");
        insertNodeAvl(pTree, eF);
        displayAvlTree(pTree);

        deleteAvlTree(pTree);
    }
    return 0;
}

