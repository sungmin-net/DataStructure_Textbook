#ifndef _AVL_TREE_
#define _AVL_TREE_

typedef struct AvlTreeType {
    AvlTreeNode* pRootNode;
} AvlTree;

AvlTree* createAvlTree();
void deleteAvlTree(AvlTree* pAVLTree);
void deleteAvlTreeNode(AvlTreeNode* pAvlTreeNode);
int insertNodeAvlTree(AvlTree* pAvlTree, AvlTreeNodeData data);
int deleteNodeAvl(AvlTree* pAvlTree, int key);
void balanceAvlTree(AvlTree* pAvlTree, LinkedStack* pStack);
int pushAvlTreeNode(LinkedStack* pStack, AvlTreeNode* data);
AvlTreeNode* popAvlTreeNode(LinkedStack* pStack);
AvlTreeNode* peekAvlTreeNode(LinkedStack* pStack);

AvlTreeNode* rotateLLAvlTree(AvlTreeNode* pParentNode);
AvlTreeNode* rotateLRAvlTree(AvlTreeNode* pParentNode);
AvlTreeNode* rotateRRAvlTree(AvlTreeNode* pParentNode);
AvlTreeNode* rotateRLAvlTree(AvlTreeNode* pParentNode);
void updateHeightAndBalanceAvl(AvlTreeNode* pNode);
AvlTreeNode* searchAvl(AvlTree* pAvlTree, int key);

void displayAvlTree(AvlTree* pTree);
void displayAvlTreeInternal(AvlTreeNode* pTreeNode, int level, char type);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE        1
#define FALSE       0

#endif
