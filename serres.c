#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KWHT  "\x1B[37m"
#define KBLD  "\x1B[1m"

char *array[] = {
    "     S   ",
    "    SE   ",
    "   SERRES",
    "  SERRES ",
    " SERRES  ",
    "SERRES   ",
    "   ES    ",
    "   S     "
};
#define ROWS 8
#define COLS 9
char const *target = "SERRES";

struct cell {
    int x;
    int y;
} path[6];  // 6 = strlen(target)

int xyWithinBounds(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS);
}

int xyNotInCurPath(int x, int y, int pathlen) {
    int i;
    for (i = 0; i < pathlen; i++) {
        if (path[i].x == x && path[i].y == y) {
            return 0;
        }
    }
    return 1;
}

void printMatch() {
    int i, j;
    static int match = 0;

    printf("%d:\n", ++match);
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (!xyNotInCurPath(i, j, strlen(target))) {
                if (path[0].x == i && path[0].y == j) {
                    printf("%s%s%c%s", KBLD, KRED, array[i][j], KNRM);  // Print first letter with red
                } else if (path[strlen(target)-1].x == i && path[strlen(target)-1].y == j) {
                    printf("%s%s%c%s", KBLD, KBLU, array[i][j], KNRM);  // Print last letter with blue
                } else {
                    printf("%s%s%c%s", KBLD, KMAG, array[i][j], KNRM);  // Print rest path letters with magenta
                }
            } else {
                //printf("%c", array[i][j]);  // Print non-matching letters
                printf("%s%c%s", KWHT, array[i][j], KNRM);  // Print rest path letters with magenta
            }
        }
        printf("\n");
    }
    printf("\n");
}

void checkNext(int x, int y, int pathlen) {
    if (xyWithinBounds(x, y) && xyNotInCurPath(x, y, pathlen) 
          && array[x][y] == target[pathlen]) {
        // Found a character match
        path[pathlen].x = x;
        path[pathlen].y = y;
        pathlen++;

        if (pathlen == strlen(target)) {
            printMatch();
            return;
        }

        checkNext(x - 1,   y  , pathlen);
        checkNext(  x  , y - 1, pathlen);
        checkNext(  x  , y + 1, pathlen);
        checkNext(x + 1,   y  , pathlen);
    }
}

int main(void) {
    int i, j;

    printf("%s%sRed color%s: begin, %s%sBlue color%s: end.\n\n", KBLD, KRED, KNRM, KBLD, KBLU, KNRM);
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            checkNext(i, j, 0);
        }
    }
    printf("%s", KNRM); // Reset terminal color

    return 0;
}

