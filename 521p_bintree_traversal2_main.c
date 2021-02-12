#include <stdio.h>
#include <stdlib.h>
#include "509p_bintree.h"
#include "512p_bintreetraversal.h"

BinTree* createExampleBinTree();

int main(int argc, char* argv[]) {
    BinTree* pBinTree = NULL;
    pBinTree = createExampleBinTree();
    if (pBinTree != NULL) {
        printf("Preorder Traversal\n");
        preorderTraversalBinTree(pBinTree);

        printf("\nInorder Traversal\n");
        inorderTraversalBinTree(pBinTree);

//        printf("\nPostorder Recursive Traversal\n");
//        postorderTraversalBinTree(pBinTree);

        printf("\nLevelorder Traversal\n");
        levelorderTraversalBinTree(pBinTree);

        deleteBinTree(pBinTree);
    }
    return 0;
}

BinTree* createExampleBinTree() {

    BinTreeNode node;
    node.data = 'A';
    BinTree* pBinTree = makeBinTree(node);

    BinTreeNode* pRoot = getRootNodeBinTree(pBinTree);

    node.data = 'B';
    BinTreeNode* pNodeB = insertLeftChildNodeBinTree(pRoot, node);

    node.data = 'C';
    BinTreeNode* pNodeC = insertRightChildNodeBinTree(pRoot, node);

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

    node.data = 'K';
    BinTreeNode* pNodeK = insertRightChildNodeBinTree(pNodeF, node);

    node.data = 'G';
    BinTreeNode* pNodeG = insertRightChildNodeBinTree(pNodeC, node);

    node.data = 'L';
    BinTreeNode* pNodeL = insertLeftChildNodeBinTree(pNodeG, node);

    node.data = 'M';
    BinTreeNode* pNodeM = insertRightChildNodeBinTree(pNodeM, node);

    return pBinTree;
}


