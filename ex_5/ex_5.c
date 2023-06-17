// (89110, Spring 2023, Assignment #5, Tal Ben Naim, 212749071, bennait3)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structs

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct Account {
    unsigned int accountNumber;
    char *accountHolder;
    int balance;
} Account;

typedef struct Transaction {
    unsigned int fromAccount;
    unsigned int toAccount;
    int amount;
} Transaction;

typedef struct Bank {
    Node *accounts;
    Node *transactions;
} Bank;

// Defines
#define NEW_LINE_ASCII 10

// Funcs declarations

// -> Helper funcs
void printMenu();
void cleanBuffer();
int isChoiceValid(char option);
int isAccountNumExists(unsigned int accountNumber, Bank *bank);
void freeAllNode(Node *node);
char *stringFromUser();
Node *lastInLinkedList(Node *linkedListHead);
Bank *createBank();
void freeBank(Bank *bank);
// -> Main missions funcs
void createAccount(Bank *bank);

/**
 * @brief Main function that wait for user input to navigate the user
 * to the right part of the program according to the input.
 * if memory allocation fail we exit the program.
 *
 * @return 0 if the program runs successfully
 */
int main() {

    // create the bank for this run, allocate memory and set a default NULL value for the fields.
    Bank *bank = createBank();

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
                createAccount(bank);
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

            default:
                break;
        }
    }

    freeBank(bank);

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
    printf("1. Create account\n");
    printf("2. Delete account\n");
    printf("3. Update account\n");
    printf("4. Deposit / Withdraw money\n");
    printf("5. Transferring\n");
    printf("6. View account\n");
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
    // This program options range is 0 - 6.
    if (choice < '0' || choice > '6') {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief Free all the nodes in the given linked list pointer
 *
 * @param node The pointer to the node instance
 */
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

/**
 * @brief Check if the given account number exist in the bank
 *
 * @param accountNumber The account number to check for
 * @param bank the pointer to the bank
 *
 * @return 1 if exists, 0 if not.
 */
int isAccountNumExists(unsigned int accountNumber, Bank *bank) {

    // take the accountsHead pointer from the bank
    Node *accountsHead = bank->accounts;

    // if the head is empty that means we dont have an account yet, the number is free.
    if (accountsHead == NULL) {
        return 0;
    } else {
        // save the accountHead pointer in the accounts we are checking
        Node *accountToCheck = accountsHead;

        // if the account to check exists check it
        while (accountToCheck != NULL) {

            // if there is no data in the account to check.
            if (accountToCheck->data != NULL) {
                // save the data of the account
                Account *accountData = accountToCheck->data;

                // check the number of the account, if equal return 1 else check the next account.
                printf("%d", accountData->accountNumber);
                if (accountData->accountNumber == accountNumber) {
                    return 1;
                }
            }
            accountToCheck = accountsHead->next;
        }

        // if we didn't find in the while loop the number is free.
        return 0;
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
 * @brief get the last node in a linked list
 *
 * @param linkedListHead the head of the linked list
 *
 * @return the last node in a linked list
 */
Node *lastInLinkedList(Node *linkedListHead) {
    // an helper pointer to store the head and not change it.
    Node *helper = linkedListHead;

    // go next node until we see a null.
    while (helper->next != NULL) {
        // move the helper to be the next node
        helper = helper->next;
    }
    // return the helper as the last node
    return helper;
}

/**
 * @brief create the bank for this run
 *
 * @return the pointer to the created bank.
 */
Bank *createBank() {
    // create the bank for this run, allocate memory and set a default NULL value for the fields.
    Bank *bank = (Bank *)malloc(sizeof(Bank));
    if (bank == NULL) {
        exit(1);
    }

    // allocate memory for the accounts node in the bank
    bank->accounts = (Node *)malloc(sizeof(Node));
    if (bank->accounts == NULL) {
        exit(1);
    }

    // reset the value and next to null
    bank->accounts->data = NULL;
    bank->accounts->next = NULL;

    // allocate memory for the transactions node in the bank
    bank->transactions = (Node *)malloc(sizeof(Node));
    if (bank->transactions == NULL) {
        exit(1);
    }

    // reset the value and next to null
    bank->transactions->data = NULL;
    bank->transactions->next = NULL;

    return bank;
}

/**
 * @brief Free all the bank memory
 *
 * @param bank the bank pointer to the bank we need to free.
 */
void freeBank(Bank *bank) {
    // free all the other nodes in the bank
    if (bank->accounts != NULL) {
        freeAllNode(bank->accounts);
    }
    if (bank->transactions != NULL) {
        freeAllNode(bank->transactions);
    }

    // free bank
    free(bank);
}

// -> Main missions funcs

/**
 * @brief Create an account with the user's choice of number of name.
 * if memory allocation fail we exit the program.
 *
 * @param bank the pointer to the bank instance.
 */
void createAccount(Bank *bank) {
    printf("Enter account number:\n");

    // take the account number from the user
    unsigned int accountNumber;
    scanf("%d", &accountNumber);
    cleanBuffer();

    // check if number is available
    if (accountNumber == 0 || isAccountNumExists(accountNumber, bank) == 1) {
        // inform the user the account number isn't valid and go back to the main menu.
        printf("Account number already exists\n");
        return;

        // take the name to proceed in the account creation
    } else {
        // take the string from the user
        printf("Enter account holder:\n");
        char *accountName = stringFromUser();

        // allocate memory to account pointer
        Account *newAccPointer = (Account *)malloc(sizeof(Account));
        if (newAccPointer == NULL) {
            exit(1);
        }

        // create the account with the given number and name.
        Account newAccount = {accountNumber, accountName, 0};

        // take the account value in the pointer
        newAccPointer = &newAccount;

        // get the pointer of the last node in the list
        Node *lastPointer = lastInLinkedList(bank->accounts);

        // add the account to the data of the last node.
        lastPointer->data = newAccPointer;

        Account *checkPointer = lastPointer->data;
        unsigned int number = checkPointer->accountNumber;
        printf("%d", number);

        printf("Account created successfully\n");
    }
}
