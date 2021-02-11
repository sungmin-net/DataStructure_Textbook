#ifndef _POLYLIST_
#define _POLYLIST_

int addPolyNodeLast(LinkedList* pList, float coef, int dgree);
LinkedList* polyAdd(LinkedList* pListA, LinkedList* pListB);
LinkedList* polySub(LinkedList* pListA, LinkedList* pListB);
void displayPolyList(LinkedList* pList);

#endif
