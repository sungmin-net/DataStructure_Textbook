#include <stdio.h>
#include <stdlib.h>

#include "955p_btreedef.h"
#include "953p_btree.h"

int main(int argc, char** argv) {
    BTree* pBTree = NULL;
    BTreeNodeData* pSearchElement = NULL;
    int key = 0;

    BTreeNodeData eA = { 9, 'A' };
    BTreeNodeData eB = { 12, 'B' };
    BTreeNodeData eC = { 19, 'C' };
    BTreeNodeData eD = { 39, 'D' };
    BTreeNodeData eE = { 65, 'E' };
    BTreeNodeData eF = { 53, 'F' };
    BTreeNodeData eG = { 63, 'G' };
    BTreeNodeData eH = { 89, 'H' };
    BTreeNodeData eI = { 48, 'I' };
    BTreeNodeData eJ = { 36, 'J' };

    pBTree = createBTree();
    if (pBTree != NULL) {
        insertNodeBTree(pBTree, eA);
        insertNodeBTree(pBTree, eB);
        insertNodeBTree(pBTree, eC);
        insertNodeBTree(pBTree, eD);
        printf("\n01-자료 추가중\n");
        displayBTree(pBTree);

        insertNodeBTree(pBTree, eE);
        printf("\n02-자료 추가중\n");
        displayBTree(pBTree);

        insertNodeBTree(pBTree, eF);
        insertNodeBTree(pBTree, eG);
        insertNodeBTree(pBTree, eH);
        printf("\n03-자료 추가중\n");
        displayBTree(pBTree);

        insertNodeBTree(pBTree, eI);
        insertNodeBTree(pBTree, eJ);

        printf("\n자료 추가가 끝났습니다.\n");
        displayBTree(pBTree);

        deleteNodeBTree(pBTree, 9);
        printf("\n검색키 9가 삭제되었습니다.\n");
        displayBTree(pBTree);

        deleteNodeBTree(pBTree, 89);
        printf("\n검색키 89가 삭제되었습니다.\n");
        displayBTree(pBTree);

        deleteNodeBTree(pBTree, 39);
        printf("\n검색키 39가 삭제되었습니다.\n");
        displayBTree(pBTree);

        deleteNodeBTree(pBTree, 63);
        deleteNodeBTree(pBTree, 53);
        printf("\n검색키 63, 53이 삭제되었습니다.\n");
        displayBTree(pBTree);

        deleteNodeBTree(pBTree, 36);
        printf("\n검색키 36이 삭제되었습니다.\n");
        displayBTree(pBTree);

        key = 19;
        pSearchElement = searchBTree(pBTree, key);
        if (pSearchElement != NULL) {
            printf("검색키-[%d], 결과-[%c]\n", key, pSearchElement->value);
        } else {
            printf("검색키-[%d], 결과 실패\n", key);
        }

        deleteBTree(pBTree);
    }
    return 0;
}

