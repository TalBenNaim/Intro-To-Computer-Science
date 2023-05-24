// (89110, Spring 2023, Assignment #3, Tal Ben Naim, 212749071, bennait3)

#include "ex_4.h"

// helper functions declaration
int playerInRange(int players, int player);

int numberInRange(int number, int numbers);

int getLowestEmptyRow(char board[ROWS][COLS], int column, int rows);

int horizontalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int verticalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int rightDownDiagConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int checkAllDiagConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int diagConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect, int rowInc, int colInc);

char getPlayerFromNum(int playerNumber);

int aDraw(char board[ROWS][COLS], int rows, int columns, int players, int connect);

int haveWin(char board[ROWS][COLS], int rows, int columns, char player, int connect);

// the main functions.

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
    int isInColRange = numberInRange(column, columns);

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
    int isInColRange = numberInRange(column, columns);

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

/**
 * @brief This function gets a board and get the status.
 * status can be the following:
 * 1 - the game is ended and there is a winner.
 * 0 - there is a draw.
 * -1 - the game still going.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param players the amount of players playing the game.
 * @param connect the connect that is considered as a win
 *
 * @return the status, 1 - game ended with a winner, 0 - there is a draw, -1 - the game still going.
 */
int getStatus(char board[ROWS][COLS], int rows, int columns, int players, int connect) {
    // check if there is a single winner
    if (getWinner(board, rows, columns, players, connect) == 1) {
        // return 1 as for the status, the game ended there is winner.
        return 1;
    }

    // check if there is a draw state
    if (aDraw(board, rows, columns, players, connect) == 1) {
        // return 0 as for the status, the game ended there is a draw.
        return 0;
    }

    // if there ins't a draw, or winner, the game is still going, return -1.
    return -1;
}

/**
 * @brief This function gets a board and get the winner if there is one
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param players the amount of players playing the game.
 * @param connect the connect that is considered as a win
 *
 * @return the winner if there is one else, return -1 meaning that there is no winner.
 */
char getWinner(char board[ROWS][COLS], int rows, int columns, int players, int connect) {

    // count the winners.
    int winners = 0;

    // save the winner
    char theWinner = ' ';

    // loop through the players
    for (int i = 0; i < players; i++) {

        // check for each iteration if i is a winner
        int aWinner = haveWin(board, rows, columns, getPlayerFromNum(i), connect);

        // if he is, add to the winners and save him.
        if (aWinner == 1) {
            winners++;
            theWinner = getPlayerFromNum(i);
        }
    }

    // only when winner is 1 we will return theWinner as it will be assigned only once.
    if (winners == 1) {
        return theWinner;

        // no winner? return -1;
    } else {
        return -1;
    }
}

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
 * @brief This function check if the given number is between  0 - numbers.
 *
 * @param number The number to check if between 0 - numbers.
 * @param numbers The numbers range.
 *
 * @return 1 if the number is in the range, 0 the number is not in the range.
 */
int numberInRange(int number, int numbers) {
    // check if the number is between 0 - numbers
    if (number >= 0 && number < numbers) {
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
        // if the cell is empty, save the row index of the cell.
        if (board[i][column] == ' ') {
            lowestEmptyRow = i;
        }
    }

    return lowestEmptyRow;
}

/**
 * @brief This function check if the player have an horizontal connect on the given board.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param player the player we are checking
 * @param connect the connect that is considered as a win
 *
 * @return 1 if there is a connect, 0 if there isn't a connect.
 */
int horizontalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect) {
    // counter to count occurrences in horizontal
    int counter = 0;

    // loop through the rows
    for (int i = 0; i < rows; i++) {
        // for each row, loop through the columns, creating horizontal look.
        for (int j = 0; j < columns; j++) {
            // if we find our player
            if (board[i][j] == player) {
                // the player appear so we add
                counter++;

                // once the counter == connect we made a connect
                if (counter == connect) {
                    return 1;
                }

                // start over if the horizontal look streak broke.
            } else {
                counter = 0;
            }
        }
    }

    // if we didn't get a connect above, there is no connect, return 0.
    return 0;
}

/**
 * @brief This function check if the player have an vertical connect on the given board.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param player the player we are checking
 * @param connect the connect that is considered as a win
 *
 * @return 1 if there is a connect, 0 if there isn't a connect.
 */
int verticalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect) {
    // counter to count occurrences in horizontal
    int counter = 0;

    // loop through the columns
    for (int i = 0; i < columns; i++) {
        // for each col, loop through the rows, creating vertical look.
        for (int j = 0; j < rows; j++) {
            // if we find our player
            if (board[j][i] == player) {
                // the player appear so we add
                counter++;

                // once the counter == connect we made a connect
                if (counter == connect) {
                    return 1;
                }

                // start over if the vertical look streak broke.
            } else {
                counter = 0;
            }
        }
    }
    // if we didn't get a connect above, there is no connect, return 0.
    return 0;
}

