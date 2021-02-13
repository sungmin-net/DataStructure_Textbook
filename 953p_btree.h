#ifndef _B_TREE_
#define _B_TREE_

typedef struct BTreeType {
    BTreeNode* pRootNode;
} BTree;

BTree* createBTree();
BTreeNode* createBTreeNode(BTreeNodeData element);
void deleteBTree(BTree* pBTree);
void deleteBTreeNode(BTreeNode* pBTreeNode);
int insertNodeBTree(BTree* pBTree, BTreeNodeData element);
void insertNodeElementBTree(BTreeNode* pCurrentNode, BTreeNodeData element,
        BTreeNode* pRightChildNode);
void splitNodeBTree(BTree* pBTree, struct LinkedStackType* pStack);

int deleteNodeBTree(BTree* pBTree, int key);
int isLeafNode(BTreeNode* pRarentNode);
BTreeNode* replaceLeafNodeBTree(BTree *pBTree, BTreeNode* pDelNode, int index,
        struct LinkedStackType* pStack);
void deleteKeyBTree(BTreeNode* pNode, int index);
void balanceBTree(BTree* pBTree, struct LinkedStackType* pStack);
int getIndexInfo(BTreeNode* pParentNode, BTreeNode* pCurrentNode);
void borrowRightNodeBTree(BTreeNode* pParentNode, BTreeNode* pCurrentNode,
        int index, BTreeNode* pRightNode);
void borrowLeftNodeBTree(BTreeNode* pParentNode, BTreeNode* pCurrentNode,
        int index, BTreeNode* pLeftNode);
void mergeNodeBTree(BTree* pBTree, struct LinkedStackType* pStack,
        BTreeNode* pParentBTreeNode, BTreeNode* pCurrentBTreeNode,
        int index);
BTreeNodeData* searchBTree(BTree* pBTree, int key);
void displayBTree(BTree* pTree);
void displayBTreeNode(BTreeNode* pNode);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE        1
#define FASLE       0

#endif
