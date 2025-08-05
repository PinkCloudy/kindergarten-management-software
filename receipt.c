#include <stdio.h>
#include "define.h"
#include <string.h>
#include <stdbool.h> 
#include "receipt.h"
#include <stdlib.h>

void addReceipt(Node** head) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Khong the cap phat bo nho\n");
        return;
    }

    printf("Nhap ma phieu thu :");
    fgets(newNode->data.ID_Receipt, MAX_ID, stdin);
    newNode->data.ID_Receipt[strcspn(newNode->data.ID_Receipt, "\n")] = 0;

    printf("Nhap ma hoc sinh :");
    fgets(newNode->data.ID_Student, MAX_ID, stdin);
    newNode->data.ID_Student[strcspn(newNode->data.ID_Student, "\n")] = 0;

    printf("Nhap ngay thu (dd/mm/yyyy) :");
    fgets(newNode->data.Date, MAX_DATE, stdin);
    newNode->data.Date[strcspn(newNode->data.Date, "\n")] = 0;
    getchar();

    printf("Nhap so tien thu :");
    scanf("%lf", &newNode->data.Amount);
    getchar();

    printf("Nhap trang thai Da thu hoac Chua thu :");
    fgets(newNode->data.Status, MAX_STATUS, stdin);
    newNode->data.Status[strcspn(newNode->data.Status, "\n")] = 0;

    newNode->next = *head;
    *head = newNode;

    printf("Da them phieu thu thanh cong\n");
}

void displayAllReceipts(Node* head) {
    if (!head) {
        printf("Danh sach phieu thu trong\n");
        return;
    }

    printf("Danh sach phieu thu\n");
    while (head) {
        printf("Ma phieu %s | Ma hoc sinh %s | Ngay %s | So tien %.2lf | Thang %d | Nam %d | Trang thai %s\n",
            head->data.ID_Receipt, head->data.ID_Student, head->data.Date,
            head->data.Amount, head->data.Month, head->data.Year, head->data.Status);
        head = head->next;
    }
}

Node* searchReceiptByID(Node* head, const char* id) {
    while (head) {
        if (strcmp(head->data.ID_Receipt, id) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

bool deleteReceiptByID(Node** head, const char* id) {
    Node *temp = *head, *prev = NULL;

    while (temp) {
        if (strcmp(temp->data.ID_Receipt, id) == 0) {
            if (prev) {
                prev->next = temp->next;
            } else {
                *head = temp->next;
            }
            free(temp);
            return true;
        }
        prev = temp;
        temp = temp->next;
    }

    return false;
}

void updateReceiptByID(Node* head, const char* id) {
    Node* node = searchReceiptByID(head, id);
    if (!node) {
        printf("Khong tim thay phieu thu\n");
        return;
    }

    printf("Nhap thong tin moi cho phieu thu %s: ", id);

    printf("Nhap ngay thu dd mm yyyy: ");
    fgets(node->data.Date, MAX_DATE, stdin);
    node->data.Date[strcspn(node->data.Date, "\n")] = 0;

    printf("Nhap so tien moi: ");
    scanf("%lf", &node->data.Amount);
    getchar();

    printf("Nhap thang moi\n");
    scanf("%d", &node->data.Month);
    getchar();

    printf("Nhap nam moi: ");
    scanf("%d", &node->data.Year);
    getchar();

    printf("Nhap trang thai moi: ");
    fgets(node->data.Status, MAX_STATUS, stdin);
    node->data.Status[strcspn(node->data.Status, "\n")] = 0;

    printf("Cap nhat thanh cong\n");
}

float calculateTotalRevenue(Node* head) {
    float total = 0;
    while (head) {
        total += head->data.Amount;
        head = head->next;
    }
    return total;
}

void freeReceiptList(Node** head) {
    Node* current = *head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}


void saveReceiptsToFile(Node* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    Node* current = head;
    while (current != NULL) {
        fprintf(fp, "%s,%s,%s,%.2lf,%d,%d,%s\n",
            current->data.ID_Receipt,
            current->data.ID_Student,
            current->data.Date,
            current->data.Amount,
            current->data.Month,
            current->data.Year,
            current->data.Status);
        current = current->next;
    }

    fclose(fp);
}

void loadReceiptsFromFile(Node** head, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Khong the mo file %s de doc, co the file chua ton tai.\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;

        Receipt temp;
        char* token = strtok(line, ",");
        if (!token) continue;
        strcpy(temp.ID_Receipt, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(temp.ID_Student, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(temp.Date, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        temp.Amount = atof(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        temp.Month = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        temp.Year = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(temp.Status, token);

        Node* newNode = (Node*) malloc(sizeof(Node));
        if (!newNode) {
            printf("Khong the cap phat bo nho.\n");
            fclose(fp);
            return;
        }
        newNode->data = temp;
        newNode->next = NULL;

        if (*head == NULL) {
            *head = newNode;
        } else {
            Node* cur = *head;
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = newNode;
        }
    }

    fclose(fp);
}
