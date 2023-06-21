// (89110, Spring 2023, Assignment #6, Tal Ben Naim, 212749071, bennait3)

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

// Defines
#define NEW_LINE_ASCII 10
#define LEGAL_AGE_TO_MARRY 18

// Funcs declarations

// -> Helper funcs
void printMenu();
void cleanBuffer();
int isChoiceValid(char option);
void sendToMission(char choice, FamilyHead *firstHuman);
Human **scanTree(FamilyHead *firstHuman, unsigned int *arrayLen);
Human **scanTreeFurther(Human *human, Human **dontScanAgain, unsigned int *index);
char *stringFromUser();
int isPtrInArray(Human **arrayOfPtr, void *ptr, unsigned int arrayLength);
int isNameFree(FamilyHead *firstHuman, char *nameToGive);
Human *getHumanByName(Human **array, unsigned int arrayLen, char *nameToFind);
int canMarry(Human *firstPerson, Human *secondPerson, FamilyHead *firstHuman);
int inSameFamily(Human *firstPerson, Human *secondPerson, FamilyHead *firstHuman);
void printStrNoNewLine(char *str);
FamilyHead *lastFamilyHead(FamilyHead *firstHuman);
Human *getYoungestChild(Human *parent);
void initializeHumanValues(Human *toUpdate, char *name, unsigned int age);
void freeAllFamilyHeads(FamilyHead *firstHuman);
void freeAll(FamilyHead *firstHuman);

// -> Missions funcs
void inputToCreateFamilyHead(FamilyHead *firstHuman);
void createFamilyHead(FamilyHead *firstHuman, char *name, unsigned int age);

void marryTwoHumans(FamilyHead *firstHuman);

void inputToCreateNewBorn(FamilyHead *firstHuman);
void createNewBorn(Human *firstParent, Human *secondParent, char *babyName);

void printFamily(FamilyHead *firstHuman);
void printFamilyFurther(Human *human, unsigned int tabTimes);
void printHumanFormat(Human *humanToPrint);

void yearsPass(FamilyHead *firstHuman);

void countHumans(FamilyHead *firstHuman);

void inputToPrintCousins(FamilyHead *firstHuman);
Human **getCousinsArray(Human *human, unsigned int degree, Human **array, unsigned int *index);

/**
 * @brief Main function that wait for user input to navigate the user
 * to the right part of the program according to the input.
 * if memory allocation fail we exit the program.
 *
 * @return 0 if the program runs successfully
 */
int main() {

    // create the firstHuman for the run.
    FamilyHead *firstHuman = (FamilyHead *)malloc(sizeof(FamilyHead));
    if (firstHuman == NULL) {
        exit(1);
    }

    // reset the value and next to null
    firstHuman->properties = NULL;
    firstHuman->next = NULL;

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

        // send the user to the right mission according to his choice.
        sendToMission(choice, firstHuman);
    }

    // free all the structs in this program run before closing it.
    freeAll(firstHuman);

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
 * @brief this function gets a choice and moves the user to the right missions
 *
 * @param choice the choice the user made
 * @param firstHuman he is needed in all the missions
 */
void sendToMission(char choice, FamilyHead *firstHuman) {
    // depending on the user's choice navigate the user to the right program.
    switch (choice) {
        case '1':
            inputToCreateFamilyHead(firstHuman);
            break;
        case '2':
            marryTwoHumans(firstHuman);
            break;
        case '3':
            inputToCreateNewBorn(firstHuman);
            break;
        case '4':
            printFamily(firstHuman);
            break;
        case '5':
            yearsPass(firstHuman);
            break;
        case '6':
            countHumans(firstHuman);
            break;
        case '7':
            inputToPrintCousins(firstHuman);
            break;
        default:
            break;
    }
}

/**
 * @brief this function scans the tree, visiting every member without repetition and return array containing them.
 * if memory allocation fail we exit the program.
 *
 * @param firstHuman the first family head in the whole tree.
 * @param arrayLen pointer to len of the array so we can "return" it as well
 *
 * @return the array with every member.
 */
