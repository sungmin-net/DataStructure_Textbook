#ifndef _CIRCULARLIST_
#define _CIRCULARLIST_

typedef struct CircularListNodeType {
	int data;
	struct CircularListNodeType* pLink;
} CircularListNode;

typedef struct CircularListType {
	int currentElementCount;	// 현재 저장된 원소의 개수
	CircularListNode* pLink;	// 헤드포인터(Head pointer)
} CircularList;

CircularList* createCircularList();
void deleteCircularList(CircularList* pList);
int addCircularListElement(CircularList* pList, int position,
		CircularListNode element);
int removeCircularListElement(CircularList* pList, int position);
void clearCircularList(CircularList* pList);
int getCircularListLength(CircularList* pList);
CircularListNode* getCircularListElement(CircularList* pList, int position);
void displayCircularList(CircularList* pList);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_
#define TRUE	    (1)
#define FALSE	    (0)
#define SUCCEEDED   (1)
#define FAILED      (-1)
#endif
