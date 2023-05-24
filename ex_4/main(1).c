#include "ex_4.c"
#include "ex_4.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// שימו לב:
// הגודל של הלוח בבדיקה הזאת הוא 6*7
// אל תגדילו או תקטינו את המימדים האלה
// כי זה יגרום לכם להרבה שגיאות
// אם השתמשתם בdefine באחד מהקבצים האחרים - שנו אותם למספרים האלה או שתמחקו אותם לפני הבדיקה
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define ROWS 6
#define COLS 7

int funFunFun(char board[ROWS][COLS], char newBoard[ROWS][COLS], int rows, int columns);

int main() {

    int i = 1;

    // fun 1 "initBoard" + fun 2 "printBoard"
    printf("\nHi!\n\nTest for \"initBoard\" + \"printBoard\":\n");
    char board[ROWS][COLS];
    initBoard(board, ROWS, COLS);
    printBoard(board, ROWS, COLS);

    // fun 3 "makeMove"
    printf("\n\nTest for \"makeMove\":\n");
    makeMove(board, ROWS, COLS, 5, 'A', 0) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 1
    makeMove(board, ROWS, COLS, 5, 'E', 0) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 2
    makeMove(board, ROWS, COLS, 5, 'A', 6) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 3
    makeMove(board, ROWS, COLS, 5, 'A', COLS) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 4
    makeMove(board, ROWS, COLS, 5, 'A', -1) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 5
    makeMove(board, ROWS, COLS, 5, 'F', 0) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 6
    makeMove(board, ROWS, COLS, 5, '!', 0) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 7
    makeMove(board, ROWS, COLS, 5, 'a', 0) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 8
    for (int i = 0; i < ROWS; i++) {
        board[i][3] = 'C';
    }
    makeMove(board, ROWS, COLS, 5, 'C', 3) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 9

    // fun 4 "undoMove"
    printf("\n\nTest for \"undoMove\":\n");
    undoMove(board, ROWS, COLS, 0) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 10
    undoMove(board, ROWS, COLS, 0) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 11
    undoMove(board, ROWS, COLS, 0) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 12
    undoMove(board, ROWS, COLS, -1) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 13
    undoMove(board, ROWS, COLS, COLS) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 14
    initBoard(board, ROWS, COLS);

    // fun 5 "getStatus" + fun 6 "getWinner"
    printf("\n\nTest for \"getStatus\" + \"getWinner\":\n");
    getStatus(board, ROWS, COLS, 5, 4) == -1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 15
    getWinner(board, ROWS, COLS, 5, 4) == -1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 16
    board[5][1] = 'A';
    board[4][1] = 'B';
    board[5][0] = 'C';
    board[4][0] = 'D';
    board[5][2] = 'A';
    board[3][1] = 'B';
    board[3][0] = 'C';
    board[2][0] = 'D';
    board[5][3] = 'A';
    board[2][1] = 'B';
    board[1][0] = 'C';
    board[0][0] = 'D';
    getStatus(board, ROWS, COLS, 3, 4) == -1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 17
    getWinner(board, ROWS, COLS, 5, 4) == -1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 18
    board[5][4] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 19
    getWinner(board, ROWS, COLS, 5, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 20
    board[5][4] = ' ';
    board[5][6] = 'A';
    board[1][1] = 'B';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 21
    getWinner(board, ROWS, COLS, 3, 4) == 'B' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 22
    board[1][1] = ' ';
    board[4][2] = 'B';
    board[4][3] = 'C';
    board[1][1] = 'D';
    board[3][2] = 'A';
    board[5][4] = 'B';
    board[0][1] = 'C';
    board[2][2] = 'D';
    board[5][5] = 'A';
    board[4][4] = 'B';
    board[3][4] = 'C';
    board[3][3] = 'D';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 23
    getWinner(board, ROWS, COLS, 3, 4) == 'D' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 24
    board[3][3] = ' ';
    board[4][5] = 'D';
    board[4][6] = 'A';
    board[3][5] = 'B';
    board[2][5] = 'C';
    board[3][6] = 'D';
    board[3][3] = 'A';
    board[2][6] = 'B';
    board[1][6] = 'C';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 25
    getWinner(board, ROWS, COLS, 3, 4) == 'C' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 26
    board[1][6] = ' ';
    board[2][4] = 'C';
    board[1][6] = 'D';
    board[2][3] = 'A';
    board[1][3] = 'B';
    board[0][3] = 'C';
    board[1][2] = 'D';
    board[1][5] = 'A';
    board[0][6] = 'B';
    board[0][5] = 'C';
    board[1][4] = 'D';
    board[0][2] = 'A';
    board[0][4] = 'B';
    getStatus(board, ROWS, COLS, 3, 4) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 27
    getWinner(board, ROWS, COLS, 3, 4) == -1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 28
    board[3][3] = ' ';
    board[2][6] = ' ';
    board[2][4] = '!';
    board[1][6] = ' ';
    board[2][3] = ' ';
    board[1][3] = ' ';
    board[0][3] = ' ';
    board[1][2] = ' ';
    board[1][5] = ' ';
    board[0][6] = ' ';
    board[0][5] = ' ';
    board[1][4] = ' ';
    board[0][2] = ' ';
    board[0][4] = ' ';
    board[1][2] = 'A';
    board[0][2] = 'B';
    board[3][3] = 'C';
    board[2][3] = 'D';
    board[1][3] = 'A';
    board[0][3] = 'B';
    board[2][4] = 'C';
    board[1][4] = 'D';
    board[1][5] = 'A';
    board[0][5] = 'B';
    board[2][6] = 'C';
    board[1][6] = 'D';
    board[0][6] = 'A';
    board[0][4] = 'B';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 29
    getWinner(board, ROWS, COLS, 3, 4) == 'B' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 30
    initBoard(board, ROWS, COLS);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    printf("הערה חשובה:\n"
           "בבדיקות הבאות, ועד לפונקציה הבאה (31-80),\n"
           "יצרתי רצפים שלא באמת קרו במהלך משחק\n"
           "(כלומר, הם מרחפים באוויר).\n"
           "אם במהלך אחת מהפונקציות getStatus או getWinner\n"
           "בדקתם גם את תקינות התווים - אתם תקבלו כאן שגיאות...\n");

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // בדיקת שורה
    board[3][0] = 'A';
    board[3][1] = 'A';
    board[3][2] = 'A';
    board[3][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 31
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 32
    board[3][0] = ' ';
    board[3][4] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 33
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 34
    board[3][1] = ' ';
    board[3][2] = ' ';
    board[3][5] = 'A';
    board[3][6] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 35
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 36

    // בדיקת עמודה
    initBoard(board, ROWS, COLS);
    board[0][3] = 'A';
    board[1][3] = 'A';
    board[2][3] = 'A';
    board[3][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 37
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 38
    board[0][3] = ' ';
    board[4][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 39
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 40
    board[1][3] = ' ';
    board[5][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 41
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 42

    // בדיקת אלכסונים מימין לשמאל
    initBoard(board, ROWS, COLS);
    board[0][6] = 'A';
    board[1][5] = 'A';
    board[2][4] = 'A';
    board[3][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 43
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 44
    board[0][6] = ' ';
    board[4][2] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 45
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 46
    board[1][5] = ' ';
    board[5][1] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 47
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 48
    initBoard(board, ROWS, COLS);
    board[1][6] = 'A';
    board[2][5] = 'A';
    board[3][4] = 'A';
    board[4][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 49
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 50
    board[1][6] = ' ';
    board[5][2] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 51
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 52
    initBoard(board, ROWS, COLS);
    board[2][6] = 'A';
    board[3][5] = 'A';
    board[4][4] = 'A';
    board[5][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 53
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 54
    initBoard(board, ROWS, COLS);
    board[0][5] = 'A';
    board[1][4] = 'A';
    board[2][3] = 'A';
    board[3][2] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 55
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 56
    board[0][5] = ' ';
    board[4][1] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 57
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 58
    board[1][4] = ' ';
    board[5][0] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 59
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 60
    initBoard(board, ROWS, COLS);
    board[0][3] = 'A';
    board[1][2] = 'A';
    board[2][1] = 'A';
    board[3][0] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 61
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 62

    // אלכסונים משמאל לימין
    initBoard(board, ROWS, COLS);
    board[0][0] = 'A';
    board[1][1] = 'A';
    board[2][2] = 'A';
    board[3][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 63
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 64
    board[0][0] = ' ';
    board[4][4] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 65
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 66
    board[1][1] = ' ';
    board[5][5] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 67
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 68
    initBoard(board, ROWS, COLS);
    board[1][0] = 'A';
    board[2][1] = 'A';
    board[3][2] = 'A';
    board[4][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 69
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 70
    board[1][0] = ' ';
    board[5][4] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 71
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 72
    initBoard(board, ROWS, COLS);
    board[2][0] = 'A';
    board[3][1] = 'A';
    board[4][2] = 'A';
    board[5][3] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 73
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 74
    initBoard(board, ROWS, COLS);
    board[0][2] = 'A';
    board[1][3] = 'A';
    board[2][4] = 'A';
    board[3][5] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 75
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 76
    board[0][2] = ' ';
    board[4][6] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 77
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 78
    initBoard(board, ROWS, COLS);
    board[0][3] = 'A';
    board[1][4] = 'A';
    board[2][5] = 'A';
    board[3][6] = 'A';
    getStatus(board, ROWS, COLS, 3, 4) == 1 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 79
    getWinner(board, ROWS, COLS, 3, 4) == 'A' ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 80
    initBoard(board, ROWS, COLS);

    // fun 7 "isValidBorad"
    printf("\n\nTest for \"isValidBorad\":\n");
    isValidBoard(board, ROWS, COLS, 3, 4) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 81
    board[5][3] = 'A';
    board[4][3] = 'B';
    board[3][3] = 'C';
    isValidBoard(board, ROWS, COLS, 3, 4) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 82
    board[5][3] = '%';
    isValidBoard(board, ROWS, COLS, 3, 4) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 83
    board[5][3] = 'a';
    isValidBoard(board, ROWS, COLS, 3, 4) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 84
    board[5][3] = ' ';
    isValidBoard(board, ROWS, COLS, 3, 4) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 85
    initBoard(board, ROWS, COLS);
    board[5][0] = 'A';
    board[5][2] = 'B';
    board[5][3] = 'C';
    board[5][1] = 'D';
    board[4][0] = 'A';
    board[4][3] = 'B';
    board[4][2] = 'C';
    board[4][1] = 'D';
    board[3][0] = 'A';
    board[3][2] = 'B';
    board[3][3] = 'C';
    board[3][1] = 'D';
    board[2][0] = 'A';
    board[2][3] = 'B';
    board[2][2] = 'C';
    board[2][1] = 'D';
    isValidBoard(board, ROWS, COLS, 3, 4) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 86
    initBoard(board, ROWS, COLS);
    isValidBoard(board, ROWS, COLS, 2, 4) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 87
    board[5][1] = 'A';
    board[5][3] = 'B';
    board[4][2] = 'A';
    board[5][2] = 'B';
    isValidBoard(board, ROWS, COLS, 2, 4) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 88
    board[5][6] = 'A';
    isValidBoard(board, ROWS, COLS, 2, 4) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 89
    initBoard(board, ROWS, COLS);
    board[5][0] = 'A';
    board[5][1] = 'A';
    board[4][0] = 'C';
    board[4][1] = 'B';
    isValidBoard(board, ROWS, COLS, 3, 4) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 90
    initBoard(board, ROWS, COLS);
    board[5][1] = 'A';
    board[4][1] = 'B';
    board[5][0] = 'C';
    board[4][0] = 'D';
    board[5][2] = 'A';
    board[3][1] = 'B';
    board[3][0] = 'C';
    board[2][0] = 'D';
    board[5][3] = 'A';
    board[2][1] = 'B';
    board[1][0] = 'C';
    board[0][0] = 'D';
    isValidBoard(board, ROWS, COLS, 4, 4) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 91
    board[5][4] = 'A';
    isValidBoard(board, ROWS, COLS, 4, 4) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 92
    board[5][4] = 'B';
    initBoard(board, ROWS, COLS);
    for (int i = 0; i <= 4; i++) {
        board[5][i] = 'A';
    }
    board[5][5] = 'B';
    board[5][6] = 'B';
    board[3][5] = 'B';
    board[3][6] = 'B';
    board[4][5] = 'C';
    board[4][6] = 'C';
    board[2][5] = 'C';
    board[2][6] = 'C';
    isValidBoard(board, ROWS, COLS, 3, 3) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 93
    initBoard(board, ROWS, COLS);
    for (int i = 0; i < 4; i++) {
        board[5][i] = 'A';
    }
    for (int i = 2; i <= 4; i++) {
        board[i][3] = 'A';
    }
    board[5][5] = 'B';
    board[5][6] = 'B';
    board[3][5] = 'B';
    board[3][6] = 'B';
    board[1][5] = 'B';
    board[1][6] = 'B';
    board[4][0] = 'B';
    board[4][5] = 'C';
    board[4][6] = 'C';
    board[2][5] = 'C';
    board[2][6] = 'C';
    board[0][5] = 'C';
    board[0][6] = 'C';
    board[4][1] = 'C';
    isValidBoard(board, ROWS, COLS, 3, 4) == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 94
    initBoard(board, ROWS, COLS);
    board[5][6] = 'A';
    board[5][5] = 'B';
    board[4][6] = 'C';
    board[3][6] = 'A';
    board[2][6] = 'B';
    board[5][2] = 'C';
    board[5][4] = 'A';
    board[5][3] = 'B';
    board[4][4] = 'C';
    board[3][4] = 'A';
    board[5][1] = 'B';
    board[2][4] = 'C';
    isValidBoard(board, ROWS, COLS, 3, 2) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 95
    board[4][5] = 'A';
    isValidBoard(board, ROWS, COLS, 3, 2) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 96

    // fun 8 "encode" + fun 2 "decode"
    initBoard(board, ROWS, COLS);
    printf("\n\nTest for \"encode\" + \"decode\":\n");
    char code[100] = "\0";
    encode(board, ROWS, COLS, code);
    strcmp(code, "H /H /H /H /H /H /") == 0 ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 97
    strcpy(code, "\0");
    board[5][1] = 'A';
    board[4][1] = 'B';
    board[5][0] = 'C';
    board[4][0] = 'D';
    board[5][2] = 'A';
    board[3][1] = 'B';
    board[3][0] = 'C';
    board[2][0] = 'D';
    board[5][3] = 'A';
    board[2][1] = 'B';
    board[1][0] = 'C';
    board[0][0] = 'D';
    encode(board, ROWS, COLS, code);
    strcmp(code, "BDG /BCG /BDBBF /BCBBF /BDBBF /BCDAD /") == 0 ? printf("%03d. Yes!\n", i)
                                                                : printf("%03d. Nooooooo!\n", i);
    i++; // 98
    board[5][5] = 'A';
    board[4][6] = 'B';
    board[4][2] = 'C';
    board[3][6] = 'D';
    board[5][6] = 'A';
    board[4][5] = 'B';
    board[4][3] = 'C';
    board[2][6] = 'D';
    board[5][4] = 'A';
    board[4][4] = 'B';
    board[3][3] = 'C';
    board[3][5] = 'D';
    strcpy(code, "\0");
    encode(board, ROWS, COLS, code);
    strcmp(code, "BDG /BCG /BDBBE BD/BCBBB BCB CD/BDBBCCDB/BCGA/") == 0 ? printf("%03d. Yes!\n", i)
                                                                        : printf("%03d. Nooooooo!\n", i);
    i++; // 99
    strcpy(code, "\0");
    board[0][2] = 'A';
    board[0][3] = 'B';
    board[0][4] = 'C';
    board[1][4] = 'D';
    encode(board, ROWS, COLS, code);
    strcmp(code, "BDB BABBBCC /BCD BDC /BDBBE BD/BCBBB BCB CD/BDBBCCDB/BCGA/") == 0 ? printf("%03d. Yes!\n", i)
                                                                                    : printf("%03d. Nooooooo!\n", i);
    i++; // 100
    char newBoard[ROWS][COLS];
    decode(code, newBoard);
    funFunFun(board, newBoard, ROWS, COLS) ? printf("%03d. Yes!\n", i) : printf("%03d. Nooooooo!\n", i);
    i++; // 101

    printf("\nThe end!\n");

    return 0;
}

int funFunFun(char board[ROWS][COLS], char newBoard[ROWS][COLS], int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] != newBoard[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}