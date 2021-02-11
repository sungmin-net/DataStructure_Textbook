#include <stdio.h>
#include <stdlib.h>

#include "480p_bintree.h"

int main(int argc, char** argv) {
    BinTree* pBinTree = NULL;
    BinTreeNode* pNodeA = NULL;
    BinTreeNode* pNodeB = NULL;
    BinTreeNode* pNodeC = NULL;
    BinTreeNode* pNodeD = NULL;
    BinTreeNode* pNodeE = NULL;
    BinTreeNode* pNodeF = NULL;
    BinTreeNode node = {0,};
    node.data = 'A';
    pBinTree = makeBinTree(node);
    if (pBinTree != NULL) {
        pNodeA = getRootNodeBinTree(pBinTree);

        node.data = 'B';
        pNodeB = insertLeftChildNodeBinTree(pNodeA, node);

        node.data = 'C';
        pNodeC = insertRightChildNodeBinTree(pNodeA, node);

        if (pNodeB != NULL) {
            node.data = 'D';
            pNodeD = insertLeftChildNodeBinTree(pNodeB, node);
        }

        if (pNodeC != NULL) {
            node.data = 'E';
            pNodeE = insertLeftChildNodeBinTree(pNodeC, node);
            node.data = 'F';
            pNodeF = insertRightChildNodeBinTree(pNodeC, node);
        }
        deleteBinTree(pBinTree);
    }
    return 0;
}
