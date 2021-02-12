#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "708p_graphlinkedlist.h"

LinkedList* createLinkedList() {
	LinkedList* pReturn = NULL;
	pReturn = (LinkedList*)malloc(sizeof(LinkedList));	// 메모리할당
	if (pReturn != NULL) {	// 메모리 할당 점검
		memset(pReturn, 0, sizeof(LinkedList));	// 할당된 메모리 초기화
	} else {
		printf("오류, 메모리 할당 createLinkedList()\n");
		return NULL;
	}
	return pReturn;
}

int addLinkedListElement(LinkedList* pList, int position, ListNode element) {
	int ret = FALSE;
	int i = 0;
	ListNode* pPreNode = NULL;
	ListNode* pNewNode = NULL;
	if (pList != NULL) {
		if (position >= 0 && position <= pList->currentElementCount) {
			pNewNode = (ListNode*)malloc(sizeof(ListNode));
			if (pNewNode != NULL) {
				*pNewNode = element;	// 노드값 설정
				pNewNode->pLink = NULL;	// 링크 초기화
				pPreNode = &(pList->headerNode);
				for (i = 0 ; i < position ; i++) {	// 노드가 추가될 위치로 이동
					pPreNode = pPreNode->pLink;
				}
				pNewNode->pLink = pPreNode->pLink;	// 추가된 노드와 기존 노드 사이의 링크 재설정
				pPreNode->pLink = pNewNode;
				pList->currentElementCount++;
				ret = TRUE;
			} else {
				printf("오류, 메모리할당 addLinkedListElement()\n");
				return ret;
			}
		} else {
			printf("오류, 위치 인덱스-[%d], addLinkedListElement()\n",
					position);
		}
	}
	return ret;
}


int removeLinkedListElement(LinkedList* pList, int position) {
	int ret = FALSE;
	int i = 0;
	int arrayCount = 0;
	ListNode* pNode = NULL;
	ListNode* pDelNode = NULL;
	if (pList != NULL) {
		arrayCount = getLinkedListLength(pList);
		if (position >= 0 && position < arrayCount) {
			pNode = &(pList->headerNode);
			for (i = 0 ; i < position ; i++) {
				pNode = pNode->pLink;
			}	// pNode 는 제거할 노드의 바로 이전 노드

			pDelNode = pNode->pLink;	// 제거할 노드
			pNode->pLink = pDelNode->pLink;	// 제거할 노드와 기존 노드 사이의 링크 재설정
			free(pDelNode);	// 제거할 노드 메모리 해제
			pList->currentElementCount--;	// 현재 노드 개수 1 감소
			ret = TRUE;
		} else {
			printf("오류, 위치 인덱스-[%d] removeLinkedListElement()\n", position);
		}
	}
	return ret;
}

ListNode* getLinkedListElement(LinkedList* pList, int position) {
	ListNode* pReturn = NULL;
	int i = 0;
	ListNode* pNode = NULL;
	if (pList != NULL) {
		if (position >= 0 && position < pList->currentElementCount) {
			pNode = &(pList->headerNode);
			for (i = 0 ; i <= position ; i++) {
				pNode = pNode->pLink;
			}
			pReturn = pNode;
		}
	}
	return pReturn;
}

void deleteLinkedList(LinkedList* pList) {
	if (pList != NULL) {
		clearLinkedList(pList);
		free(pList);
	}
}

void clearLinkedList(LinkedList* pList) {
	if (pList != NULL) {
		if (pList->currentElementCount > 0) {
			removeLinkedListElement(pList, 0);
		}
	}
}

int getLinkedListLength(LinkedList* pList) {
	int ret = 0;
	if (pList != NULL) {
		ret = pList -> currentElementCount;
	}
	return ret;
}

int isEmpty(LinkedList* pList) {
	int ret = FALSE;

	if (pList != NULL) {
		if (pList->currentElementCount == 0) {
			ret = TRUE;
		}
	}

	return ret;
}
