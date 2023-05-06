// (89110, Spring 2023, Assignment #3, Tal Ben Naim, 212749071, bennait3)
#include <stdio.h>

// Defines

// defines related to option 3. BINARY STRINGS
#define START_RANGE_BINARY_STRINGS 1
#define END_RANGE_BINARY_STRINGS 32

// 10 is the optimal array length - 10 digits of unsigned int.
#define ARRAY_LENGTH 10
#define DECIMAL_BASE 10

// Functions declaration.

// general functions
void printMenu();
void cleanBuffer();
int isOptionValid(char option);

int isThereReminder(int number, int divideBy);

unsigned int countDigits(int number, int base);

int power(int number, int powerBy);

unsigned int reverseNumber(unsigned int number, unsigned int digitsCount, int base);

void shiftArrayToLeft(unsigned int array[], int arrayLength);

// All the options
void expressionEvaluator();

void findBinaryStrings();
void binaryStringsLogic(int length);

void isExcitingNumber();
unsigned long sumDigitsPowerLength(unsigned int number, unsigned int digitsCount, int base);

void isCoolNumber();
void changeToDigitsArray(unsigned int array[], unsigned int number, unsigned int digitCount, int base);
int coolNumberLogic(unsigned int array[], unsigned int digitsCount, int number);

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
                // findBinaryStrings();
                break;
            case '3':
                isExcitingNumber();
                break;
            case '4':
                isCoolNumber();
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
 * @brief a recursive function that counts the number of digits the number have.
 *
 * @param number the number we count the digits of.
 * @param base the base of the number
 *
 * @return the digit count of the given number.
 */
unsigned int countDigits(int number, int base) {
    // variable to sum all the digits. start at 0 so we can calc.
    static unsigned int sum = 0;

    /*
    the sumSaver is here to save the sum we got after all the calc.
    by using a saver we can reset the sum to 1 for the next calc.
    */
    unsigned int sumSaver;

    // the exit case! number /base gives the next digit. if we get 0 that means no more digits.
    if (number == 0) {
        sumSaver = sum;

        // reset the sum for next calc.
        sum = 0;
        return sumSaver;
    }

    /*
    each run of the function add to the sum.
    even the first one, because number/base will at the end "skip" the last digit.
    so we make up for that.
    */
    sum++;
    return countDigits(number / base, base);
}

/**
 * @brief a recursive function to calc the number^power by.
 *
 * @param number the base we want to power.
 * @param powerBy the amount we power by the number.
 *
 * @return the result of number^powerBy.
 */
int power(int number, int powerBy) {
    // variable to sum all the times we multiply. start at 1 so we can calc and not affect multiplication.
    static int sum = 1;

    /*
    the sumSaver is here to save the sum we got after all the calc.
    by using a saver we can reset the sum to 1 for the next calc.
    */
    int sumSaver;

    // the exit case! we reduce the powerBy by 1 for each calc round.
    if (powerBy == 0) {
        sumSaver = sum;

        // reset the sum for next calc.
        sum = 1;
        return sumSaver;
    }

    // the actual calc of the power.
    sum = sum * number;

    // the -1 of powerBy is to count how much to multiply is left.
    return power(number, powerBy - 1);
}

/**
 * @brief this function change an array to an array with the digits of the given number
 * each index is a digit. from left to right. 14 -> [1,4]
 *
 * @param array the array to change
 * @param number The number we are creating the array from.
 * @param digitsCount the number of digits in the given number
 * @param base the base of the given number
 */
void changeToDigitsArray(unsigned int array[], unsigned int number, unsigned int digitsCount, int base) {
    if (digitsCount == 0) {
        array[0] = 0;
    } else {
        for (int i = 0; i < digitsCount; i++) {
            // get the digit
            array[i] = number % base;

            // remove that digit
            number = number / base;
        }
    }
}

/**
 * @brief this function flip the number. reverse the digits.
 *
 * @param number the number to reverse the digit of
 * @param digitsCount the number of digits in the given number
 * @param base the base of the given number
 *
 * @return the reversed number
 */
unsigned int reverseNumber(unsigned int number, unsigned int digitsCount, int base) {

    unsigned int reversedNum = 0;

    for (int i = 0; i < digitsCount; i++) {

        int power = 1; // neutral to multiplication

        /*
        digits - i to get the digit index.
        and -1 to fix counting from 0 for power calc.
        */
        for (int j = 0; j < digitsCount - i - 1; j++) {
            power *= base;
        }

        // num % 10 gets the first digit
        reversedNum = reversedNum + (number % base) * power;
        number = number / base; // remove the last digit
    }

    return reversedNum;
}

/**
 * @brief this function shift the given array one cell to the left. (removing the most left cell)
 *
 * @param array the given array to move
 * @param arrayLength the length of the array
 */
void shiftArrayToLeft(unsigned int array[], int arrayLength) {
    // start from 1 (to get rid of the 0 cell).
    for (int i = 1; i < arrayLength; i++) {
        array[i] = array[i - 1];
    }
}

// Important functions for the options.

