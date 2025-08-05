#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "health.h"
#include "utils.h"
#include "student.h"


Health* createHealthNode(Health dataHealth) {
    Health *newNode = (Health*)malloc(sizeof(Health));
    strcpy(newNode->ID_Health, dataHealth.ID_Health);
    strcpy(newNode->ID_Student, dataHealth.ID_Student);
    newNode->Height = dataHealth.Height;
    newNode->Weight = dataHealth.Weight;
    strcpy(newNode->MedicalCondition, dataHealth.MedicalCondition);
    strcpy(newNode->Vaccination, dataHealth.Vaccination);
    strcpy(newNode->Notes, dataHealth.Notes);
    newNode->next = NULL;
    return newNode;
}

void addHealthToList(Health **LinkedListHealth, Health *newNode) {
    newNode->next = *LinkedListHealth;
    *LinkedListHealth = newNode;
}


void displayHealthList(Health *LinkedList) {
    Health *ptr = LinkedList;
    int count = 0;
    printf("\nDANH SACH HO SO SUC KHOE\n");
    if (ptr == NULL) {
        printf("Danh sach ho so suc khoe rong.\n");
    } else {
        printf("STT  Ma Ho So   Ma HS      Chieu Cao   Can Nang   Tinh Trang\n");
        while (ptr != NULL) {
            count++;
            printf("%-5d%-11s%-11s%-12.1f%-11.1f%-s\n", count, ptr->ID_Health, ptr->ID_Student, ptr->Height, ptr->Weight, ptr->MedicalCondition);
            ptr = ptr->next;
        }
        printf("Tong so ho so suc khoe: %d\n", count);
    }
}

void displayHealthDetails(Health *health) {
    if (health == NULL) {
        printf("\nKhong co thong tin ho so suc khoe.\n");
        return;
    }
    printf("\nTHONG TIN HO SO SUC KHOE\n");
    printf("Ma Ho So: %s\n", health->ID_Health);
    printf("Ma Hoc Sinh: %s\n", health->ID_Student);
    printf("Chieu Cao: %.1f cm\n", health->Height);
    printf("Can Nang: %.1f kg\n", health->Weight);
    printf("Tinh Trang Benh Ly: %s\n", health->MedicalCondition);
    printf("Lich Tiem Phong: %s\n", health->Vaccination);
    printf("Ghi Chu: %s\n", health->Notes);
}

int findHealth(Health *LinkedList, const char* ID_Student) {
    Health *ptr = LinkedList;
    int count = 0;
    int foundCount = 0;
    printf("\nKET QUA TIM KIEM HO SO SUC KHOE\n");
    if (LinkedList == NULL) {
        printf("Danh sach rong.\n");
        return 0;
    }
    if (ID_Student == NULL || strlen(ID_Student) == 0) {
        printf("Vui long nhap ma hoc sinh can tim.\n");
        return 0;
    }
    printf("STT  Ma Ho So   Ma HS      Chieu Cao   Can Nang   Tinh Trang\n");
    while (ptr != NULL) {
        count++;
        if (strcmp(ptr->ID_Student, ID_Student) == 0) {
            foundCount++;
            printf("%-5d%-11s%-11s%-12.1f%-11.1f%-s\n", foundCount, ptr->ID_Health, ptr->ID_Student, ptr->Height, ptr->Weight, ptr->MedicalCondition);
        }
        ptr = ptr->next;
    }
    if (foundCount == 0) {
        printf("Khong tim thay ho so suc khoe nao cho ma hoc sinh '%s'.\n", ID_Student);
    }
    printf("Tim thay %d ho so suc khoe.\n", foundCount);
    return foundCount;
}

