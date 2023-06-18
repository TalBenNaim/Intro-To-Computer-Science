// (89110, Spring 2023, Assignment #5, Tal Ben Naim, 212749071, bennait3)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structs
typedef struct Human {
    char *name;
    unsigned int age;
    struct Human *firstChild;
    struct Human *partner;
    struct Human *parent1;
    struct Human *parent2;
    struct Human *sibling;
} Human;

typedef struct FamilyHead {
    Human *properties;
    struct FamilyHead *next;
} FamilyHead;

// Funcs declarations

// -> Helper funcs
void printMenu();
void cleanBuffer();
int isChoiceValid(char option);
void scanTree(FamilyHead *firstHuman);
void scanTreeFurther(Human *human, Human dontScanAgain[], unsigned int index);

/**
 * @brief Main function that wait for user input to navigate the user
 * to the right part of the program according to the input.
 * if memory allocation fail we exit the program.
 *
 * @return 0 if the program runs successfully
 */
int main() {

    // save the option the user picked, initalized to 1 to enter while loop.
    char choice = 1;

    while (choice != '0') {
        // present the menu to the user and take his choice
        printMenu();

        scanf("%c", &choice);
        cleanBuffer();

        // inform the user about the invalid choice, then ask them again.
        if (!isChoiceValid(choice)) {
            printf("Invalid option\n");
        }

        // depending on the user's choice navigate the user to the right program.
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
            case '6':
                break;
            case '7':
                break;

            default:
                break;
        }
    }

    return 0;
}

// Funcs defintions

// -> Helper funcs

/**
 * @brief Print the menu of options to the user.
 */
void printMenu() {
    printf("Choose an option:\n");
    printf("0. Exit\n");
    printf("1. Add a head\n");
    printf("2. Marry two people\n");
    printf("3. New offspring\n");
    printf("4. Print family top-down\n");
    printf("5. Years pass\n");
    printf("6. Count people\n");
    printf("7. Print cousins\n");
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
int isChoiceValid(char choice) {

    // This program options range is 0 - 7.
    if (choice < '0' || choice > '7') {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief this function scans the tree, visiting every memeber without repetition
 * 
 * @param firstHuman the first family head in the whole tree.
 * 
*/
void scanTree(FamilyHead *firstHuman){
    // look at each familyHead - it's firstHuman right now
    // do something according to what we want
    if(firstHuman != NULL){
        // for now just print the name of the human
        printf("%s",firstHuman->properties->name);

        // send the next FH
        scanTree(firstHuman->next);

        // create an array of humans to not scan again, empty for now
        Human dontScanAgain[];
        static unsigned index = 0;
        // send his firstChild to the scanTreeFurther   
        scanTreeFurther(firstHuman->properties->firstChild, dontScanAgain, index);

        return;
    }
}

/**
 * @brief this function scan the tree further, all the memebers after each family head
 * 
 * @param human the human to scan
 * @param dontScanAgain an array to save the humans we don't want to scan again. (if we won't through them).
*/
void scanTreeFurther(Human *human, Human dontScanAgain[], unsigned int index){
    if(human != NULL){
        // add him to the dontScanAgain array

        // send this human firstChild to scanTreeFurther
        scanTreeFurther(human->firstChild,dontScanAgain);

        // send this human siblings to scanTreeFurther
        scanTreeFurther(human->sibling, dontScanAgain);

    }

}