// (89110, Spring 2023, Assignment #2, Tal Ben Naim, 212749071, bennait3)
#include <stdio.h>

// defines related to option 1. Hourglass
#define SAND_ON_TOP '1'
#define SAND_ON_BOTTOM '0'
#define MIN_HOURGLASS_SIZE 3

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
        // scanf until we see \n, then we save that \n in the buffer cleaner
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

                // scanf until we see \n, then we save that \n in the buffer cleaner
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
                break;
            }

            case '3': {
                break;
            }

            case '4': {
                break;
            }

            case '5': {
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