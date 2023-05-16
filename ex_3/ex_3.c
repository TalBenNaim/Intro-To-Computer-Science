// (89110, Spring 2023, Assignment #3, Tal Ben Naim, 212749071, bennait3)
#include <stdio.h>

// Defines

#define NEW_LINE_ASCII 10

// defines related to option 1. expression evaluator

// a value who is illegal but will put us in the loop to start.
#define START_VALUE 'S'

// a double value to differentiate from the rest. means error.
#define ERROR 0.1

// defines related to option 3. BINARY STRINGS
#define START_RANGE_BINARY_STRINGS 1
#define END_RANGE_BINARY_STRINGS sizeof(int) * 8

// 10 is the optimal array length - 10 digits of unsigned int.
#define ARRAY_LENGTH 10
#define DECIMAL_BASE 10
#define BINARY_BASE 2

// defines related to option 5. COUNT PATHS
#define MOVE_LIMIT 3

// Functions declaration.

// general functions
void printMenu();
void cleanBuffer();
int isOptionValid(char option);

unsigned int countDigits(int number, int base);

int power(int number, int powerBy);

unsigned int reverseNumber(unsigned int number, unsigned int digitsCount, int base);

void printBinary(long number, int length);

int isNumber(char c);

int isOperator(char c);

double operate(int number, int secNumber, char operator);
// All the options
void expressionEvaluator();
double expressionEvaluatorLogic(char current, char previous, double sum);

void findBinaryStrings();
void binaryStringsLogic(int length);
int consecutiveOnes(long number);

void isExcitingNumber();
unsigned long sumDigitsPowerLength(unsigned int number, unsigned int digitsCount, int base);

void isCoolNumber();
void changeToDigitsArray(unsigned int array[], unsigned int number, unsigned int digitCount, int base);
int coolNumberLogic(unsigned int array[], unsigned int digitsCount, unsigned long number);

void printPathsCount();
unsigned long countPaths(unsigned int width, unsigned int height, int moveLimit, int movesRight, int movesDown);

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
                expressionEvaluator();
                break;
            case '2':
                findBinaryStrings();
                break;
            case '3':
                isExcitingNumber();
                break;
            case '4':
                isCoolNumber();
                break;
            case '5':
                printPathsCount();
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

    // when we get 0 from the start
    if (number == 0 && sum == 0) {
        // 0 -> 1 digits.
        return 1;
    }

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
        for (unsigned int i = 0; i < digitsCount; i++) {
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

    for (unsigned int i = 0; i < digitsCount; i++) {

        int power = 1; // neutral to multiplication

        /*
        digits - i to get the digit index.
        and -1 to fix counting from 0 for power calc.
        */
        for (unsigned int j = 0; j < digitsCount - i - 1; j++) {
            power *= base;
        }

        // num % 10 gets the first digit
        reversedNum = reversedNum + (number % base) * power;
        number = number / base; // remove the last digit
    }

    return reversedNum;
}

/**
 * @brief print the given number in binary
 *
 * @param number the number to print in binary
 * @param length the length of the given number in binary - 1. (for proper shifting)
 */
void printBinary(long number, int length) {
    // exit case! when we are out of digits left.
    if (length == 0) {
        printf("\n");
        return;
    }

    // move the the current bit we are looking at (from left to right) all the way to the right;
    int bit = number >> (length - 1);

    // the reminder of 2 is odd/even and thats dictating the most right bits.
    int digit = bit % 2;

    printf("%d", digit);

    // each time move the number to the next target digit as well as the length.
    return printBinary(number, length - 1);
}

/**
 * @brief the function check if the given char is a number
 *
 * @param c the given char to check
 *
 * @return 1 if number 0 if not.
 */
