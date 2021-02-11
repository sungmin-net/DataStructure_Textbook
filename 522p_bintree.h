#ifndef _BIN_TREE_
#define _BIN_TREE_

typedef struct BinTreeNodeType {
    char data;
    int visited;
    struct BinTreeNodeType* pLeftChild;
    struct BinTreeNodeType* pRightChild;
} BinTreeNode;

typedef struct BinTreeType {
    struct BinTreeNodeType* pRootNode;
} BinTree;

BinTree* makeBinTree(BinTreeNode rootNode);
BinTreeNode* getRootNodeBinTree(BinTree* pBinTree);
BinTreeNode* insertLeftChildNodeBinTree(BinTreeNode* pParentNode,
        BinTreeNode element);
BinTreeNode* insertRightChildNodeBinTree(BinTreeNode* pParentNode,
        BinTreeNode element);
BinTreeNode* getLeftChildNodeBinTree(BinTreeNode* pNode);
BinTreeNode* getRightChildNodeBinTree(BinTreeNode* pNode);
void deleteBinTree(BinTree* pBinTree);
void deleteBinTreeNode(BinTreeNode* pNode);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE    1
#define FALSE   0

#endif

