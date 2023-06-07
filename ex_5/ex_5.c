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

// Funcs declarations

// -> Helper funcs
void printMenu();
void cleanBuffer();
int isChoiceValid(char option);
int isAccountNumExists(unsigned int accountNumber);
void freeAllNode(Node *node);

// -> Main missions funcs
void createAccount(Bank *bank);

/**
 * @brief Main function that wait for user input to navigate the user
 * to the right part of the program according to the input.
 * @return 0 if the program runs successfully
 */
int main() {
    // create the bank for this run, allocate memory and set a default NULL value for the fields.
    Bank *bank = (Bank *)malloc(sizeof(Bank));
    bank->accounts = NULL;
    bank->transactions = NULL;

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

    // free all the other things before just check

    // free bank
    free(bank);

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
    if (node) {
        // free the next node recursively
        freeAllNode(node->next);
        // free the current node
        free(node);

        // after freeing the current node, exit the func
        return;
    }
}

/**
 * @brief Check if the given account number exist
 *
 * @param accountNumber The account number to check for
 *
 * @return 1 if exists, 0 if not.
 */
int isAccountNumExists(unsigned int accountNumber) {
}

// -> Main missions funcs

/**
 * @brief Create an account with the user's choice of number of name.
 *
 */
void createAccount(Bank *bank) {

    printf("Enter account number:\n");

    // take the account number from the user
    unsigned int accountNumber;
    scanf("%d", &accountNumber);

    // check if number is available
}