int isNumber(char c) {

    // if c between 0 and 9 its a number.
    if (c >= '0' && c <= '9') {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief the function check if the given char is an operator
 *
 * @param c the given char to check
 *
 * @return 1 if operator 0 if not
 */
int isOperator(char c) {
    // if c is any of these return 1
    switch (c) {
        case '+':
            return 1;
            break;
        case '-':
            return 1;

            break;
        case '*':
            return 1;

            break;
        case '/':
            return 1;

            break;
    }
    // return 0 if not.
    return 0;
}

/**
 * @brief this function gets two numbers and operate according to the operator
 *
 * @param number the first number to start operation
 * @param secNumber the second number to continue operation
 *
 * @return the result from the operation or ERROR.
 */
double operate(int number, int secNumber, char operator) {
    switch (operator) {
        case '+':
            return number + secNumber;
            break;
        case '-':
            return number - secNumber;

            break;
        case '*':
            return number * secNumber;

            break;
        case '/':
            if (secNumber == 0) {
                return ERROR;
            } else {
                return number / secNumber;
            }

            break;
    }

    return 0;
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
    if (length < START_RANGE_BINARY_STRINGS || (unsigned)length > END_RANGE_BINARY_STRINGS) {
        printf("Invalid length\n");
        return;
    } else {
        // we can activate the logic!
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
    // we are using this number to run through all the numbers from 0 to how much we need.
    static long number = 0;

    // count the digits of the number in binary.
    int digitsCount = countDigits(number, BINARY_BASE);

    // print the numbers as long as we are in the range. (same length or below)
    if (digitsCount <= length) {
        // if the number doesn't have consecutiveOnes go and print it.
        if (consecutiveOnes(number) == 0) {
            // print all the missing zeros if we need to. digitsCount < length.
            if (digitsCount < length) {
                printf("%0*d", (length - digitsCount), 0);
            }
            // print the number in binary
            printBinary(number, digitsCount);
        }

        // move to the next number and check it's conditions. 0,1,2,3 ... as long as digitsCount <= length
        number++;
        return binaryStringsLogic(length);

        // exit case! when the number of digits have exceeded the length get out.
    } else {
        // reset the number for the next call.
        number = 0;
        return;
    }
}

/**
 * @brief this function take the given number and test if within its binary there is 1 after 1.
 *
 * @param number The number we are testing
 *
 * @return 1 - have within its binary there is 1 after 1. and 0 if doesn't have.
 */
int consecutiveOnes(long number) {
    // count the steps we have done
    static int counter = 0;

    // exit case, at the end we will get 0 from shifting.
    if ((number >> counter) == 0) {

        // reset counter;
        counter = 0;
        return 0;
    }
    // move each time the current bit to the right.
    int currentBit = number >> counter;

    // we update the counter to look at the bit in the next spot. moving it to the right.
    counter++;
    int nextBit = number >> counter;

    // exit case! if the bits in the right is 1 the number is odd and % will return 1.
    if (currentBit % 2 == 1 && nextBit % 2 == 1) {
        // reset counter;
        counter = 0;
        return 1;
    } else {
        // keep going with the same number, counter will keep going and further the func.
        return consecutiveOnes(number);
    }
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
int coolNumberLogic(unsigned int array[], unsigned int digitsCount, unsigned long number) {
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
        for (unsigned int i = 0; i < digitsCount; i++) {
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

/**
 * @brief print the number of paths in a table of given size where
 * the paths is the way for the dog (in the most left upper corner)
 * to get to the bone (in the most right bottom corner)
 */
void printPathsCount() {
    // take from the user the width and height of the table
    printf("Enter width and height:\n");

    unsigned width, height;
    scanf(" %d", &width);
    scanf(" %d", &height);

    // make sure we are leaving an empty buffer after the scan.
    cleanBuffer();

    unsigned long paths = countPaths(width, height, MOVE_LIMIT, 0, 0);

    printf("The number of paths is %lu\n", paths);
}

/**
 * @brief this function calc the paths in a table of given size where
 * the paths is the way for the dog (in the most left upper corner)
 * to get to the bone (in the most right bottom corner)
 *
 * @param width the width of the table
 * @param height the height of the table
 * @param moveLimit the limit of the moves the dog can move in a row.
 * @param movesRight count the moves we did to the right - start at 0
 * @param movesDown count the moves we did down - start at 0
 *
 * @return the number of paths.
 */
unsigned long countPaths(unsigned int width, unsigned int height, int moveLimit, int movesRight, int movesDown) {

    // exit case! when width or height = 1 there is one path to the bone.
    if (width == 1 || height == 1) {
        // also that way we count the times
        return 1;
    }

    // if we exceed moves it's an invalid path. also -1 move right.
    if ((unsigned)movesRight > width - 1 || (unsigned)movesDown > height - 1) {
        return 0;
    }

    // count the paths
    unsigned long paths = 0;

    // if we still yet to exceed the limit, keep going
    if (movesRight < moveLimit) {
        // we are going right so remove 1 width each move. and add 1 to right.
        paths += countPaths(width - 1, height, moveLimit, movesRight + 1, movesDown);
    }

    // if we still yet to exceed the limit, keep going
    if (movesDown < moveLimit) {
        // we are going right so remove 1 height each move. and add 1 to down.

        paths += countPaths(width, height - 1, moveLimit, movesRight, movesDown + 1);
    }

    // sum up with all the calls, in the end we get the paths we want.
    return paths;
}

/**
 *  @this function ask for expression from the user.
 */
void expressionEvaluator() {
    printf("Enter an expression:\n");

    char c;
    scanf(" %c", &c);

    // make sure we are leaving an empty buffer after the scan.
    cleanBuffer();

    // we put in the start value as well as 0 for the sum. (start from 0).

    // couldn't solve this question. so the trial is in grey to not effect other questions i did do.

    /*
    double result = expressionEvaluatorLogic(START_VALUE, START_VALUE, 0);
    printf("The result is :|%f|\n", result);
    */
}

/**
 * @brief this function holds all the logic in the expressionEvaluation.
 *
 * @param current the current char we are looking at
 * @param previous the previous char we're looking at
 * @param sum the sum of the expression
 *
 * @return the sum
 */
/*
double expressionEvaluatorLogic(char current, char previous, double sum) {
    while (current != NEW_LINE_ASCII) {
        previous = current;

        scanf("%c", &current);

        if (current == '(') {
            // at the start of each brackets we reset the sum for this call.
            sum = 0;
            expressionEvaluatorLogic(current, previous, sum);
        }

        if (isNumber(current) == 1) {
            if (isOperator(previous) == 1) {
                return current;
            }
        }

        if (isOperator(current) == 1) {
            if (isNumber(previous) == 1) {
                printf("%d", sum);
                sum += operate(previous, expressionEvaluatorLogic(current, previous, sum), current);
            }
        }

        if (current == ')') {
            return sum;
        }
    }
}
*/