Human **scanTree(FamilyHead *firstHuman, unsigned int *arrayLen) {
    // create an array of humans , empty for now. (allocate memory)
    Human **array = (Human **)malloc(sizeof(Human *));
    if (array == NULL) {
        exit(1);
    }

    // save the size of the array.
    unsigned int index = 0;
    if (firstHuman->properties == NULL) {
        return NULL;
    }

    while (firstHuman != NULL) {
        // the actual length is always the index + 1 because we start from 0 in the index count.
        *arrayLen = index + 1;

        /*
        expand the memory according to the size thous far (*arrayLen)
        */
        array = (Human **)realloc(array, (*arrayLen) * sizeof(Human *));
        if (array == NULL) {
            exit(1);
        }

        // insert the human in the array in the right place.
        array[index] = firstHuman->properties;

        // send his firstChild to the scanTreeFurther

        // if there is a firstChild check further
        if (firstHuman->properties->firstChild != NULL) {
            array = scanTreeFurther(firstHuman->properties->firstChild, array, &index);
        }

        firstHuman = firstHuman->next;

        // there is a human to add so index goes by 1. (prep for next iteration)
        index++;
    }

    return array;
}

/**
 * @brief this function scan the tree further, all the members after each family head.
 * this function recursively calls itself for the firstChild and sibling of each human.
 * if memory allocation fail we exit the program.
 *
 * @param human the human to scan
 * @param dontScanAgain an array to save the humans we don't want to scan again. (if we won't through them).
 */
Human **scanTreeFurther(Human *human, Human **dontScanAgain, unsigned int *index) {
    if (human != NULL) {
        // if he's in the dontScanAgain we return before processing
        if (isPtrInArray(dontScanAgain, human, *index) == 1) {
            return dontScanAgain;
        }
        // adding new human so ++ the index.
        *index = (*index) + 1;

        /*
        expand the memory according to the size thous far
        we allocated index+1 to offset the diff of array numbering to actual numbers of memory blocks
        */
        dontScanAgain = (Human **)realloc(dontScanAgain, ((*index) + 1) * sizeof(Human *));
        if (dontScanAgain == NULL) {
            exit(1);
        }

        // add him to the dontScanAgain array
        dontScanAgain[*index] = human;

        // send this human firstChild to scanTreeFurther
        dontScanAgain = scanTreeFurther(human->firstChild, dontScanAgain, index);

        // send this human siblings to scanTreeFurther
        dontScanAgain = scanTreeFurther(human->sibling, dontScanAgain, index);
    }

    return dontScanAgain;
}

/**
 * @brief create a string from the user inputs.
 * if memory allocation fail we exit the program.
 *
 * @return the string.
 */
char *stringFromUser() {
    // initialize the str and allocate memory
    char *str = (char *)malloc(sizeof(char));
    if (str == NULL) {
        exit(1);
    }

    unsigned int index = 0;
    char usersInput;
    do {
        // take the user input into the current index of the str
        scanf("%c", &str[index]);
        usersInput = str[index];

        // move the index
        index++;

        // expand the memory according to the size thous far
        str = (char *)realloc(str, (index + 1) * sizeof(char));
        if (str == NULL) {
            exit(1);
        }

        // check the index we just inserted to and see if it's new line.
    } while (usersInput != NEW_LINE_ASCII);

    // return the pointer to the string we built
    return str;
}

/**
 * @brief check if the giving pointer is in the array of ptr
 *
 * @param arrayOfPtr the array of pointers to check in
 * @param ptr the pointer to look out for
 * @param arrayLength the length of the array
 *
 * @return 1 is in array, 0 isn't
 */
int isPtrInArray(Human **arrayOfPtr, void *ptr, unsigned int arrayLength) {
    // loop through each element of the array
    for (unsigned int i = 0; i < arrayLength; i++) {
        // if an element is equal to the ptr we are looking for, return 1;
        if (arrayOfPtr[i] == ptr) {
            return 1;
        }
    }

    // we didn't find it
    return 0;
}