Health* findHealthById(Health *LinkedList, const char* ID) {
    if (ID == NULL) {
        fprintf(stderr, "ERROR (findHealthById): Ma Ho So can tim la NULL.\n");
        return NULL;
    }
    if (LinkedList == NULL) {
        return NULL;
    }
    Health *current = LinkedList;
    while (current != NULL) {
        if (strcmp(current->ID_Health, ID) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int editHealthById(Health **LinkedList, const char *ID, Student *LinkedListStudent) {
    if (ID == NULL) {
        fprintf(stderr, "ERROR (editHealthById): Ma Ho So can sua la NULL.\n");
        return 0;
    }

    Health *healthToUpdate = findHealthById(*LinkedList, ID);
    if (healthToUpdate == NULL) {
        printf("\nKhong tim thay ho so suc khoe co Ma Ho So: %s de sua.\n", ID);
        return 0;
    }

    printf("\nTHONG TIN HIEN TAI CUA HO SO SUC KHOE %s\n", healthToUpdate->ID_Health);
    displayHealthDetails(healthToUpdate);

    printf("\nNHAP THONG TIN MOI (De trong va Enter de giu nguyen)\n");

    char buffer[256];
    while (getchar() != '\n'); // Xóa bộ đệm

    printf("Ma Hoc Sinh hien tai: %s\nNhap Ma Hoc Sinh moi: ", healthToUpdate->ID_Student);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        if (findStudentById(LinkedListStudent, buffer) == NULL) {
            printf("LOI: Ma Hoc Sinh '%s' khong ton tai.\n", buffer);
        } else {
            strcpy(healthToUpdate->ID_Student, buffer);
        }
    }

    printf("Chieu Cao hien tai: %.1f\nNhap Chieu Cao moi: ", healthToUpdate->Height);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) healthToUpdate->Height = atof(buffer);

    printf("Can Nang hien tai: %.1f\nNhap Can Nang moi: ", healthToUpdate->Weight);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) healthToUpdate->Weight = atof(buffer);

    printf("Tinh Trang Benh Ly hien tai: %s\nNhap Tinh Trang moi: ", healthToUpdate->MedicalCondition);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(healthToUpdate->MedicalCondition, buffer);

    printf("Lich Tiem Phong hien tai: %s\nNhap Lich Tiem Phong moi: ", healthToUpdate->Vaccination);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(healthToUpdate->Vaccination, buffer);

    printf("Ghi Chu hien tai: %s\nNhap Ghi Chu moi: ", healthToUpdate->Notes);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(healthToUpdate->Notes, buffer);

    saveHealthToFile(*LinkedList, "health_data.dat");
    printf("\nDa cap nhat thong tin cho ho so suc khoe %s.\n", healthToUpdate->ID_Health);
    displayHealthDetails(healthToUpdate);
    return 1;
}

int deleteHealthById(Health **LinkedList, const char* ID, Student *LinkedListStudent) {
    if (ID == NULL || *LinkedList == NULL) {
        printf("\nLOI: Du lieu dau vao khong hop le.\n");
        return 0;
    }

    Health *nodeToDelete = *LinkedList;
    Health *previousNode = NULL;

    if (strcmp(nodeToDelete->ID_Health, ID) == 0) {
        *LinkedList = nodeToDelete->next;
        printf("\nDa xoa ho so suc khoe: Ma Ho So %s\n", nodeToDelete->ID_Health);
        free(nodeToDelete);
        saveHealthToFile(*LinkedList, "health_data.dat");
        return 1;
    }

    previousNode = nodeToDelete;
    nodeToDelete = nodeToDelete->next;
    while (nodeToDelete != NULL) {
        if (strcmp(nodeToDelete->ID_Health, ID) == 0) {
            previousNode->next = nodeToDelete->next;
            printf("\nDa xoa ho so suc khoe: Ma Ho So %s\n", nodeToDelete->ID_Health);
            free(nodeToDelete);
            saveHealthToFile(*LinkedList, "health_data.dat");
            return 1;
        }
        previousNode = nodeToDelete;
        nodeToDelete = nodeToDelete->next;
    }
    printf("\nKhong tim thay ho so suc khoe voi Ma Ho So '%s'.\n", ID);
    return 0;
}

Health inputHealthData(Student *LinkedListStudent) {
    Health newHealthData;
    char buffer[256];

    newHealthData.ID_Health[0] = '\0';

    printf("\nNHAP THONG TIN HO SO SUC KHOE MOI\n");
    printf("(Nhap 'huy' vao Ma Ho So de huy)\n");

    do {
        printf("Nhap Ma Ho So (vd: HS001): ");
        fgets(newHealthData.ID_Health, sizeof(newHealthData.ID_Health), stdin);
        newHealthData.ID_Health[strcspn(newHealthData.ID_Health, "\n")] = 0;

        if (strcmp(newHealthData.ID_Health, "huy") == 0) {
            printf("Da huy bo them ho so suc khoe.\n");
            newHealthData.ID_Health[0] = '\0';
            return newHealthData;
        }

        if (strlen(newHealthData.ID_Health) == 0) {
            printf("Ma Ho So khong duoc de trong.\n");
        }
    } while (strlen(newHealthData.ID_Health) == 0);

    printf("Nhap Ma Hoc Sinh: ");
    fgets(newHealthData.ID_Student, sizeof(newHealthData.ID_Student), stdin);
    newHealthData.ID_Student[strcspn(newHealthData.ID_Student, "\n")] = 0;
    while (strlen(newHealthData.ID_Student) == 0 || findStudentById(LinkedListStudent, newHealthData.ID_Student) == NULL) {
        printf("LOI: Ma Hoc Sinh khong duoc de trong hoac khong ton tai.\n");
        printf("Nhap lai Ma Hoc Sinh: ");
        fgets(newHealthData.ID_Student, sizeof(newHealthData.ID_Student), stdin);
        newHealthData.ID_Student[strcspn(newHealthData.ID_Student, "\n")] = 0;
    }

    printf("Nhap Chieu Cao (cm): ");
    fgets(buffer, sizeof(buffer), stdin);
    newHealthData.Height = atof(buffer);

    printf("Nhap Can Nang (kg): ");
    fgets(buffer, sizeof(buffer), stdin);
    newHealthData.Weight = atof(buffer);

    printf("Nhap Tinh Trang Benh Ly: ");
    fgets(newHealthData.MedicalCondition, sizeof(newHealthData.MedicalCondition), stdin);
    newHealthData.MedicalCondition[strcspn(newHealthData.MedicalCondition, "\n")] = 0;

    printf("Nhap Lich Tiem Phong: ");
    fgets(newHealthData.Vaccination, sizeof(newHealthData.Vaccination), stdin);
    newHealthData.Vaccination[strcspn(newHealthData.Vaccination, "\n")] = 0;

    printf("Nhap Ghi Chu: ");
    fgets(newHealthData.Notes, sizeof(newHealthData.Notes), stdin);
    newHealthData.Notes[strcspn(newHealthData.Notes, "\n")] = 0;

    printf("Da hoan tat nhap thong tin.\n");
    return newHealthData;
}

