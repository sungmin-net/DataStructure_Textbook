#include <stdio.h>
#include <stdlib.h>

#include "522p_bintree.h"
#include "523p_bintreeop.h"

BinTree* createExampleBinTree();

int main(int argc, char* argv[]) {
    int compareResult = FALSE;
    int count = 0;
    BinTree* pBinTree = NULL;
    BinTree* pCopyBinTree = NULL;

    pBinTree = createExampleBinTree();
    printf("���� Ʈ�� ���� :\n");
    displayBinTree(pBinTree);

    pCopyBinTree = copyBinTree(pBinTree);
    printf("���� Ʈ�� ���纻 :\n");
    displayBinTree(pCopyBinTree);

    compareResult = isEqualBinTree(pBinTree, pCopyBinTree);
    printf("\n���� Ʈ�� �� ��� : (%s)\n", compareResult ? "TRUE" : "FALSE");

    count = getNodeCountBinTree(pBinTree);
    printf("\n���� Ʈ�� ��� ���� : %d\n", count);

    count = getLeafNodeCountBinTree(pBinTree);
    printf("\n���� Ʈ�� �ܸ� ��� ���� : %d\n", count);

    count = getHeightBinTree(pBinTree);
    printf("\n���� Ʈ���� ���� : %d\n", count);

    deleteBinTree(pBinTree);
    deleteBinTree(pCopyBinTree);
    return 0;
}

BinTree* createExampleBinTree() {
    BinTree* pReturn = NULL;
    BinTreeNode node = {0,};
    node.data = 'A';
    pReturn = makeBinTree(node);

    node.data = 'B';
    BinTreeNode* pNodeB = insertLeftChildNodeBinTree(pReturn->pRootNode, node);

    node.data = 'C';
    BinTreeNode* pNodeC = insertRightChildNodeBinTree(pReturn->pRootNode, node);

    node.data = 'D';
    BinTreeNode* pNodeD = insertLeftChildNodeBinTree(pNodeB, node);

    node.data = 'E';
    BinTreeNode* pNodeE = insertRightChildNodeBinTree(pNodeB, node);

    node.data = 'H';
    BinTreeNode* pNodeH = insertLeftChildNodeBinTree(pNodeD, node);

    node.data = 'I';
    BinTreeNode* pNodeI = insertRightChildNodeBinTree(pNodeD, node);

    node.data = 'J';
    BinTreeNode* pNodeJ = insertLeftChildNodeBinTree(pNodeE, node);

    node.data = 'F';
    BinTreeNode* pNodeF = insertLeftChildNodeBinTree(pNodeC, node);

    node.data = 'G';
    BinTreeNode* pNodeG = insertRightChildNodeBinTree(pNodeC, node);

    node.data = 'K';
    BinTreeNode* pNodeK = insertRightChildNodeBinTree(pNodeF, node);

    node.data = 'L';
    BinTreeNode* pNodeL = insertLeftChildNodeBinTree(pNodeG, node);

    node.data = 'M';
    BinTreeNode* pNodeM = insertRightChildNodeBinTree(pNodeG, node);
    return pReturn;
}