/**
 * @brief get the last familyHead in the familyHead struct
 *
 * @param firstHuman the head of the familyHead struct
 *
 * @return the last node in the familyHead
 */
FamilyHead *lastFamilyHead(FamilyHead *firstHuman) {
    // an helper pointer to store the head and not change it.
    FamilyHead *helper = firstHuman;

    // go next node until we see a null.
    while (helper->next != NULL) {
        // move the helper to be the next node
        helper = helper->next;
    }
    // return the helper as the last node
    return helper;
}

/**
 * @brief this function initialize values into a human pointer.
 *
 * @param toUpdate pointer to human to update
 * @param name contains the name we want
 * @param age contains the age we want
 */
void initializeHumanValues(Human *toUpdate, char *name, unsigned int age) {
    // update each property
    toUpdate->age = age;
    toUpdate->name = name;
    toUpdate->firstChild = NULL;
    toUpdate->parent1 = NULL;
    toUpdate->parent2 = NULL;
    toUpdate->partner = NULL;
    toUpdate->sibling = NULL;
}

/**
 * @brief this function takes a name and check if its free in our humans array
 *
 * @param array the array of humans to check in
 * @param arrayLen the length of the array
 * @param nameToGive the name we want to check if its free
 *
 * @return 1 if the name is free, 0 if not.
 */
int isNameFree(FamilyHead *firstHuman, char *nameToGive) {
    // get the array with all the humans
    unsigned int arrayLen = 0;
    Human **array = scanTree(firstHuman, &arrayLen);

    // loop through every element
    for (unsigned int i = 0; i < arrayLen; i++) {
        // if the name of an element is the same as the name we want to give it's not free, return 0.
        if (strcmp(array[i]->name, nameToGive) == 0) {
            // free the array after use
            free(array);
            return 0;
        }
    }
    // free the array after use
    free(array);
    // couldn't find it so, it's free
    return 1;
}

/**
 * @brief this function gets a human from the array by it's name and return it.
 *
 * @param array the array of humans to check in
 * @param arrayLen the length of the array
 * @param nameToFind the name we want to find and return the human of
 *
 * @return the human with the same name, or null if it does not exists.
 */
Human *getHumanByName(Human **array, unsigned int arrayLen, char *nameToFind) {
    // loop through every element
    for (unsigned int i = 0; i < arrayLen; i++) {
        // if the name of an element is the same as the name we want to give it's not free, return 0.
        if (strcmp(array[i]->name, nameToFind) == 0) {

            return array[i];
        }
    }

    // couldn't find it so, it's free
    return NULL;
}

/**
 * @brief this function check if the two humans we get can marry
 *
 * @param firstPerson pointer to the first person to check
 * @param secondPerson pointer to the second person to check
 * @param firstHuman the head of the familyHead
 *
 * @return 1 they can marry, 0 they can't.
 */
int canMarry(Human *firstPerson, Human *secondPerson, FamilyHead *firstHuman) {
    // if any of them is already married they can't marry
    if (firstPerson->partner != NULL && secondPerson->partner != NULL) {
        return 0;
    }

    // if any of them is under the legal age (18)
    if (firstPerson->age < LEGAL_AGE_TO_MARRY && secondPerson->age < LEGAL_AGE_TO_MARRY) {
        return 0;
    }

    // if they are in the same family
    if (inSameFamily(firstPerson, secondPerson, firstHuman) == 1) {
        return 0;
    }

    // passed all the requirements now they can marry.
    return 1;
}

/**
 * @brief this function check if the two humans are in the same family
 *
 * @param firstPerson pointer to the first person to check
 * @param secondPerson pointer to the second person to check
 * @param firstHuman the head of the familyHead
 *
 * @return 1 if they are, 0 if they are not.
 */
