// (89110, Spring 2023, Assignment #3, Tal Ben Naim, 212749071, bennait3)
#include <stdio.h>

// Defines

// defines related to option 3. BINARY STRINGS
#define START_RANGE_BINARY_STRINGS 1
#define END_RANGE_BINARY_STRINGS 32

// Functions declaration.

// general functions
void printMenu();
void cleanBuffer();
int isOptionValid(char option);

int isThereReminder(int number, int divideBy);

// All the options
void expressionEvaluator();

void findBinaryStrings();
void binaryStringsLogic(int length);

void isExcitingNumber();
void isCoolNumber();
void countPaths();

/**
 * @brief Main function that wait for user input to navigate the user
 * to the right part of the program according to the input.
 * @return 0 if the program runs successfully
 */
int main() {
    char choice;

    do {
        // present the menu to the user and take his choice
        printMenu();

        scanf("%c", &choice);
        cleanBuffer();

        // inform the user about the invalid choice, then I will ask them again.
        if (!isOptionValid(choice)) {
            printf("Invalid option\n");
        }

        // depending on the user's choice navigate the user to the right program.
        switch (choice) {
            case '1':
                // expressionEvaluator();
                break;
            case '2':
                findBinaryStrings();
                break;
            case '3':
                // isExcitingNumber();
                break;
            case '4':
                // isCoolNumber();
                break;
            case '5':
                // countPaths();
                break;

            default:
                break;
        }

        // '0' is the option to exit the program;
    } while (choice != '0');
}

// Functions definitions

// General functions

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

/**
 * @brief check if there is a reminder when we divide the number with the divideBy number.
 *
 * @param number the number we are dividing
 *
 * @param divideBy the number we divide by
 *
 * @return return the reminder if there is no reminder we will get 0.
 * which acts as false for the if statement.
 * (any number other than 0 will be seen as "TRUE" in an if statement).
 */
int isThereReminder(int number, int divideBy) {
    return number % divideBy;
}

/**
 * @brief check if user's input is a valid option.
 *
 * @param the user's option
 *
 * @return 1 for valid input, 0 for invalid.
 */
int isOptionValid(char option) {
    // This program options range is 0 - 5.
    if (option < '0' || option > '5') {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief Finds all the binary strings that match the user's length and print all
 * but the strings with consecutive '1'.
 */
void findBinaryStrings() {
    // take a length from the user
    int length;

    printf("Enter length:\n");

    scanf(" %d", &length);
    cleanBuffer();

    // if the length isn't within the allowed range, inform the user.
    if (length < START_RANGE_BINARY_STRINGS || length > END_RANGE_BINARY_STRINGS) {
        printf("Invalid length\n");
        return;
    } else {
        binaryStringsLogic(length);
    }
}

/**
 * @brief contains the logic to finds all the binary strings that match the user's length and print all
 * but the strings with consecutive '1'.
 *
 * @param length The length of strings to print.
 */
void binaryStringsLogic(int length) {

    static unsigned int numberToPrint = 0;

    printf("%0*d\n", length, numberToPrint);
}