void addNewHealth(Health **LinkedListHealth, Student *LinkedListStudent) {
    printf("\nTHEM HO SO SUC KHOE MOI\n");

    Health healthDataFromUser = inputHealthData(LinkedListStudent);
    if (strlen(healthDataFromUser.ID_Health) == 0) {
        return;
    }

    if (findHealthById(*LinkedListHealth, healthDataFromUser.ID_Health) != NULL) {
        printf("LOI: Ma Ho So '%s' da ton tai.\n", healthDataFromUser.ID_Health);
        pauseScreen(NULL);
        return;
    }

    Health *newNode = createHealthNode(healthDataFromUser);
    if (newNode == NULL) {
        fprintf(stderr, "LOI: Khong the cap phat bo nho.\n");
        pauseScreen(NULL);
        return;
    }

    addHealthToList(LinkedListHealth, newNode);
    printf("Da them ho so suc khoe '%s' cho hoc sinh '%s' thanh cong!\n", newNode->ID_Health, newNode->ID_Student);
    saveHealthToFile(*LinkedListHealth, "health_data.dat");
    pauseScreen(NULL);
}

void freeHealthList(Health **LinkedList) {
    Health *current = *LinkedList;
    Health *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *LinkedList = NULL;
}

void saveHealthToFile(Health *LinkedList, const char* filename) {
    FILE *file_ptr = fopen(filename, "wb");
    if (file_ptr == NULL) {
        fprintf(stderr, "LOI (saveHealthToFile): Khong the mo file '%s' de ghi.\n", filename);
        perror("Nguyen nhan");
        return;
    }

    Health *current = LinkedList;
    int count = 0;
    while (current != NULL) {
        if (fwrite(current, sizeof(Health), 1, file_ptr) != 1) {
            fprintf(stderr, "LOI (saveHealthToFile): Khong the ghi du lieu ho so suc khoe '%s' vao file.\n", current->ID_Health);
            break;
        }
        count++;
        current = current->next;
    }

    if (fclose(file_ptr) == EOF) {
        fprintf(stderr, "LOI (saveHealthToFile): Khong the dong file '%s' sau khi ghi.\n", filename);
        perror("Nguyen nhan");
    }
}

Health* loadHealthFromFile(const char* filename) {
    FILE *file_ptr = fopen(filename, "rb");
    Health *dsLoadedHead = NULL;
    Health tempHealthData;

    if (file_ptr == NULL) {
        return NULL;
    }

    int count = 0;
    while (fread(&tempHealthData, sizeof(Health), 1, file_ptr) == 1) {
        Health *newNode = createHealthNode(tempHealthData);
        if (newNode == NULL) {
            fprintf(stderr, "LOI (loadHealthFromFile): Khong the cap phat bo nho cho node khi tai tu file.\n");
            continue;
        }
        addHealthToList(&dsLoadedHead, newNode);
        count++;
    }

    if (ferror(file_ptr)) {
        fprintf(stderr, "LOI (loadHealthFromFile): Co loi xay ra khi doc du lieu tu file '%s'.\n", filename);
        perror("Nguyen nhan");
        freeHealthList(&dsLoadedHead);
        dsLoadedHead = NULL;
    }

    if (fclose(file_ptr) == EOF) {
        fprintf(stderr, "LOI (loadHealthFromFile): Khong the dong file '%s' sau khi tai.\n", filename);
        perror("Nguyen nhan");
    }

    return dsLoadedHead;
}