int inSameFamily(Human *firstPerson, Human *secondPerson, FamilyHead *firstHuman) {

    // save the size of the array.
    unsigned int index = 0;
    if (firstHuman->properties == NULL) {
        return 0;
    }

    while (firstHuman != NULL) {
        // create an array of humans , empty for now. (allocate memory) we want to reset each round so it's okay here.
        Human **array = (Human **)malloc(sizeof(Human *));
        if (array == NULL) {
            exit(1);
        }

        array[index] = firstHuman->properties;

        index++;

        // send his firstChild to the scanTreeFurther

        if (firstHuman->properties->firstChild != NULL) {
            scanTreeFurther(firstHuman->properties->firstChild, array, &index);
        }

        if (isPtrInArray(array, firstPerson, index) == 1 && isPtrInArray(array, secondPerson, index) == 1) {
            return 1;
        }

        firstHuman = firstHuman->next;

        // reset the array.
        free(array);
        index = 0;
    }

    return 0;
}

/**
 * @brief print the given string without the new line.
 * @param str the pointer to the string to print
 */
void printStrNoNewLine(char *str) {
    int index = 0;
    while (str[index] != '\0' && str[index] != NEW_LINE_ASCII) {
        printf("%c", str[index]);
        index++;
    }
}

/**
 * @brief this function gets the youngest child the parent have.
 *
 * @param parent the parent to get the youngest child of
 *
 * @return the pointer of the youngest child
 */
Human *getYoungestChild(Human *parent) {
    // an helper pointer to store the head and not change it.
    Human *firstChild = parent->firstChild;

    // go next node until we see a null.
    while (firstChild->sibling != NULL) {
        // move the helper to be the next node
        firstChild = firstChild->sibling;
    }
    // return the helper as the last node
    return firstChild;
}

/**
 * @brief this function free all the nodes in the family head list.
 * we are free the each one recursively
 *
 * @param firstHuman the first human in the program. he holds all the family heads.
 */
void freeAllFamilyHeads(FamilyHead *firstHuman) {
    // if firstHuman exists
    if (firstHuman) {

        // free the next one recursively
        freeAllFamilyHeads(firstHuman->next);

        // free the current node
        free(firstHuman);

        return;
    }
}

/**
 * @brief free everything in the program, all the family heads and the humans.
 *
 * @param firstHuman the first human in the program. he holds all the family heads.
 */
void freeAll(FamilyHead *firstHuman) {
    // get an array of all the humans.
    unsigned int arrayLen = 0;
    Human **array = scanTree(firstHuman, &arrayLen);

    // free all humans through the array.
    for (unsigned int i = 0; i < arrayLen; i++) {
        free(array[i]);
    }

    // free the array after we used it.
    free(array);

    // free all the familyHeads before ending the program.
    freeAllFamilyHeads(firstHuman);
}

/**
 * @brief this function prints the human name and age according to the format
 * - name (age)
 *
 * @param humanToPrint the human to print
 */
void printHumanFormat(Human *humanToPrint) {
    // print the name
    printStrNoNewLine(humanToPrint->name);

    // print the age
    printf(" (%d)", humanToPrint->age);
}

void printChildrens(Human *human) {
    Human *firstChild = human->firstChild;
    while (firstChild != NULL) {
        printStrNoNewLine(firstChild->name);

        printf("\n");

        firstChild = firstChild->sibling;
    }
}

// -> Missions funcs

/**
 * @brief This function takes from the user a name and age, pass them to create the familyHead.
 *
 * @param firstHuman the pointer to the first human in the program
 */
void inputToCreateFamilyHead(FamilyHead *firstHuman) {
    // get name from user
    printf("Enter a name:\n");
    char *name = stringFromUser();

    // get age from user
    printf("Enter age:\n");
    unsigned int age;
    scanf("%u", &age);

    cleanBuffer();

    // check if the name we want exists in the array
    int exists = isNameFree(firstHuman, name);
    if (exists == 0) {
        printf("The name is already taken\n");
        return;
    }

    // create the familyHead with the name and age we want.
    createFamilyHead(firstHuman, name, age);
}

