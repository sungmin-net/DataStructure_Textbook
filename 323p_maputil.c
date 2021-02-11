#include <stdio.h>
#include <stdlib.h>
#include "318p_mapdef.h"
#include "322p_maplinkedstack.h"
#include "323p_maputil.h"

int pushLinkedStackMapPosition(LinkedStack* pStack, MapPosition data) {
    StackNode node = {0,};
    node.data = data;
    return pushLinkedStack(pStack, node);
}

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos,
        MapPosition endPos, LinkedStack* pStack) {
    StackNode* pNode = NULL;
    int isEmpty = FALSE;
    int isFound = FALSE;
    int markArray[HEIGHT][WIDTH] = {0,};

    if (pStack != NULL) {
        MapPosition newPosition = startPos;
        newPosition.direction = 0;
        pushLinkedStackMapPosition(pStack, newPosition); // �Ա� ��ġ�� stack �� push.
        while (isEmpty == FALSE && isFound == FALSE) { // ������ �ٸ� ���� �ְ�, ���� �ⱸ�� ��ã�Ҵٸ� ��θ� ��� ã�´�.
            pNode = popLinkedStack(pStack); // ���ÿ��� ��ġ ���� �� ���� ���� pop.
            if (pNode != NULL) {
                int x = pNode->data.x;
                int y = pNode->data.y;
                int direction = pNode->data.direction;
                while (isFound == FALSE && direction < NUM_DIRECTIONS) {
                    // �� ��ġ����, ���� ������ ����(�̵� ������) ������ ������ �ݺ�.
                    int newX = x + DIRECTION_OFFSETS[direction][0];
                    int newY = y + DIRECTION_OFFSETS[direction][1];

                    if (newX >= 0 && newX < WIDTH
                            && newY >= 0 && newY < HEIGHT
                            && mazeArray[newY][newX] == NOT_VISIT
                            && markArray[newY][newX] == NOT_VISIT) {
                        // ���ο� ���⿡ ���� ���ο� ��ġ�� �̵� �����ϸ�,
                        // ������ ��ġ ���� �� ���� ������ ���ÿ� push.
                        MapPosition newPosition;
                        newPosition.x = x;
                        newPosition.y = y;
                        newPosition.direction = direction + 1;
                        pushLinkedStackMapPosition(pStack, newPosition);
                        markArray[y][x] = VISIT;

                        x = newX;
                        y = newY;
                        direction = 0;  // �� ��ġ�� �̵�, �� �̶� ���� ������ �ʱ�ȭ

                        if (newX == endPos.x && newY == endPos.y) {
                            // �ⱸ�� ã�� ���, ������ �ⱸ ��ġ�� ���ÿ� push.
                            isFound = TRUE;
                            newPosition.x = newX;
                            newPosition.y = newY;
                            newPosition.direction = 0;
                            pushLinkedStackMapPosition(pStack, newPosition);
                            markArray[newY][newX] = VISIT;
                        }
                    } else {
                        // ������ ���⿡ ���� ���ο� ��ġ�� �̵��� �� ���ٸ�,
                        // �ٸ� �������� �õ��غ���.
                        direction++;
                    }
                } // end of while
                free(pNode);
            } // end of if
            isEmpty = isLinkedStackEmpty(pStack); // �� �̻� ������ ��ġ�� �ִ� �� ����
        } // end of while
    }
}

void showPath(LinkedStack* pStack, int mazeArray[HEIGHT][WIDTH]) {
    printf("showPath() started.\n");
    fflush(stdout);
    StackNode* pNode = NULL;
    int resultArray[HEIGHT][WIDTH] = {0,};
    int isEmpty = FALSE;

    int i = 0;
    int j = 0;
    for (i = 0 ; i < HEIGHT ; i++) {
        for (j = 0 ; j < WIDTH ; j++) {
            resultArray[i][j] = mazeArray[i][j];
        }
    }

    if (pStack != NULL) {
        i = 0;
        while (isEmpty == FALSE) {
            pNode = popLinkedStack(pStack);
            if (pNode != NULL) {
                int x = pNode->data.x;
                int y = pNode->data.y;
                resultArray[y][x] = VISIT;

                if (i > 0) {
                    printf("<-");
                }
                printf("(%d,%d) ", x, y);
                fflush(stdout);
                i++;
                free(pNode);
            }
            isEmpty = isLinkedStackEmpty(pStack);
        }
        printf("\n");
        fflush(stdout);
        printMaze(resultArray);
    }
}

void printMaze(int mazeArray[HEIGHT][WIDTH]) {
    printf("printMaze() started.\n");
    fflush(stdout);
    int i;
    int j;
    for (i = 0 ; i < HEIGHT ; i++) {
        for (j = 0 ; j < WIDTH ; j++) {
            if (mazeArray[i][j] == WALL) {
                printf("*");
            } else if (mazeArray[i][j] == VISIT) {
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("\n");
        fflush(stdout);
    }
}

