/*
 * arraylist.h
 *
 *  Created on: 2018. 1. 9.
 *      Author: Sungmin
 */

//��ó��
#ifndef _ARRAYLIST_
#define _ARRAYLIST_

// ����ü ����
typedef struct ArrayListNodeType {
	int data;
} ArrayListNode;

typedef struct ArrayListType {
	int maxElementCount;		// �ִ� ���� ����
	int currentElementCount;	// ���� ������ ����
	ArrayListNode* pElement;	// ���� ������ ���� 1���� �迭
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
