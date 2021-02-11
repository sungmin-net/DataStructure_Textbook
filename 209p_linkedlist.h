#ifndef _LINKEDLIST_
#define _LINKEDLIST_

typedef struct ListNodeType {
    float coef;
    int degree;
	struct ListNodeType* pLink;
} ListNode;

typedef struct LinkedListType {
	int currentElementCount;	// 현재 저장된 원소의 개수
	ListNode headerNode;		// 헤더 노드
} LinkedList;

LinkedList* createLinkedList();
int addLinkedListElement(LinkedList* pList, int position, ListNode element);
int removeLinkedListElement(LinkedList* pList, int position);
ListNode* getLinkedListElement(LinkedList* pList, int position);
void clearLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);
void deleteLinkedList(LinkedList* pList);
void displayLinkedList(LinkedList* pList);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE	(1)
#define FALSE	(0)
#define FAILED  (-1)

#endif