/**
 * @brief This function creates a family head with the name and age
 * if memory allocation fail we exit the program.
 *
 * @param firstHuman the pointer to the first human in the program
 * @param name the name of the human
 * @param age the age of the human
 */
void createFamilyHead(FamilyHead *firstHuman, char *name, unsigned int age) {
    // allocate memory to human pointer
    Human *newHumanPointer = (Human *)malloc(sizeof(Human));
    if (newHumanPointer == NULL) {
        exit(1);
    }

    // first familyHead? save the value to firstHuman
    if (firstHuman->properties == NULL) {
        firstHuman->properties = newHumanPointer;

        // not the first? get the last node of the familyHead and add to it the new one
    } else {
        // create the newHead
        FamilyHead *newHead = (FamilyHead *)malloc(sizeof(FamilyHead));
        if (newHead == NULL) {
            exit(1);
        }

        // reset the properties to new pointer and next to null
        newHead->properties = newHumanPointer;
        newHead->next = NULL;

        // get the last pointer and link the nextHead to it
        FamilyHead *lastPointer = lastFamilyHead(firstHuman);
        lastPointer->next = newHead;
    }

    // create the human with name and age, everything else is null, and put in the new pointer.
    initializeHumanValues(newHumanPointer, name, age);
}

/**
 * @brief this func take from the user two humans names and marry them if they can.
 *
 * @param firstHuman the pointer to the first human in the program
 */
void marryTwoHumans(FamilyHead *firstHuman) {
    // ask the user who he want's to marry with who
    printf("Enter the name of the first person:\n");
    char *firstPersonName = stringFromUser();

    printf("Enter the name of the second person:\n");
    char *secondPersonName = stringFromUser();

    // get the array with all the humans
    unsigned int arrayLen = 0;
    Human **array = scanTree(firstHuman, &arrayLen);

    // get them both by name
    Human *firstPerson = getHumanByName(array, arrayLen, firstPersonName);
    Human *secondPerson = getHumanByName(array, arrayLen, secondPersonName);

    // free array after use
    free(array);

    // if both persons exists
    if (firstPerson != NULL && secondPerson != NULL) {
        // if they can marry
        if (canMarry(firstPerson, secondPerson, firstHuman)) {

            printStrNoNewLine(firstPersonName);
            printf(" and ");
            printStrNoNewLine(secondPersonName);
            printf(" are now married\n");

            // assign the partner for each other
            firstPerson->partner = secondPerson;
            secondPerson->partner = firstPerson;

        } else {
            printf("Invalid marriage\n");
        }

    } else {
        printf("One of the persons does not exist\n");
    }
    // free the names and the objects
    free(firstPersonName);
    free(secondPersonName);
}

/**
 * @brief ask the users for two parents names and the baby name pass them to birth him if it possible.
 *
 * @param firstHuman the pointer to the first human in the program
 */
void inputToCreateNewBorn(FamilyHead *firstHuman) {
    // ask the user who he want's to marry with who
    printf("Enter the name of the first parent:\n");
    char *firstParentName = stringFromUser();

    printf("Enter the name of the second parent:\n");
    char *secondParentName = stringFromUser();

    // get the wanted baby name
    printf("Enter offspring's name:\n");
    char *babyName = stringFromUser();

    // get the array with all the humans
    unsigned int arrayLen = 0;
    Human **array = scanTree(firstHuman, &arrayLen);

    // get them both by name
    Human *firstParent = getHumanByName(array, arrayLen, firstParentName);
    Human *secondParent = getHumanByName(array, arrayLen, secondParentName);

    // free array after use
    free(array);

    // free the string of the names after we got the humans objs and the array itself.
    free(firstParentName);
    free(secondParentName);

    // if the parents exists
    if (firstParent != NULL && secondParent != NULL) {
        // check if they are married.
        if (firstParent->partner == secondParent) {

            // check if name is free for the baby
            int exists = isNameFree(firstHuman, babyName);
            if (exists == 0) {
                printf("The name is already taken\n");

                // its free so create the baby
            } else {
                createNewBorn(firstParent, secondParent, babyName);
            }
        } else {
            printf("The parents are not married\n");
        }
    } else {
        printf("One of the persons does not exist\n");
    }
}

