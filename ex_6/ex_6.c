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
Human *getHumansInTree(FamilyHead *famHead, unsigned int index);
void addHumansBelow(Human *human, Human *array, unsigned int index);
int elementInArray(void *array, void *element, unsigned int arrayLength);

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
 * @brief save the pointers to every human in the current family tree.
 * if memory allocation fail we exit the program.
 *
 * @param firstHuman the first human created in this family tree.
 * @param index The starting index for the array to start at.
 *
 * @return a pointer to the array containing all the pointers to each human in the tree.
 */
Human *getHumansInTree(FamilyHead *famHead, unsigned int index) {
    // the array of pointers we return
    Human *humansInTree = (Human *)malloc(sizeof(Human));
    if (humansInTree == NULL) {
        exit(1);
    }

    if (famHead != NULL) {
        // check if famHead in array if not then add to array

        // send his firstChild to get further
        addHumansBelow(famHead->properties->firstChild, humansInTree, index);

        // get the next familyHead
        return getHumansInTree(famHead->next, index);
    }

    return humansInTree;
}

void addHumansBelow(Human *human, Human *array, unsigned int index) {

    if (human != NULL) {
        // check if human in array if not then add to array

        // send his firstChild to get further
        addHumansBelow(human->firstChild, array, index);

        // send his next sibling to get further
        addHumansBelow(human->sibling, array, index);

        // after adding exit the func
        return;
    }
}

int elementInArray(void *array, void *element, unsigned int arrayLength) {
}

/*
void freeAllNode(Node *node) {
    // if the node exists
    if (node == NULL) {
        // free the next node recursively
        freeAllNode(node->next);
        // free the current node
        free(node);

        // after freeing the current node, exit the func
        return;
    }
}
*/