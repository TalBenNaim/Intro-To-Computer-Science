// (89110, Spring 2023, Assignment #4, Tal Ben Naim, 212749071, bennait3)

#include "ex_4.h"
#include <string.h>

// helper functions declaration
int playerInRange(int players, int player);

int numberInRange(int number, int numbers);

int getLowestEmptyRow(char board[ROWS][COLS], int column, int rows);

int horizontalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int verticalConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int checkAllDiagConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int diagConnect(char board[ROWS][COLS], int rows, int columns, char player, int connect, int rowInc, int colInc);

char getPlayerFromNum(int playerNumber);

int aDraw(char board[ROWS][COLS], int rows, int columns, int players, int connect);

int haveWin(char board[ROWS][COLS], int rows, int columns, char player, int connect);

int aFloatingCell(char board[ROWS][COLS], int rows, int columns);

char getValueAboveCell(char board[ROWS][COLS], int row, int column);

int replayTheBoard(char board[ROWS][COLS], int rows, int columns, int connect, int moves, char player, int players);

int movesDoneInBoard(char board[ROWS][COLS], int rows, int columns);

int canUndoMove(char board[ROWS][COLS], int rows, int columns, int column);

void encodeRow(const char board[ROWS][COLS], int columns, char *code, int theRow);

char getNumInBase64(int num);

int getDecimalFrom64(char character);

int isPlayerAtTop(char board[ROWS][COLS], int rows, char player, int column);

// the main functions.

/**
 * @brief This function initialize the board to the default state - every cell in the board is empty.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 */
void initBoard(char board[ROWS][COLS], int rows, int columns) {
    // get each cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // set the cell content to empty
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
    // check if can undo the move
    int canUndo = canUndoMove(board, rows, columns, column);

    // get the lowestEmpty row in the given col.
    int lowestEmptyRow = getLowestEmptyRow(board, column, rows);

    // can undo the move
    if (canUndo == 0) {
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
    if (getWinner(board, rows, columns, players, connect) != -1) {
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

/**
 * @brief This function gets a board and check if it's valid according to several parameters:
 * 1. there is a cell with player not in the range
 * 2. there is a col with a floating player (the cell below is empty).
 * 3. the is an illegal cell in the board.
 * 4. the player kept playing even though somebody won. (recreate the game and check).
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 * @param players the amount of players playing the game.
 * @param connect the connect that is considered as a win
 *
 * @return 1 if the board is valid, 0 if the board is invalid.
 */
int isValidBoard(char board[ROWS][COLS], int rows, int columns, int players, int connect) {
    // check if the the board have floating.
    int haveFloating = aFloatingCell(board, rows, columns);

    // if there is a floating cell the board is invalid.
    if (haveFloating == 1) {
        return 0;
    }

    // look at each cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            char cell = board[i][j];
            // check if player is in range of players, as well as if the cell content is legal.
            int isPlayerInRange = playerInRange(players, cell);

            // check if the cell is not empty and also not in the range it's illegal.
            if (cell != ' ' && isPlayerInRange == 0) {
                // illegal cell, the board is invalid.
                return 0;
            }
        }
    }

    // get the moves that have been done
    int moves = movesDoneInBoard(board, rows, columns);

    // get the last player
    char lastPlayer = 'A' + (players - 1);

    // check if the board can be replayed
    int canReplay = replayTheBoard(board, rows, columns, connect, moves, lastPlayer, players);

    // if can't replay return 0
    if (canReplay == 0) {
        return 0;
    }

    // return 1 if any the previous tests did not fail the board.
    return 1;
}

/**
 * @brief this function encode the board into the give code using the following rule
 * let's say a row is [A,A,A,B,B] the encode will be DACB because there are D (3 in base64)
 * A in a row in the row, like wise, C(2 in base64) times, B..
 * then between each row we put /.
 *
 * @param board the board we are playing on, a 2D char array, to encode.
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param code the string to add to the encode.
 *
 */
void encode(const char board[ROWS][COLS], int rows, int columns, char *code) {
    // go through the rows
    for (int i = 0; i < rows; i++) {
        // encode the row i
        encodeRow(board, columns, code, i);
        // add a / to represent end of the row.
        strcat(code, "/");
    }
    // at the end of the encode we need to add \0
    strcat(code, "\0");
}

/**
 * @brief this function decode the code into the given board using the following rule
 * let's say a code is DACB/ the decode will be [A,A,A,B,B] because there are D (3 in base64)
 * A in a row in the row, like wise, C(2 in base64) times, B..
 * then between each row we put /.
 *
 * @param code the string we decode from
 * @param board the board we are playing on, a 2D char array, we are inserting from the code.
 *
 */
void decode(const char *code, char board[ROWS][COLS]) {
    // take the length of the code
    int lengthOfCode = strlen(code);

    // to save the location of the char we print, to not calc len
    int notToCalcLength = -1;

    // we don't know the size of the board so index will help us with pointers
    int index = 0;

    // check each char in the code
    for (int i = 0; i < lengthOfCode; i++) {
        char currentChar = code[i];

        // if the char isn't the one not to calc or its end of line
        if (notToCalcLength != i && currentChar != '/') {
            // the first char will always be the times to print the one following so get the decimal from in base 64.
            int length = getDecimalFrom64(currentChar);

            /*
            the next char is the one we are printing, we dont have to worry about i+1 not existing because the last
            char is always /
            */
            notToCalcLength = i + 1;
            char toInsert = code[i + 1];

            // save the length before looping
            int lengthToRun = length + index;
            for (int j = index; j < lengthToRun; j++) {
                // accessing the board array using pointer arithmetic
                char *currentElement = &board[0][0] + j;

                // modify the element at the current position
                *currentElement = toInsert;

                // each modification moves one next on the index.
                index++;
            }
        }
    }
}

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

/**
 * @brief this function take a board and check if there is a floating cell in the board
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param columns the number of columns in the board.
 *
 * @return 1 if there is a floating cell and 0 if there isn't a floating cell.
 */
int aFloatingCell(char board[ROWS][COLS], int rows, int columns) {
    // get each cell without the first row, cause we are looking up from empty cell.
    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // take the cell
            char cell = board[i][j];

            // if the cell is empty, we need to check there is occupied cells above him.
            if (cell == ' ') {
                // get the content of the above cell
                char cellAboveContent = getValueAboveCell(board, i, j);

                // if the content of the above cell is not empty, and can be reached (not -1) the cell above
                // floating.
                if (cellAboveContent != ' ' && cellAboveContent != -1) {
                    return 1;
                }
            }
        }
    }

    // if we didn't find any floating cell above, that mean there aren't any.
    return 0;
}

