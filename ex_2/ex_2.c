// (89110, Spring 2023, Assignment #2, Tal Ben Naim, 212749071, bennait3)
#include <stdio.h>

// general defines
#define INDEX_OF_LAST_BIT ((sizeof(int) * 8) - 1)
#define LARGEST_SINGED_INT -2147483648
#define NEW_LINE_ASCII 10

// defines related to option 1. Hourglass
#define SAND_ON_TOP '1'
#define SAND_ON_BOTTOM '0'
#define MIN_HOURGLASS_SIZE 3

// defines related to option 4. Convert to Decimal
#define MIN_BASE 2
#define MAX_BASE 9

// defines related to option 5. Base64 to Decimal
#define START_NUMBERS_RANGE_BASE64 52
#define END_NUMBERS_RANGE_BASE64 61

int main() {

    char choice;

    do {
        // ask the user to pick an option.
        printf("Choose an option:\n");
        printf("0. Exit\n");
        printf("1. Hourglass\n");
        printf("2. Reverse bits\n");
        printf("3. Reverse digits\n");
        printf("4. Convert to Decimal\n");
        printf("5. Base64 to Decimal\n");
        printf("6. Swap bits\n");

        scanf("%c", &choice);

        //  to clean the buffer: scanf until we see \n, then we save that \n in the buffer cleaner
        char bufferCleaner;
        scanf("%[^\n]");
        scanf("%c", &bufferCleaner);

        // if the choice is any other char then '0' - '6' its invalid.
        if (choice < '0' || choice > '6') {
            printf("Invalid option\n");
        }

        switch (choice) {
            case '1': {
                int size;
                char flag;

                printf("Enter size:\n");
                scanf(" %d", &size);

                printf("Enter flag:\n");
                scanf(" %c", &flag);

                //  to clean the buffer: scanf until we see \n, then we save that \n in the buffer cleaner
                char bufferCleaner;
                scanf("%[^\n]");
                scanf("%c", &bufferCleaner);

                // size should be bigger than min size, and flag should be either of the one exists.
                if (size < MIN_HOURGLASS_SIZE || (flag != SAND_ON_TOP && flag != SAND_ON_BOTTOM)) {
                    printf("Invalid Parameters\n");
                    break;
                }

                // create the top of the hourglass
                for (int i = 0; i < size; i++) {
                    printf("-");
                }

                // a new line after the top
                printf("\n");

                // create the first half of the hourglass
                int sizeSaver = size;
                int spacesToPrint = 0;

                // each half of the hourglass contains half the size of rows. (without the X row in odd).
                int timeToRun = size / 2;

                for (int i = 0; i < timeToRun; i++) {

                    // print all the spaces between rows
                    for (int k = 0; k < spacesToPrint; k++) {
                        printf(" ");
                    }

                    for (int j = 0; j < sizeSaver; j++) {

                        // first char of the row we print "\"
                        if (j == 0) {
                            printf("\\");

                            // last char of the row we print "/"
                        } else if (j == sizeSaver - 1) {
                            printf("/");
                        } else {

                            // print sand on top if it's the flag. else, don't.
                            if (flag == SAND_ON_TOP) {
                                printf(".");
                            } else {
                                printf(" ");
                            }
                        }
                    }

                    // new line between every row
                    printf("\n");

                    // 1 space is added after every row to keep the shape.
                    spacesToPrint++;

                    // every row shrinks in size by 2 to make the shape.
                    sizeSaver -= 2;
                }

                // print X if hourglass size is odd
                if (size % 2 == 1) {

                    for (int k = 0; k < spacesToPrint; k++) {
                        printf(" ");
                    }

                    spacesToPrint--;
                    printf("X\n");
                }

                // create the second half of the hourglass
                for (int i = 0; i < timeToRun; i++) {

                    // print all the spaces between rows
                    for (int k = 0; k < spacesToPrint; k++) {
                        printf(" ");
                    }

                    /*
                    - every row grows in size by 2 to make the shape.
                    - we do it before the loop because we are starting at 0/1 from the first half.
                    */
                    sizeSaver += 2;

                    for (int j = 0; j < sizeSaver; j++) {

                        // first char of the row we print "/"
                        if (j == 0) {
                            printf("/");
                            // last char of the row we print "\"
                        } else if (j == sizeSaver - 1) {
                            printf("\\");
                        } else {

                            // print sand on top if it's the flag. else, don't.
                            if (flag == SAND_ON_BOTTOM) {
                                printf(".");
                            } else {
                                printf(" ");
                            }
                        }
                    }

                    // new line between every row
                    printf("\n");

                    // 1 space is remove after every row to keep the shape.
                    spacesToPrint--;
                }

                // create the bottom of the hourglass
                for (int i = 0; i < size; i++) {
                    printf("-");
                }

                // new line at the end
                printf("\n");

                break;
            }

            case '2': {
                int number, numberSaver;
                int flippedNumber = 0;
                int digit = 0;

                // take input from user
                printf("Enter a number:\n");
                scanf("%d", &number);

                //  to clean the buffer: scanf until we see \n, then we save that \n in the buffer cleaner
                char bufferCleaner;
                scanf("%[^\n]");
                scanf("%c", &bufferCleaner);

                for (int i = 0; i < sizeof(int) * 8; i++) {

                    // isolate the digit 1/0 and push all the way to the left
                    numberSaver = number >> i;
                    numberSaver = numberSaver << INDEX_OF_LAST_BIT;

                    // digit is on the most left so 1 = largest_signed_int
                    if (numberSaver == LARGEST_SINGED_INT) {
                        digit = 1;
                    } else if (numberSaver == 0) {
                        digit = 0;
                    }

                    /*
                    move one for every difference between the last index and the current one
                    that way -> push the bit to the right place in the flipped.
                    */
                    for (int j = i; j < INDEX_OF_LAST_BIT; j++) {
                        digit = digit << 1;
                    }
                    numberSaver = digit;

                    // flippedNumber starts out as 0,in every index we switch according to the new bit - using |.
                    flippedNumber = flippedNumber | numberSaver;
                }

                printf("The reversed number is %d\n", flippedNumber);

                break;
            }

            case '3': {
                int num, numSaver;
                int digits = 0, reversedNum = 0;
                printf("Enter a number:\n");
                scanf(" %d", &num);

                //  to clean the buffer: scanf until we see \n, then we save that \n in the buffer cleaner
                char bufferCleaner;
                scanf("%[^\n]");
                scanf("%c", &bufferCleaner);

                numSaver = num;

                // this while target is to find how many digits there are in num.
                while (num != 0) {
                    num = num / 10; // get num without first digit each time
                    digits++;
                }

                num = numSaver;

                for (int i = 0; i < digits; i++) {

                    int power = 1; // neutral to multiplication

                    /*
                    digits - i to get the digit index.
                    and -1 to fix counting from 0 for power calc.
                    */
                    for (int j = 0; j < digits - i - 1; j++) {
                        power *= 10; // base for decimal...
                    }

                    // num % 10 gets the first digit
                    reversedNum = reversedNum + (num % 10) * power;
                    num = num / 10; // remove the last digit
                }

                printf("The reversed number is %d\n", reversedNum);
                break;
            }

            case '4': {

                printf("Enter base:\n");
                int base;

                scanf(" %d", &base);

                // if the base is not in the bases supported ranged.
                if (base < MIN_BASE || base > MAX_BASE) {
                    printf("Invalid Base\n");
                    break;
                }

                //  to clean the buffer: scanf until we see \n, then we save that \n in the buffer cleaner
                char bufferCleaner;
                scanf("%[^\n]");
                scanf("%c", &bufferCleaner);

                printf("Enter a number:\n");
                char number;

                int invalidBase = 0;
                int convertedNumber = 0;

                // run over the input until it's empty, each time we get the char to work with
                do {
                    scanf("%c", &number);

                    // if input is empty (user have to press "enter" and create a new line to end)
                    if (number == NEW_LINE_ASCII) {
                        continue;
                    }

                    // '0' is the starting point of numbers in ascii.
                    if (number < '0' || number >= (base + '0')) {
                        printf("Invalid character %c in base %d\n", number, base);
                        invalidBase = 1;
                        break;
                    }

                    // get the real number
                    number = number - '0';

                    convertedNumber = convertedNumber * base + number;

                    // we stop if new line is present. same reason as above comment.
                } while (number != NEW_LINE_ASCII);

                // if the base is invalid we break again cause one break won't exit the main switch.
                if (invalidBase) {
                    break;
                }

                printf("The converted number is %u\n", convertedNumber);

                //  to clean the buffer: scanf until we see \n, then we save that \n in the buffer cleaner
                scanf("%[^\n]");
                scanf("%c", &bufferCleaner);

                break;
            }

            case '5': {
                printf("Enter a number in base 64:\n");

                char number;
                int base = 64;
                long convertedNumber = 0;

                // run over the input until it's empty, each time we get the char to work with
                do {
                    scanf("%c", &number);

                    // if input is empty (user have to press "enter" and create a new line to end)
                    if (number == NEW_LINE_ASCII) {
                        continue;
                    }

                    // 'A' is the starting point of capital letters in ascii 'Z' the last.
                    int capitalLetter = (number >= 'A' && number <= 'Z');

                    // 'a' is the starting point of small letters in ascii 'Z' the last.
                    int smallLetter = (number >= 'a' && number <= 'z');

                    // '0' is the starting point of numbers in ascii '9' the last.
                    int numbersIn64 = (number >= '0' && number <= '9');

                    int specialCharsIn64 = (number == '/' || number == '+');
                    // beside the letters we have + and / in base 64
                    if (!capitalLetter && !smallLetter && !numbersIn64 && !specialCharsIn64) {
                        printf("Invalid character %c in base %d\n", number, base);
                        break;
                    }

                    // in the if's bellow, we are subtracting smallest number in the catagories
                    if (capitalLetter) {
                        number = number - 'A';
                    }

                    if (smallLetter) {
                        number = number - 'a';
                    }

                    if (numbersIn64) {
                        /*
                        to make up for the diff in numbers in base64 and ascii we add the different between
                        starting point
                        */
                        number = number + (START_NUMBERS_RANGE_BASE64 - '0');
                    }

                    if (specialCharsIn64) {

                        if (number == '+') {
                            // 62 is the value of + in base64
                            number = 62;

                        } else if (number == '/') {

                            // 62 is the value of + in base64
                            number = 63;
                        }
                    }

                    convertedNumber = convertedNumber * base + number;

                    // we stop if new line is present. same reason as above comment.
                } while (number != NEW_LINE_ASCII);

                printf("The number in Decimal is %ld\n", convertedNumber);

                //  to clean the buffer: scanf until we see \n, then we save that \n in the buffer cleaner
                char bufferCleaner;
                scanf("%[^\n]");
                scanf("%c", &bufferCleaner);

                break;
            }

            case '6': {
                break;
            }

            default:
                break;
        }
        // as long as the user don't choose the exit option -> keep going.
    } while (choice != '0');
}