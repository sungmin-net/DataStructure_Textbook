/*
 * arraylist.h
 *
 *  Created on: 2018. 1. 9.
 *      Author: Sungmin
 */

//전처리
#ifndef _ARRAYLIST_
#define _ARRAYLIST_

// 구조체 선언
typedef struct ArrayListNodeType {
	int data;
} ArrayListNode;

typedef struct ArrayListType {
	int maxElementCount;		// 최대 원소 개수
	int currentElementCount;	// 현재 원소의 개수
	ArrayListNode* pElement;	// 원소 저장을 위한 1차원 배열
} ArrayList;

ArrayList* createArrayList(int mexElementCount);
void deleteArrayList(ArrayList* pList);
int isArrayListFull(ArrayList* pList);
int addArrayListElement(ArrayList* pList, int position, ArrayListNode element);
int removeArrayListElement(ArrayList* pList, int position);
ArrayListNode* getArrayListElement(ArrayList* pList, int position);
void displayArrayList(ArrayList* pList);
void clearArrayList(ArrayList* pList);
int getArrayListLength(ArrayList* pList);

#endif /* ARRAYLIST_H_ */

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_
#define TRUE	1
#define FALSE	0
#endif