/**
 * @brief this function take a board and a cell, and get the content of the cell above it.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param row the row of the current cell
 * @param column the column of the current cell
 *
 * @return the content of the above cell, or -1 if can't get the cell. (out of bound)
 */
char getValueAboveCell(char board[ROWS][COLS], int row, int column) {
    // only when the cell row is 1 there is no row above.
    if (row != 0) {
        return board[row - 1][column];
    } else {
        return -1;
    }
}

/**
 * @brief this is a recursive function that tries to replay the board by making the moves backward.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board
 * @param columns the number of rows in the board
 * @param connect the connect that is considered as a win
 * @param moves the number of moves that have been done in the given board
 * @param player the player to check the moves on
 * @param players the amount of players
 *
 * @return 1 if we could mimic and 0 if we couldn't mimic the moves.
 */
int replayTheBoard(char board[ROWS][COLS], int rows, int columns, int connect, int moves, char player, int players) {
    // exit case!, if no moves have been done the board is empty and legal, and if we could mimic all the moves.
    if (moves == 0) {
        return 1;
    }

    // loop through the columns and try to undo each action.
    for (int i = 0; i < columns; i++) {
        // check if can undo a move with the given player.
        int canUndo = canUndoMove(board, rows, columns, i);

        // if the player is the one on top
        int atTop = isPlayerAtTop(board, rows, player, i);

        // if can undo and the current player is the one on top, move on.
        if (canUndo && atTop) {
            break;
        }

        // if can't undo the move, return 0 the board isn't valid, cant be replayed.
        if (canUndo == 0) {
            return 0;
        }
    }

    // got to the first player
    if (player == 'A') {
        // reduce the moves by one, and transform the player to the "last" player. (we are going backward).
        return replayTheBoard(board, rows, columns, connect, moves - 1, player + (players - 1), players);
    } else {
        // reduce the moves by one, and transform the player to the previous player. (we are going backward).
        return replayTheBoard(board, rows, columns, connect, moves - 1, player - 1, players);
    }
}

/**
 * @brief this function counter how many moves have been down in the given board.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board
 * @param columns the number of rows in the board
 *
 * @return counter - the number of moves done. 0 is non done ofc.
 */
