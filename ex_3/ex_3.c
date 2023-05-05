// (89110, Spring 2023, Assignment #3, Tal Ben Naim, 212749071, bennait3)
#include <stdio.h>

// #region Functions declaration.

// general functions
void printMenu();

void cleanBuffer();

// All the options
void expressionEvaluator();

void findBinaryStrings();

void isExcitingNumber();

void isCoolNumber();

void countPaths();

// #endregion (Functions declaration)

/**
 * @brief Main function that wait for user input to navigate the user
 * to the right part of the program according to the input.
 * @return 0 if the program runs successfully
 */
int main() {

    char choice;

    do {
        printMenu();

        scanf("%c", &choice);

        cleanBuffer();

        switch (choice) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;

            default:
                break;
        }

    } while (choice != '0');
}

// #region Functions definitions

// #region General functions

/**
 * @brief print out the program options to the user
 */
void printMenu() {

    printf("Choose an option:\n");
    printf("0. Exit\n");
    printf("1. Evaluator\n");
    printf("2. Binary strings\n");
    printf("3. Exciting number\n");
    printf("4. Cool number\n");
    printf("5. Count paths\n");
}

/**
 * @brief remove any leftovers from user input, like new line \n etc.
 */
void cleanBuffer() {

    // scanf until we see \n, then we save that \n in the buffer cleaner
    char bufferCleaner;
    scanf("%*[^\n]");
    scanf("%c", &bufferCleaner);
}

// #endregion (General functions)

// #endregion (Functions definitions)
