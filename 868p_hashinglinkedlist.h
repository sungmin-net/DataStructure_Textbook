#ifndef _LINKED_LIST_
#define _LINKED_LIST_

typedef struct ListNodeType {
    HashElement data;
    struct ListNodeType* pLink;
} ListNode;

typedef struct LinkedListType {
    int currentElementCount;
    ListNode headerNode;
} LinkedList;

LinkedList* createLinkedList();
int addElementLinkedList(LinkedList* pList, int position, ListNode element);
int removeElementLinkedList(LinkedList* pList, int position);
ListNode* getElementLinkedList(LinkedList* pList, int position);

void clearLinkedList(LinkedList* pList);
int getLengthLinkedList(LinkedList* pList);
void deleteLinkedList(LinkedList* pList);
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE        1
#define FALSE       0

#endif
