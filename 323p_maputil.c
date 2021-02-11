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
        pushLinkedStackMapPosition(pStack, newPosition); // 입구 위치를 stack 에 push.
        while (isEmpty == FALSE && isFound == FALSE) { // 움직일 다른 곳이 있고, 아직 출구를 못찾았다면 경로를 계속 찾는다.
            pNode = popLinkedStack(pStack); // 스택에서 위치 정보 및 방향 정보 pop.
            if (pNode != NULL) {
                int x = pNode->data.x;
                int y = pNode->data.y;
                int direction = pNode->data.direction;
                while (isFound == FALSE && direction < NUM_DIRECTIONS) {
                    // 현 위치에서, 아직 가보지 못한(이동 가능한) 방향이 있으면 반복.
                    int newX = x + DIRECTION_OFFSETS[direction][0];
                    int newY = y + DIRECTION_OFFSETS[direction][1];

                    if (newX >= 0 && newX < WIDTH
                            && newY >= 0 && newY < HEIGHT
                            && mazeArray[newY][newX] == NOT_VISIT
                            && markArray[newY][newX] == NOT_VISIT) {
                        // 새로운 방향에 의해 새로운 위치로 이동 가능하면,
                        // 현재의 위치 정보 및 방향 정보를 스택에 push.
                        MapPosition newPosition;
                        newPosition.x = x;
                        newPosition.y = y;
                        newPosition.direction = direction + 1;
                        pushLinkedStackMapPosition(pStack, newPosition);
                        markArray[y][x] = VISIT;

                        x = newX;
                        y = newY;
                        direction = 0;  // 새 위치로 이동, 단 이때 방향 정보는 초기화

                        if (newX == endPos.x && newY == endPos.y) {
                            // 출구를 찾은 경우, 마지막 출구 위치를 스택에 push.
                            isFound = TRUE;
                            newPosition.x = newX;
                            newPosition.y = newY;
                            newPosition.direction = 0;
                            pushLinkedStackMapPosition(pStack, newPosition);
                            markArray[newY][newX] = VISIT;
                        }
                    } else {
                        // 기존의 방향에 의한 새로운 위치로 이동할 수 없다면,
                        // 다른 방향으로 시도해본다.
                        direction++;
                    }
                } // end of while
                free(pNode);
            } // end of if
            isEmpty = isLinkedStackEmpty(pStack); // 더 이상 움질일 위치가 있는 지 점검
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

