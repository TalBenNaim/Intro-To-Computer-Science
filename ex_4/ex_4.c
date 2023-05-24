// (89110, Spring 2023, Assignment #3, Tal Ben Naim, 212749071, bennait3)

#include "ex_4.h"

// helper functions declaration
int playerInRange(int players, int player);

int colInColumnsRange(int column, int columns);

int getLowestEmptyRow(char board[ROWS][COLS], int column, int rows);

int horizontalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int verticalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

/**
 * @brief This function initialize the board to the default state - every cell in the board is empty.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 */
void initBoard(char board[ROWS][COLS], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }
}

/**
 * @brief This function print the given board board, with two ~ lines, one at the start and one at the end.
 * Between those ~ lines we are printing the content of each cell in the board each cell have || around it.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 */
void printBoard(char board[ROWS][COLS], int rows, int columns) {

    // print the first row of ~ (2 * columns) + 1 times

    for (int i = 0; i < (2 * columns) + 1; i++) {
        printf("%c", '~');
    }

    // go down a line
    printf("\n");

    // go through all the rows
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < columns; j++) {

            // print | before each cell
            printf("%c", '|');

            // print the content of the cell
            printf("%c", board[i][j]);
        }

        // print the last | and go down a line between each row print
        printf("|\n");
    }

    // print the last row of ~ (2 * (columns + 1)) times

    for (int i = 0; i < (2 * columns) + 1; i++) {
        printf("%c", '~');
    }

    // go down a line
    printf("\n");
}

/**
 * @brief This function, make a move for the player.
 * The move is described as taking his name and putting it down the given column.
 * The char will "fall" and be put in the lowest empty row in t he column.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param players the amount of players playing the game.
 * @param player the player making the move.
 * @param column the column to make the move on.
 *
 * @return 0 if the move isn't allowed, and 1 if it is.
 */
int makeMove(char board[ROWS][COLS], int rows, int columns, int players, char player, int column) {
    // check if the given player is in the players range.
    int isInPlayerRange = playerInRange(players, player);

    // check if the given column is in the columns range.
    int isInColRange = colInColumnsRange(column, columns);

    // get the lowest empty row of the column.
    int lowestEmptyRow = getLowestEmptyRow(board, column, rows);

    /*
    if one of the checks doesn't pass, return 0 (we can't do the move)
    (if the lowestEmptyRow == columns that mean the whole column is full).
    */
    if (isInColRange == 0 || isInPlayerRange == 0 || lowestEmptyRow == -1) {
        return 0;

    } else {

        // insert the actual player name in the correct place on the board
        board[lowestEmptyRow][column] = player;
        return 1;
    }
}

/**
 * @brief This function, undo a move. That means, taking out the lowestOccupied cell in the given col.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param column the column to undo the move on.
 *
 * @return 0 if the move isn't allowed, and 1 if it is.
 */
int undoMove(char board[ROWS][COLS], int rows, int columns, int column) {
    // check if the given column is in the columns range.
    int isInColRange = colInColumnsRange(column, columns);

    // get the lowest empty row of the column.
    int lowestEmptyRow = getLowestEmptyRow(board, column, rows);

    /*
    if one of the checks doesn't pass, return 0 (we can't do the move).
    (if the lowestEmptyRow == columns that mean the whole column is empty).
    */
    if (isInColRange == 0 || lowestEmptyRow == columns) {
        return 0;
    } else {
        // move down one row to the lowestOccupied cell.
        int lowestOccupied = lowestEmptyRow + 1;

        // clear the lowestOccupiedCell
        board[lowestOccupied][column] = ' ';
        return 1;
    }
}

/*
int getStatus(char board[ROWS][COLS], int rows, int columns, int players, int connect) {

}

*/
/*
char getWinner(char board[ROWS][COLS], int rows, int columns, int players, int connect) {
}
*/
/*
int isValidBoard(char board[ROWS][COLS], int rows, int columns, int players, int connect) {
}

void encode(const char board[ROWS][COLS], int rows, int columns, char *code) {
}

void decode(const char *code, char board[ROWS][COLS]){}
*/

// helper functions

/**
 * @brief This function check if the player is in the given players range. (represent by A - Z)
 *
 * @param players The amount of players to get the range.
 * @param player The player to check.
 *
 * @return 1 if the player is in the range, 0 the player is not in the range.
 */
int playerInRange(int players, int player) {
    // if the player is between the first character, A. and the last Character (depend on the players.)
    if ((player >= 'A') && (player <= 'A' + (players - 1))) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief This function check if the given column is between  0 - columns.
 *
 * @param column The columns to check if between 0 - columns.
 * @param columns The amount of columns.
 *
 * @return 1 if the column is in the range, 0 the column is not in the range.
 */
int colInColumnsRange(int column, int columns) {
    // check if the column is between 0 - columns
    if (column >= 0 && column < columns) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief This function get the lowest empty row in a given column.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param column the number column to check.
 * @param rows the number of rows in the board.
 *
 * @return the lowestEmptyRow, it will be -1 if the given column is full.
 */
int getLowestEmptyRow(char board[ROWS][COLS], int column, int rows) {
    // starting value, -1 never will be a location, and is useful for undo move.
    int lowestEmptyRow = -1;

    // go on the every row in the col, and set it to the lowestEmptyRow the last one set will be the lowest.
    for (int i = 0; i < rows; i++) {
        if (board[i][column] == ' ') {
            lowestEmptyRow = i;
        }
    }

    return lowestEmptyRow;
}

int horizontalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect) {
    int counter = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            if (board[i][j] == player) {
                counter++;
                if (counter == connect) {
                    return 1;
                }
            } else {
                counter = 0;
            }
        }
    }

    return 0;
}

int verticalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect) {
    int counter = 0;

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {

            if (board[j][i] == player) {
                counter++;
                if (counter == connect) {
                    return 1;
                }
            } else {
                counter = 0;
            }
        }
    }

    return 0;
}