#ifndef _AVL_DEF_
#define _AVL_DEF_

#define VALUE_SIZE      100
typedef struct AvlTreeNodeDataType {
    int key;
    char aValue[ VALUE_SIZE + 1];
} AvlTreeNodeData;

typedef struct AvlTreeNodeType {
    AvlTreeNodeData data;
    int balance;
    int height;
    struct AvlTreeNodeType* pLeftChild;
    struct AvlTreeNodeType* pRightChild;
} AvlTreeNode;

#endif
