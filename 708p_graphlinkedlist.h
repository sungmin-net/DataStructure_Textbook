#ifndef _GRAPH_LINKEDLIST_
#define _GRAPH_LINKEDLIST_

typedef struct GraphVertexType {
    int vertexId;
    int weight;
} GraphVertex;

typedef struct ListNodeType {
    GraphVertex data;
	struct ListNodeType* pLink;
} ListNode;

typedef struct LinkedListType {
    int currentElementCount;
    ListNode headerNode;
} LinkedList;

LinkedList* createLinkedList();
int addLinkedListElement(LinkedList* pList, int position, ListNode element);
int removeLinkedListElement(LinkedList* pList, int position);
ListNode* getLinkedListElement(LinkedList* pList, int position);
void clearLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);
void deleteLinkedList(LinkedList* pList);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE	1
#define FALSE	0

#endif
