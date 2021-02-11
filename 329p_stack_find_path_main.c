#include <stdio.h>
#include <stdlib.h>

#include "318p_mapdef.h"
#include "322p_maplinkedstack.h"
#include "323p_maputil.h"

int main(int argc, char* argv[]) {
    LinkedStack* pStack = NULL;
    MapPosition startPos;
    MapPosition endPos;

    int mazeArray[HEIGHT][WIDTH] = {
            {0, 0, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 0}
    };

    // 스택 생성
    pStack = createLinkedStack();
    if (pStack != NULL) {
        startPos.x = 0;
        startPos.y = 0;
        endPos.x = 7;
        endPos.y = 7;

        printMaze(mazeArray);

        findPath(mazeArray, startPos, endPos, pStack);
        showPath(pStack, mazeArray);
        deleteLinkedStack(pStack);
    }
    return 0;
}