/**
 * @brief This function check if the player have at least one of the allowed Diag connects on the given board.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param player the player we are checking
 * @param connect the connect that is considered as a win
 *
 * @return 1 if there is at least one connect, 0 if there isn't a connect.
 */
int checkAllDiagConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect) {
    // rightDown Diag
    if (diagConnect(board, rows, columns, player, connect, 1, 1) == 1) {
        return 1;
    }

    // leftDown Diag
    if (diagConnect(board, rows, columns, player, connect, 1, -1) == 1) {
        return 1;
    }

    // rightUp Diag
    if (diagConnect(board, rows, columns, player, connect, -1, 1) == 1) {
        return 1;
    }

    // leftUp Diag
    if (diagConnect(board, rows, columns, player, connect, -1, -1) == 1) {
        return 1;
    }

    // if any of the diagConnect versions didn't return 1, there is no connect.
    return 0;
}

/**
 * @brief This function check if a diagConnect is possible with the given rowInc and colInc.
 * rowInc and colInc determine the connect angel.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param player the player we are checking
 * @param connect the connect that is considered as a win
 * @param rowInc the movement for the next row
 * @param colInc the movement for the next col
 *
 * @return 1 if there is a connect, 0 if there isn't a connect.
 */
int diagConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect, int rowInc, int colInc) {
    // counter to count occurrences in diagonal
    int counter = 0;

    // the two loops is to go each cell.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // once we find the player in the cell..
            if (board[i][j] == player) {
                counter++;

                // save the row and col he's in
                int currentRow = i;
                int currentCol = j;

                // as long as we are in the current ranges (the limit of the array) keep going
                while (numberInRange(currentRow, rows) && numberInRange(currentCol, columns)) {
                    // move row or col according to the given instructions, that was we look diagonally.
                    currentRow += rowInc;
                    currentCol += colInc;

                    // if the the player appear in the next diag cell add to counter
                    if (board[currentRow][currentCol] == player) {
                        counter++;

                        // check if we get a connect
                        if (counter == connect) {
                            return 1;
                        }
                        // start over if the diagonally look streak broke.
                    } else {
                        counter = 0;
                    }
                }
            }
        }
    }

    return 0;
}

/**
 * @brief this function get a number and return the player in A-Z char form.
 *
 * @param playerNumber the number to check
 *
 * @return the playerNumber in char form. A-Z.
 */
char getPlayerFromNum(int playerNumber) {
    // A is the first player, just add it.
    playerNumber += 'A';

    return playerNumber;
}

/**
 * @brief This function check if the given board is in a draw state
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param players the amount of players playing the game.
 * @param connect the connect that is considered as a win
 *
 * @return 1 if draw, 0 if not a draw.
 */
int aDraw(char board[ROWS][COLS], int rows, int columns, int players, int connect) {
    // check if all the cells are occupied, start with 1 for yes, and then change to 0 if not.
    int allOccupied = 1;

    // run through every cell in the board
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < columns; j++) {
            // if any board is not occupied, mark it in allOccupied.
            if (board[i][j] == ' ') {
                allOccupied = 0;
            }
        }
    }

    // there can't be a draw unless the board is full.
    if (allOccupied == 0) {
        return 0;
    } else {

        // go through all the players
        for (int i = 0; i < players; i++) {
            // check if the i player is a winner each iteration
            int aWinner = haveWin(board, rows, columns, getPlayerFromNum(i), connect);

            // if he is return 0 cause there cant be a winner in a draw board.
            if (aWinner == 1) {
                return 0;
            }
        }

        // there is no winner, and the board is full. so return 1. we are in a draw.
        return 1;
    }
}

/**
 * @brief this function check if the given player have any possible connect in the given board.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param player the player we are checking
 * @param connect the connect that is considered as a win
 *
 * @return 1 if haveWin, 0 if not.
 *
 */
int haveWin(char board[ROWS][COLS], int rows, int columns, char player, int connect) {

    // check vertical connect
    int vertical = verticalConnect(board, rows, columns, player, connect);

    // check horizontal connect
    int horizontal = horizontalConnect(board, rows, columns, player, connect);

    // check if have atleast one diagonal connect
    int diagonal = checkAllDiagConnect(board, rows, columns, player, connect);

    // if any of the connects above exist he win.
    if (vertical == 1 || horizontal == 1 || diagonal == 1) {
        return 1;
    } else {
        // no connect = not a winner
        return 0;
    }
}