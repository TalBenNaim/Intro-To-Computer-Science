#include "ex_4.c"
#include "ex_4.h"

int main() {

    char board[ROWS][COLS];
    initBoard(board, ROWS, COLS);

    printBoard(board, ROWS, COLS);

    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'A', 0);
    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'B', 2);
    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'B', 5);
    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'B', 3);
    printBoard(board, ROWS, COLS);

    int horizontal = horizontalConnect(board, ROWS, COLS, 'B', 2);
    int vertical = verticalConnect(board, ROWS, COLS, 'B', 2);

    printf("%d\n", horizontal);
    printf("%d\n", vertical);
}