/**
 * @brief this function createNewBorn with parents names and baby name the user chose.
 * if memory allocation fail we exit the program.
 *
 * @param firstParent the firstParent to create a new born
 * @param secondParent the secondParent to create a new born
 * @param babyName the baby name the users chose for the new born
 */
void createNewBorn(Human *firstParent, Human *secondParent, char *babyName) {
    // allocate memory to human pointer
    Human *newHumanPointer = (Human *)malloc(sizeof(Human));
    if (newHumanPointer == NULL) {
        exit(1);
    }

    // if it's their first child point to it.
    if (firstParent->firstChild == NULL) {
        firstParent->firstChild = newHumanPointer;
        secondParent->firstChild = newHumanPointer;

        // grab the latest
    } else {

        Human *lastPointer = getYoungestChild(firstParent);

        // add the human to the last node of the familyHead.
        lastPointer->sibling = newHumanPointer;
    }

    // create the human with name and age(default is 0), everything else is null, and put in the new pointer.
    initializeHumanValues(newHumanPointer, babyName, 0);

    // make them his parents
    newHumanPointer->parent1 = firstParent;
    newHumanPointer->parent2 = secondParent;

    // the baby was born!
    printStrNoNewLine(babyName);
    printf(" was born\n");
}

/**
 * @brief this functions ask the user for a name of a person and prints his family
 *
 * @param firstHuman the firstHuman in the program.
 */
void printFamily(FamilyHead *firstHuman) {
    // take the name of the person from the user
    printf("Enter the name of the person:\n");
    char *nameOfHuman = stringFromUser();

    // get the array with all the humans
    unsigned int arrayLen = 0;
    Human **array = scanTree(firstHuman, &arrayLen);

    // get the human object from the name
    Human *wantedHuman = getHumanByName(array, arrayLen, nameOfHuman);

    // free array after use, and the name
    free(array);
    free(nameOfHuman);

    if (wantedHuman != NULL) {
        // print the human itself according to the format.
        printHumanFormat(wantedHuman);

        // if the human is married print the partner and separate them with -
        if ((wantedHuman->partner) != NULL) {
            printf(" - ");
            printHumanFormat(wantedHuman->partner);

            // if there is a firstChild send him to even printFurther
            if ((wantedHuman->firstChild) != NULL) {
                // print new line before printing child
                printf("\n");
                printFamilyFurther(wantedHuman->firstChild, 1);
            }

            // can't have childrens without a partner
        } else {

            return;
        }

        // new line before coming back to options screen.
        printf("\n");
    } else {
        printf("The person does not exist\n");
    }
}

/**
 * @brief this function prints the family further
 *
 * @param human the human to start printing with
 */
void printFamilyFurther(Human *human, unsigned int tabTimes) {
    // if the human exists
    if (human != NULL) {
        // print tab for space
        for (unsigned int i = 0; i < tabTimes; i++) {
            printf("\t");
        }

        // print the human itself according to the format.
        printHumanFormat(human);

        // if the human is married print the partner
        if ((human->partner) != NULL) {
            // separate them with -
            printf(" - ");
            printHumanFormat(human->partner);

            // if there is a firstChild send him to even printFurther
            if ((human->firstChild) != NULL) {
                // print new line before printing child
                printf("\n");

                printFamilyFurther(human->firstChild, tabTimes + 1);
            }
        }

        if ((human->sibling != NULL)) {
            printf("\n");
            printFamilyFurther(human->sibling, tabTimes);
        }
    }
}

/**
 * @brief this function will update ages according to the year.
 *
 * @param firstHuman the first human in the program.
 */
