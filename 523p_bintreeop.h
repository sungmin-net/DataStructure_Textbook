#ifndef _BIN_TREE_OPERATION_
#define _BIN_TREE_OPERATION_

BinTree* copyBinTree(BinTree* pSource);
BinTreeNode* copyBinTreeNode(BinTreeNode* pSourceNode);
int isEqualBinTree(BinTree* pFirst, BinTree* pSecond);
int isEqualBinTreeNode(BinTreeNode* pFirst, BinTreeNode* pSecond);
int getNodeCountBinTree(BinTree* pSource);
int getNodeCountBinTreeNode(BinTreeNode* pSource);
int getLeafNodeCountBinTree(BinTree* pSource);
int getLeafNodeCountBinTreeNode(BinTreeNode* pSource);
int getHeightBinTree(BinTree* pSource);
int getHeightBinTreeNode(BinTreeNode* pSource);
void displayBinTree(BinTree* pTree);
void displayBinTreeNode(BinTreeNode* pNode, int level, char type);
#endif