int movesDoneInBoard(char board[ROWS][COLS], int rows, int columns) {
    int counter = 0;

    // get each cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // the cell
            char cell = board[i][j];

            // if the cell is empty a move have been done.
            if (cell != ' ') {
                counter++;
            }
        }
    }

    return counter;
}

/**
 * @brief this function check if a move can be undone on the given column.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board
 * @param columns the number of rows in the board
 * @param column the given column to check the undo on
 *
 * @return 1 if can be undone, and 0 if cannot.
 */
int canUndoMove(char board[ROWS][COLS], int rows, int columns, int column) {

    int isInColRange = numberInRange(column, columns);

    // get the lowest empty row of the column.
    int lowestEmptyRow = getLowestEmptyRow(board, column, rows);

    /*
    if one of the checks doesn't pass, return 0 (we can't do the move).
    (if the lowestEmptyRow == rows - 1 that mean the whole column is empty).
    */
    if (isInColRange == 0 || lowestEmptyRow == (rows - 1)) {
        return 0;
    } else {
        // can be done.
        return 1;
    }
}

/**
 * @brief this function encode the given row according to the encode rules.
 * let's say a row is [A,A,A,B,B] the encode will be DACB because there are D (3 in base64)
 * A in a row in the row, like wise, C(2 in base64) times, B..
 *
 * @param board the board we are playing on, a 2D char array.
 * @param columns the number of columns in the board
 * @param code the string to add to the encode.
 * @param theRow the given row to encode in a string manner
 */
void encodeRow(const char board[ROWS][COLS], int columns, char *code, int theRow) {
    // a counter to count occurrences
    int counter = 0;

    for (int j = 0; j < columns; j++) {
        // take the content of the cell to check
        char check = board[theRow][j];
        counter++;

        // if there is next col
        if (j + 1 != columns) {
            // if the curent cell is different from the next, we encode.
            if (check != board[theRow][j + 1]) {
                // turn into base64 and make a new string with the base and the char. like the rule
                char numInBase64 = getNumInBase64(counter);
                // add the number and check to the new string
                char newString[] = {numInBase64, check, '\0'};
                // add the new string to the code.
                strcat(code, newString);
                // reset the counter
                counter = 0;
            }
            // check if the last cell is the same as before
        } else if (check == board[theRow][j - 1]) {
            // turn into base64 and make a new string with the base and the char. like the rule
            char numInBase64 = getNumInBase64(counter);
            // add the number and check to the new string
            char newString[] = {numInBase64, check, '\0'};
            // add the new string to the code.
            strcat(code, newString);
            // reset the counter
            counter = 0;
        } else {
            // turn into base64 and make a new string with the base and the char. like the rule
            char numInBase64 = getNumInBase64(counter);
            // add the number and check to the new string
            char newString[] = {numInBase64, check, '\0'};
            // add the new string to the code.
            strcat(code, newString);
            // reset the counter
            counter = 0;
        }
    }
}

/**
 * @brief this function get a number and return the number in a base 64 digits
 *
 * @param number the number to turn into base64
 *
 * @return the transformed char from the number.
 */
char getNumInBase64(int number) {
    // the base64 size.. 64
    const int base64 = 64;
    // base64 character set
    const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // to get the index
    int index = number % base64;

    // get the character from the base64 table
    char base64Char = base64Table[index];

    return base64Char;
}

/**
 * @brief the function get a char and turn it into decimal in base 64
 *
 * @param character the char in base to turn into decimal
 *
 * @return the number in decimal, else return -1 if couldn't do it
 */
int getDecimalFrom64(char character) {
    // the base64 size.. 64
    const int base64 = 64;
    // base64 character set
    const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // to get the index
    for (int i = 0; i < base64; i++) {
        if (base64Table[i] == character) {
            return i;
        }
    }

    return -1;
}

/**
 * @brief this function checks if the given player is on top of the possible col to undo a move on.
 *
 * @param board the board we are playing on, a 2D char array.
 * @param rows the number of rows in the board.
 * @param player the given player to check
 * @param column the col to check
 *
 * @return 1 if the player is, else 0.
 */
int isPlayerAtTop(char board[ROWS][COLS], int rows, char player, int column) {
    // get lowestEmptyRow
    int lowestEmptyRow = getLowestEmptyRow(board, column, rows);

    // get the cell below to get the cell on top
    int cellBelow = board[lowestEmptyRow + 1][column];

    // if the cell at top == player return 1
    if (cellBelow == player) {
        return 1;
    } else {
        return 0;
    }
}