void yearsPass(FamilyHead *firstHuman) {
    printf("Enter number of years:\n");
    unsigned int years;
    scanf("%d", &years);

    cleanBuffer();

    unsigned int arrayLen = 0;
    Human **array = scanTree(firstHuman, &arrayLen);

    for (unsigned int i = 0; i < arrayLen; i++) {
        array[i]->age = array[i]->age + years;
    }

    // free the array after we used it.
    free(array);
}

/**
 * @brief this function will return the number of humans so far
 *
 * @param firstHuman the first human in the program.
 */
void countHumans(FamilyHead *firstHuman) {
    // get the array of Humans from scanTree
    unsigned int arrayLen = 0;
    Human **array = scanTree(firstHuman, &arrayLen);

    // if the array isn't empty
    if (array != NULL) {
        // arrayLen = number of peoples
        if (arrayLen == 1) {
            printf("There is one person\n");
        } else {
            printf("There are %d people\n", arrayLen);
        }
    }

    // free the array after we used it.
    free(array);
}

/**
 * @brief this function takes the input to then print cousins of a person.
 *
 * @param firstHuman the first human in the program.
 */
void inputToPrintCousins(FamilyHead *firstHuman) {
    // take the name of the person from the user
    printf("Enter the name of the person:\n");
    char *nameOfHuman = stringFromUser();

    // take the degree level of the wanted cousin from the user
    printf("Enter the name of the person:\n");
    unsigned int degree;
    scanf("%d", &degree);

    cleanBuffer();

    // get the array with all the humans
    unsigned int arrayLen = 0;
    Human **array = scanTree(firstHuman, &arrayLen);

    // get the human object from the name
    Human *wantedHuman = getHumanByName(array, arrayLen, nameOfHuman);

    // free array after use, and the name
    free(array);
    free(nameOfHuman);

    if (wantedHuman != NULL) {
        // create an array of humans , empty for now. (allocate memory)
        Human **array = (Human **)malloc(sizeof(Human *));
        if (array == NULL) {
            exit(1);
        }
        // save the size of the array.
        unsigned int index = 0;
        array = getCousinsArray(wantedHuman, degree, array, &index);

        // print all the items in the array just to check it
        for (unsigned int i = 0; i < index + 1; i++) {
            printStrNoNewLine(array[i]->name);

            printf("\n");
        }

    } else {
        printf("The person does not exist\n");
    }
}

/**
 * @brief this function getCousinsArray of the wanted degree  for the given human
 *
 * @param firstHuman the first human in the program.
 * @param human the human to get the cousins of
 * @param degree the degree of the cousins to get
 *
 * @return pointer to the cousinsArray
 */
Human **getCousinsArray(Human *human, unsigned int degree, Human **array, unsigned int *index) {

    // exit case, if degree is 0 we are finished.
    if (degree == 0) {
        return array;
    }

    // if don't have any parents there is no reason to keep checking.
    if (human->parent1 == NULL) {
        return array;
    }

    // get the firstChild of your parents
    Human *firstChild = human->parent1->firstChild;

    // add children of firstChild and his sibling childrens
    while (firstChild != NULL) {

        /*
        expand the memory according to the size thous far
        we allocated index+1 to offset the diff of array numbering to actual numbers of memory blocks
        */
        array = (Human **)realloc(array, ((*index) + 1) * sizeof(Human *));
        if (array == NULL) {
            exit(1);
        }

        // add all firstChild childrens
        Human *child = firstChild->firstChild;
        array[*index] = child;

        // adding new human so ++ the index.
        *index = (*index) + 1;

        Human *sibling = child->sibling;
        while (sibling != NULL) {
            array = (Human **)realloc(array, ((*index) + 1) * sizeof(Human *));
            if (array == NULL) {
                exit(1);
            }

            // adding new human so ++ the index.
            *index = (*index) + 1;
            sibling = sibling->sibling;
        }

        array[*index] = firstChild;

        firstChild = firstChild->sibling;
    }

    // check forward with the parents, parent1 and parent2.
    return getCousinsArray(human->parent1, degree - 1, array, index);
    return getCousinsArray(human->parent2, degree - 1, array, index);
}