#include "ex_4.c"
#include "ex_4.h"

int main() {

    char board[ROWS][COLS];
    initBoard(board, ROWS, COLS);

    printBoard(board, ROWS, COLS);

    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'A', 3);
    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'B', 3);
    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'A', 0);
    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'B', 1);
    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'A', 3);
    makeMove(board, ROWS, COLS, NUM_PLAYERS, 'B', 2);
    undoMove(board, ROWS, COLS, 3);
    undoMove(board, ROWS, COLS, 3);

    printBoard(board, ROWS, COLS);

    int status = getStatus(board, ROWS, COLS, NUM_PLAYERS, CONNECT);
    if (status == 1) {
        printf("Game-over\n");
    } else if (status == 0) {
        printf("Tie\n");
    } else if (status == -1) {
        printf("Game is in progress\n");
    } else {
        printf("Invalid return value from getStatus(...)\n");
    }

    char winner = getWinner(board, ROWS, COLS, NUM_PLAYERS, CONNECT);
    if (winner == -1) {
        printf("No winner\n");
    } else {
        printf("Winner is '%c'\n", winner);
    }

    int valid = isValidBoard(board, ROWS, COLS, NUM_PLAYERS, CONNECT);
    if (valid) {
        printf("Board is valid\n");
    } else {
        printf("Board is invalid\n");
    }

    char code[ROWS * COLS + 1];
    encode(board, ROWS, COLS, code);
    printf("Encoded board: '%s'\n", code);

    char newBoard[ROWS][COLS];
    decode(code, newBoard);
    printBoard(newBoard, ROWS, COLS);

    char board2[ROWS][COLS] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', 'A', ' ', ' ', ' ', ' '},
        {' ', ' ', 'B', ' ', ' ', ' ', ' '}, {' ', ' ', 'A', ' ', ' ', ' ', ' '}, {' ', ' ', 'B', ' ', ' ', ' ', ' '},
    };

    printBoard(board2, ROWS, COLS);
}