/**
 * @brief Finds all the binary strings that match the user's length and print all
 * but the strings with consecutive '1'.
 */
void findBinaryStrings() {
    // take a length from the user
    printf("Enter length:\n");

    int length;
    scanf(" %d", &length);

    // make sure we are leaving an empty buffer after the scan.
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

/**
 * @brief print to the user if the given number is an exciting number!
 * exciting number is like 153 = 1^3 + 5^3 + 3^3 = 153. (the digits power the number length sum).
 */
void isExcitingNumber() {
    // take the number to check from the user.
    printf("Enter a natural number:\n");

    unsigned int number;
    scanf(" %d", &number);

    // make sure we are leaving an empty buffer after the scan.
    cleanBuffer();

    // first we fetch the digits count for the calc.
    unsigned int digitsCount = countDigits(number, DECIMAL_BASE);

    if (sumDigitsPowerLength(number, digitsCount, DECIMAL_BASE) == number) {
        // this is the criteria of an exciting number. (sum of each digit^length)
        printf("The number is exciting\n");
    } else {
        printf("The number is not exciting\n");
    }
}

/**
 * @brief a recursive function that calc the sum of the each digit^length.
 *
 * @param number The number we are checking if it's exciting.
 * @param digitsCount the number of the over all digits. needed for power calcs.
 * @param base  the base of the number.
 *
 * @return the sum of the each digit^length.
 */
unsigned long sumDigitsPowerLength(unsigned int number, unsigned int digitsCount, int base) {
    // variable to sum all the numbers. start at 0 so we can calc.
    static unsigned long sum = 0;

    /*
    the sumSaver is here to save the sum we got after all the calc.
    by using a saver we can reset the sum to 1 for the next calc.
    */
    int sumSaver;

    // the exit case! number /10 gives the next digit. if we get 0 that means no more digits.
    if (number == 0) {
        sumSaver = sum;

        // reset the sum for next calc.
        sum = 0;
        return sumSaver;
    }

    // fetch the digit of the number
    unsigned int digit = number % base;

    sum = sum + power(digit, digitsCount);

    return sumDigitsPowerLength(number / base, digitsCount, base);
}

/**
 * @brief print to the user if the given number is cool or not.
 * cool number is the a number that appear in the series that's made like:
 * - create a series with the digits. 14 -> a1 = 1, a2 = 4.
 * - now a3 = 1 + 4, and so on.
 * - the number of the items to sum each time is the digit count of the number.
 */
void isCoolNumber() {
    // take a number from user to check
    printf("Enter a natural number:\n");

    unsigned int number;
    scanf(" %d", &number);

    // make sure we are leaving an empty buffer after the scan.
    cleanBuffer();

    // first we fetch the digits count for the calc.
    unsigned int digitsCount = countDigits(number, DECIMAL_BASE);

    /*
    we reverse the number to input the digits in the left -> order.
    it's easier to take the right -> so we just flip the number
    */
    unsigned int reversedNumber = reverseNumber(number, digitsCount, DECIMAL_BASE);

    // create an unsigned int array
    unsigned int theSeries[ARRAY_LENGTH];

    // push all the digits to the right cells.
    changeToDigitsArray(theSeries, reversedNumber, digitsCount, DECIMAL_BASE);

    // inform the user if the number is cool
    if (coolNumberLogic(theSeries, digitsCount, number)) {
        printf("The number is cool\n");
    } else {
        printf("The number is not cool\n");
    }
}

/**
 * @brief this function check if the given number is cool or not.
 * cool number is the a number that appear in the series that's made like:
 * - create a series with the digits. 14 -> a1 = 1, a2 = 4.
 * - now a3 = 1 + 4, and so on.
 * - the number of the items to sum each time is the digit count of the number.
 *
 * @param array The series with the digits in each cell.
 * @param digitsCount how many digits there are in the number that made the array.
 * @param number the number we are checking
 *
 * @return 0 if the number is not cool, 1 if it's.
 */
int coolNumberLogic(unsigned int array[], unsigned int digitsCount, int number) {
    // variable to sum the additive
    unsigned long sum;

    // count the loop steps
    int counter = 0;

    /*
    outer loop to save the sum into the not needed cell for the further calc.
    we covered all cases of return so while will not be an infinite loop.
    */
    while (1 && number != 0) {
        // each time reset the sum to have a clean sum
        sum = 0;
        // the inner loop is to sum the digits according to the definition of cool number.
        for (int i = 0; i < digitsCount; i++) {
            sum = sum + array[i];

            // exit case! if sum = number it's a cool number.
            if (sum == number) {
                return 1;

                // exit case ! if the sum is bigger that's mean the number isn't cool (we passed it).
            } else if (sum > number) {
                return 0;
            }
        }

        // digit count can't be zero. but if somehow it is... we wont divide.
        if (digitsCount != 0) {
            // each time put the sum in the index to clear (0 - digitsCount) for further calc.
            int indexToClear = counter % digitsCount;
            array[indexToClear] = sum;
        }

        counter++;
    }

    // the only case we get here is if the number is 0. and 0 is a cool number so return 1..
    return 1;
}
