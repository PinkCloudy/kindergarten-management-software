#ifndef RECEIPT_H
#define RECEIPT_H
 
#include <stdio.h>
#include "define.h"
#include <string.h>
#include <stdbool.h> 

typedef struct Receipt {
    char ID_Receipt[MAX_ID];
    char ID_Student[MAX_ID];
    char Date[MAX_DATE];
    double Amount;
    int Month;
    int Year;
    char Status[MAX_STATUS];
} Receipt;

typedef struct Node {
    Receipt data;
    struct Node* next;
} Node;

// Các prototype hàm
void addReceipt(Node** head);
void displayAllReceipts(Node* head);
Node* searchReceiptByID(Node* head, const char* id);
bool deleteReceiptByID(Node** head, const char* id);
void updateReceiptByID(Node* head, const char* id);
float calculateTotalRevenue(Node* head);
void freeReceiptList(Node** head);
void saveReceiptsToFile(Node* head, const char* filename);
void loadReceiptsFromFile(Node** head, const char* filename);


#endif
