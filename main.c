/* COP 3502C Assignment 6
This program is written by: Aaron Burgess */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTLEN 30 //29+1 for the null character
#define TABLESIZE 300007

typedef struct merchandise {
    char name[MAXSTLEN]; // e.g., "braziljersey"
    int quantity; // stock available
    int price; // sale price per item
} merchandise;

typedef struct inventoryNode {
    merchandise* merchPtr;
    struct inventoryNode* next;
} inventoryNode;

typedef struct inventoryTable { //Hash table
    inventoryNode** lists;
    int size; // number of buckets (table size)
} inventoryTable;

//functions
int hashfunction(char* word, int size); //provided for hashvalues in the table
void init(inventoryTable *table); //set each linked list to NULL at the start
inventoryNode* searchList(inventoryNode *list, char item[]); //return the node indicated by item in the linked list
inventoryNode* buyMerch(inventoryTable *table, char item[], int quantity); //return the node after updating the quantity or creating a node
inventoryNode* sellItem(inventoryTable *table, char item[], int quantity); //return the node after updating the quantity post sell
inventoryTable* changePrice(inventoryTable *table, char item[], int newPrice); //change the price of the item in the table
void freeTable(inventoryTable *table); //free up the hash table when done with the program
void freeLinkedList(inventoryNode* list); //recursive function to free each linked list in the table

//global variables
int money = 100000;
int complexity = 0;

int main(void) {
    //create and read in the number of commands
    int numC;
    scanf("%d", &numC);

    //create and initialize the hash table
    inventoryTable *table = (inventoryTable*)malloc(sizeof(inventoryTable));
    table->lists = (inventoryNode**)malloc(TABLESIZE * sizeof(inventoryNode*));
    table->size = TABLESIZE;
    init(table);

    for (int i = 0; i < numC; i++) { //for each command
        char command[MAXSTLEN];
        scanf("%s", command);

        if (strcmp(command, "buy") == 0) { //if buy command
            char item[MAXSTLEN];
            int quantity, totalPrice;
            scanf("%s %d %d", item, &quantity, &totalPrice);

            //change the money to account for the purchase of the merchandise
            money -= totalPrice;

            //return the node to print after buying merchandise
            inventoryNode *product = buyMerch(table, item, quantity);

            //print outputs
            printf("%s %d %d\n", item, product->merchPtr->quantity, money);
        }
        else if (strcmp(command, "sell") == 0) { //if sell command
            char item[MAXSTLEN];
            int quantity;
            scanf("%s %d", item, &quantity);

            //find the product in the table
            inventoryNode *product = sellItem(table, item, quantity);

            //print outputs
            printf("%s %d %d\n", item, product->merchPtr->quantity, money);

        }
        else if (strcmp(command, "change_price") == 0) { //if change price_command
            char item[MAXSTLEN];
            int newPrice;
            scanf("%s %d", item, &newPrice);

            //update the list with the new price for the item
            table = changePrice(table, item, newPrice);
        }
    }

    //print final outputs
    printf("%d\n", money);
    printf("%d\n", complexity);

    //free the table
    freeTable(table);
}

int hashfunction(char* word, int size) {
    int len = strlen(word);
    int hvalue = 0;
    for (int i=0; i<len; i++)
        hvalue = (1151*hvalue + (word[i]-'a'))%size;
    return hvalue;
}

void init(inventoryTable *table) {
    // make each index of the table a NULL linked list
    for (int i=0; i<TABLESIZE; i++) {
        table->lists[i] = NULL;
    }
}

inventoryNode* searchList(inventoryNode *list, char item[]) {
    for (inventoryNode *walker = list; walker != NULL; walker = walker->next){ //parse through the linked list until you get to the end
        complexity++; //increase for each node checked
        if (strcmp(walker->merchPtr->name, item) == 0) { //if you get the node with the item name, return it
            return walker;
        }
    }
    complexity++; //whole thing checked so this is to also "check" NULL
    return NULL;
}

inventoryNode* buyMerch(inventoryTable *table, char item[], int quantity) {
    int index = hashfunction(item, table->size); //linked list index in the hash table
    inventoryNode *product = searchList(table->lists[index], item); //product in the linked list
    if (product != NULL) { //if the product is in the linked list
        product->merchPtr->quantity += quantity;
        return product;
    }
    product = (inventoryNode*)malloc(sizeof(inventoryNode)); //else, make a node
    if (product != NULL) { //if memory allocation worked
        product->merchPtr = (merchandise*)malloc(sizeof(merchandise)); //allocate memory for the merchandise pointer
        //store the item's details
        strcpy(product->merchPtr->name, item);
        product->merchPtr->quantity = quantity;
        product->merchPtr->price = TABLESIZE;

        //put it at the start of the linked list and make the table at that index the linked list
        product->next = table->lists[index];
        table->lists[index] = product;
    }
    return product;
}

inventoryNode *sellItem(inventoryTable *table, char item[], int quantity) {
    int index = hashfunction(item, table->size);
    inventoryNode *product = searchList(table->lists[index], item);
    if (product != NULL) { //item is in the hash table to be sold
        if (product->merchPtr->quantity <= 0) { //no product to sell
            return product;
        }
        if (product->merchPtr->quantity < quantity) { //if they want more than available
            money += (product->merchPtr->price * product->merchPtr->quantity); //sell all
            product->merchPtr->quantity = 0; //sell all
            return product;
        }
        //they want less than the entire stock
        money += (product->merchPtr->price * quantity); //sell what they want
        product->merchPtr->quantity -= quantity; //sell what they want
        return product;
    }
}

inventoryTable* changePrice(inventoryTable *table, char item[], int newPrice) {
    int index = hashfunction(item, table->size); //linked list in the table
    inventoryNode *product = searchList(table->lists[index], item); //node in the linked list
    if (product != NULL) { //you found the node with the name "item"
        product->merchPtr->price = newPrice; //change the price of the merch in the node
    }
    return table;
}

void freeTable(inventoryTable *table) {
    for (int i=0; i<TABLESIZE; i++) { //for each linked list in the table
        if (table->lists[i] != NULL) { //if there is something in the linked list
            freeLinkedList(table->lists[i]); //recursive function to free each node in the linked list
        }
    }
    free(table->lists); //free the lists
    free(table); //free the table
}

void freeLinkedList(inventoryNode* list) {
    if (list == NULL) return;
    freeLinkedList(list->next); //go all the way to the end
    free(list->merchPtr); //free the merchPtr
    free(list); //free the node
}