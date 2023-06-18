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

// Defines
#define NEW_LINE_ASCII 10

// Funcs declarations

// -> Helper funcs
void printMenu();
void cleanBuffer();
int isChoiceValid(char option);
void sendToMission(char choice, FamilyHead *firstHuman);
void scanTree(FamilyHead *firstHuman);
void scanTreeFurther(Human *human, Human **dontScanAgain, unsigned int index);
char *stringFromUser();
int isPtrInArray(Human **arrayOfPtr, void *ptr, unsigned int arrayLength);
void sendToAction(void *ptr,char * action);

// -> Missions funcs
void createFamilyHead(FamilyHead *firstHuman);
void marryTwoHumans();

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
    firstHuman ->next = NULL; 

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

        sendToMission(choice, firstHuman);
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
 * @brief this function gets a choice and moves the user to the right missions
 * 
 * @param choice the choice the user made
 * @param firstHuman he is neede in all the missions
*/
void sendToMission(char choice, FamilyHead *firstHuman){
    // depending on the user's choice navigate the user to the right program.
    switch (choice) {
        case '1':
            createFamilyHead(firstHuman);
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

/**
 * @brief this function scans the tree, visiting every memeber without repetition
 * if memory allocation fail we exit the program.
 * 
 * @param firstHuman the first family head in the whole tree.
 * 
*/
void scanTree(FamilyHead *firstHuman){
    // look at each familyHead - it's firstHuman right now
    if(firstHuman != NULL){
        // for now just print the age of the human
        printf("%s",firstHuman->properties->name);

        // send the next FH
        scanTree(firstHuman->next);

        // create an array of humans to not scan again, empty for now. (allocate memory)
        Human **dontScanAgain = (Human **)malloc(sizeof(Human));
        if (dontScanAgain == NULL) {
            exit(1);
        }

        // save the size of the array.
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
void scanTreeFurther(Human *human, Human **dontScanAgain, unsigned int index){
    if(human != NULL){
        // if he's in the dontScanAgain we return before proccessing
        if(isPtrInArray(dontScanAgain, human, index) == 1){
            return;
        }

        // do something, in this case printf just to check
        printf("%s", human->name);

        // add him to the dontScanAgain array
        dontScanAgain[index] = human;

        /*
        expand the memory according to the size thous far
        we allocated index+1 to offset the diff of array numbering to actual numbers of memory blocks
        */
        dontScanAgain = (Human **)realloc(dontScanAgain, (index + 1) * sizeof(Human));
        if (dontScanAgain == NULL) {
            exit(1);
        }

        index++;

        // send this human firstChild to scanTreeFurther
        scanTreeFurther(human->firstChild,dontScanAgain, index);

        // send this human siblings to scanTreeFurther
        scanTreeFurther(human->sibling, dontScanAgain, index);

        return;

    }

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
int isPtrInArray(Human **arrayOfPtr, void *ptr, unsigned int arrayLength){
    // loop through each element of the array
    for (unsigned int i = 0; i < arrayLength; i++) {
        // if an element is equal to the ptr we are looing for, return 1;
        if(arrayOfPtr[i] == ptr){
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
 * @brief this function updates a humans values into new values
 * 
 * @param toUpdate pointer to human to update
 * @param source contains the info we want
*/
void updateHuman(Human *toUpdate, Human source){
    // update each property
    toUpdate -> age = source.age;
    toUpdate -> name = source.name;
    toUpdate -> firstChild = source.firstChild;
    toUpdate -> parent1 = source.parent1;
    toUpdate -> parent2 = source.parent2;
    toUpdate -> partner = source.partner;
    toUpdate -> sibling = source.sibling;

}

/**
 * @brief this func take a ptr and action in string, to send to different actions
 * 
 * @param ptr the pointer to perform the actions on
 * @param action the action in string format
*/
void sendToAction(void *ptr, char * action){

}
// -> Missions funcs

/**
 * @brief This function creates a family head with the name and age
 * 
 * @param firstHuman the pointer to the first human in the program
*/
void createFamilyHead(FamilyHead *firstHuman){

    // get name from user
    printf("Enter a name:\n");
    char *name = stringFromUser();

    // get age from user
    printf("Enter age:\n");
    unsigned int age;
    scanf("%u",&age);

    cleanBuffer();
    
    // check if name doesn't exists with the scan upward (W.I.P)
    int exists = 0; // just for testing

    if(exists == 1){
        printf("The name is already taken\n");
    }

    // allocate memory to human pointer
    Human *newHumanPointer = (Human *)malloc(sizeof(Human));
    if (newHumanPointer == NULL) {
        exit(1);
    }

    // first familyHead? save the value to firstHuman
    if(firstHuman->properties == NULL){
        firstHuman->properties = newHumanPointer;

        // not the first? get the last node of the familyHead and add to it the new one
    }else{
        // create the newHead
        FamilyHead *newHead = (FamilyHead *)malloc(sizeof(FamilyHead));
        if (newHead == NULL) {
            exit(1);
        }

        // reset the properites to new pointer and next to null
        newHead->properties = newHumanPointer;
        newHead ->next = NULL; 

        FamilyHead *lastPointer = lastFamilyHead(firstHuman);
        
        // add the human to the last node of the familyHead.
        lastPointer -> next = newHead;
    }

    // create the human with name and age, everything else is null, and put in the new pointer.
    Human human = {name, 0, NULL,NULL,NULL,NULL,NULL};
    updateHuman(newHumanPointer, human);
}

/**
 * @brief this func take from the user two humans names and marry them
*/
void marryTwoHumans(){
    // ask the user who he want's to marry with who
    printf("Enter the name of the first person:\n");
    char * firstPersonName = stringFromUser();

    printf("Enter the name of the second person:\n");
    char * secondPersonName = stringFromUser();

    // check if they exists.

}
