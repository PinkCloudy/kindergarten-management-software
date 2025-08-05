#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "extracurricular.h"
#include "student.h"
#include "utils.h"

ExtracurricularNode* createExtracurricularNode(ExtracurricularInfo data) {
    ExtracurricularNode* newNode = (ExtracurricularNode*)malloc(sizeof(ExtracurricularNode));
    if (newNode == NULL) {
        fprintf(stderr, "LOI: Khong the cap phat bo nho cho node hoat dong.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addExtracurricular(ExtracurricularNode** head, ExtracurricularInfo data) {
    ExtracurricularNode* newNode = createExtracurricularNode(data);
    if (newNode == NULL) return;
    newNode->next = *head;
    *head = newNode;
}

void addNewExtracurricular(ExtracurricularNode** head, struct Student* studentList) {
    ExtracurricularInfo newData;
    char buffer[256];
    int numParticipants;

    printf("\nTHEM HOAT DONG NGOAI KHOA MOI\n");

    do {
        printf("Nhap Ma Hoat Dong (vd: ACT001): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            printf("Ma Hoat Dong khong duoc de trong.\n");
        } else {
            ExtracurricularNode* current = *head;
            int exists = 0;
            while (current != NULL) {
                if (strcmp(current->data.activityId, buffer) == 0) {
                    exists = 1;
                    break;
                }
                current = current->next;
            }
            if (exists) {
                printf("Ma Hoat Dong '%s' da ton tai. Vui long nhap ma khac.\n", buffer);
            } else {
                strncpy(newData.activityId, buffer, sizeof(newData.activityId) - 1);
                newData.activityId[sizeof(newData.activityId) - 1] = '\0';
                break;
            }
        }
    } while (1);

    printf("Nhap Ten Hoat Dong: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strncpy(newData.name, buffer, sizeof(newData.name) - 1);
        newData.name[sizeof(newData.name) - 1] = '\0';
    } else {
        strcpy(newData.name, "Chua co ten");
    }

    printf("Nhap Ngay (dd/mm/yyyy): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strncpy(newData.date, buffer, sizeof(newData.date) - 1);
        newData.date[sizeof(newData.date) - 1] = '\0';
    } else {
        strcpy(newData.date, "Chua xac dinh");
    }

    printf("Nhap Dia diem: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strncpy(newData.location, buffer, sizeof(newData.location) - 1);
        newData.location[sizeof(newData.location) - 1] = '\0';
    } else {
        strcpy(newData.location, "Chua xac dinh");
    }

    printf("Nhap so luong hoc sinh tham gia: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    numParticipants = atoi(buffer);
    if (numParticipants > 0) {
        char validParticipants[256] = "";
        int valid = 1;

        for (int i = 0; i < numParticipants; i++) {
            printf("Nhap Ma HS thu %d: ", i + 1);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;

            char* temp = buffer;
            while (*temp == ' ') temp++;
            size_t len = strlen(temp);
            while (len > 0 && temp[len - 1] == ' ') temp[--len] = '\0';

            if (strlen(temp) == 0) {
                printf("Canh bao: Ma HS trong danh sach khong hop le, se bo qua.\n");
                valid = 0;
                break;
            }

            if (findStudentById(studentList, temp) == NULL) {
                printf("Canh bao: Ma HS '%s' khong ton tai, se bo qua.\n", temp);
                valid = 0;
                break;
            }

            if (strlen(validParticipants) > 0) {
                strncat(validParticipants, ",", sizeof(validParticipants) - strlen(validParticipants) - 1);
            }
            strncat(validParticipants, temp, sizeof(validParticipants) - strlen(validParticipants) - 1);
        }

        if (valid) {
            strncpy(newData.participants, validParticipants, sizeof(newData.participants) - 1);
            newData.participants[sizeof(newData.participants) - 1] = '\0';
        } else {
            strcpy(newData.participants, "");
        }
    } else {
        strcpy(newData.participants, "");
    }

    addExtracurricular(head, newData);

    saveExtracurricularToFile(*head, "extracurricular_data.dat");

    printf("Da them hoat dong moi voi Ma '%s' thanh cong!\n", newData.activityId);
}

void displayExtracurricular(ExtracurricularNode* head, const char* activityId, struct Student* studentList) {
    ExtracurricularNode* current = head;
    int found = 0;
    printf("\nTHONG TIN HOAT DONG NGOAI KHOA\n");
    while (current != NULL) {
        if (strcmp(current->data.activityId, activityId) == 0) {
            found = 1;
            printf("Ma Hoat Dong: %s\n", current->data.activityId);
            printf("Ten Hoat Dong: %s\n", current->data.name);
            printf("Ngay: %s\n", current->data.date);
            printf("Dia diem: %s\n", current->data.location);
            printf("\nDanh sach tham gia:\n");
            printf("------------------------------------------------\n");
            printf("| Ma HS  | Ho Ten              | Lop           |\n");
            printf("------------------------------------------------\n");

            char tempParticipants[256];
            strncpy(tempParticipants, current->data.participants, sizeof(tempParticipants) - 1);
            tempParticipants[sizeof(tempParticipants) - 1] = '\0'; 

            printf("Danh sach participants: '%s'\n", tempParticipants);

            if (strlen(tempParticipants) == 0) {
                printf("| %-6s | %-20s | %-12s |\n", "N/A", "Khong co HS", "Khong xac dinh");
            } else {
                char* token = strtok(tempParticipants, ",");
                while (token != NULL) {
                    while (*token == ' ') token++;
                    size_t len = strlen(token);
                    while (len > 0 && token[len - 1] == ' ') token[--len] = '\0';

                    if (strlen(token) > 0) {
                        Student* student = findStudentById(studentList, token);
                        if (student) {
                            printf("| %-6s | %-20s | %-12s |\n", student->ID_Student, student->Name, student->ID_Class);
                        } else {
                            printf("| %-6s | %-20s | %-12s |\n", token, "Khong tim thay", "Khong xac dinh");
                        }
                    }
                    token = strtok(NULL, ",");
                }
            }
            printf("------------------------------------------------\n");
            return;
        }
        current = current->next;
    }
    if (!found) {
        printf("Khong tim thay thong tin hoat dong voi Ma '%s'.\n", activityId);
    }
}

void updateExtracurricular(ExtracurricularNode* head, const char* activityId, struct Student* studentList) {
    ExtracurricularNode* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->data.activityId, activityId) == 0) {
            found = 1;
            printf("\nCAP NHAT THONG TIN HOAT DONG NGOAI KHOA CHO MA %s\n", activityId);
            printf("(De trong va Enter de giu nguyen)\n");

            char buffer[256];
            while (getchar() != '\n'); // Xóa bộ đệm

            printf("Ten Hoat Dong hien tai: %s\nNhap Ten moi: ", current->data.name);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) strncpy(current->data.name, buffer, sizeof(current->data.name) - 1);
            current->data.name[sizeof(current->data.name) - 1] = '\0';

            printf("Ngay hien tai: %s\nNhap Ngay moi (dd/mm/yyyy): ", current->data.date);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) strncpy(current->data.date, buffer, sizeof(current->data.date) - 1);
            current->data.date[sizeof(current->data.date) - 1] = '\0';

            printf("Dia diem hien tai: %s\nNhap Dia diem moi: ", current->data.location);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) strncpy(current->data.location, buffer, sizeof(current->data.location) - 1);
            current->data.location[sizeof(current->data.location) - 1] = '\0';

            printf("Danh sach tham gia hien tai: %s\nNhap so luong hoc sinh tham gia (0 de giu nguyen): ", current->data.participants);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;

            int numParticipants = atoi(buffer);
            if (numParticipants > 0) {
                char validParticipants[256] = "";
                int valid = 1;

                for (int i = 0; i < numParticipants; i++) {
                    printf("Nhap Ma HS thu %d: ", i + 1);
                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\n")] = 0;

                    char* temp = buffer;
                    while (*temp == ' ') temp++;
                    size_t len = strlen(temp);
                    while (len > 0 && temp[len - 1] == ' ') temp[--len] = '\0';

                    if (strlen(temp) == 0) {
                        printf("Canh bao: Ma HS trong danh sach khong hop le, se bo qua.\n");
                        valid = 0;
                        break;
                    }

                    if (findStudentById(studentList, temp) == NULL) {
                        printf("Canh bao: Ma HS '%s' khong ton tai, se bo qua.\n", temp);
                        valid = 0;
                        break;
                    }

                    if (strlen(validParticipants) > 0) {
                        strncat(validParticipants, ",", sizeof(validParticipants) - strlen(validParticipants) - 1);
                    }
                    strncat(validParticipants, temp, sizeof(validParticipants) - strlen(validParticipants) - 1);
                }

                if (valid) {
                    strncpy(current->data.participants, validParticipants, sizeof(current->data.participants) - 1);
                    current->data.participants[sizeof(current->data.participants) - 1] = '\0';
                    printf("Da cap nhat danh sach tham gia: %s\n", current->data.participants);
                } else {
                    printf("Khong cap nhat danh sach tham gia do co ma HS khong hop le.\n");
                }
            }

            saveExtracurricularToFile(head, "extracurricular_data.dat");

            printf("Da cap nhat thong tin hoat dong '%s'.\n", activityId);
            return;
        }
        current = current->next;
    }

    if (!found) {
        printf("Khong tim thay thong tin hoat dong voi Ma '%s'.\n", activityId);
    }
}

void saveExtracurricularToFile(ExtracurricularNode* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "LOI: Khong the mo file '%s' de ghi.\n", filename);
        perror("Nguyen nhan");
        return;
    }
    ExtracurricularNode* current = head;
    int count = 0;
    while (current != NULL) {
        if (fwrite(&(current->data), sizeof(ExtracurricularInfo), 1, file) != 1) {
            fprintf(stderr, "LOI: Khong the ghi du lieu hoat dong '%s' vao file.\n", current->data.activityId);
            break;
        }
        count++;
        current = current->next;
    }
    if (fclose(file) != 0) {
        fprintf(stderr, "LOI: Khong the dong file '%s'.\n", filename);
        perror("Nguyen nhan");
    }
    if (count == 0) {
        fprintf(stderr, "CANH BAO: Khong co du lieu hoat dong nao duoc ghi vao file '%s'.\n", filename);
    }
}

ExtracurricularNode* loadExtracurricularFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "LOI: Khong the mo file '%s' de doc.\n", filename);
        perror("Nguyen nhan");
        return NULL;
    }
    ExtracurricularNode* head = NULL;
    ExtracurricularInfo data;
    int count = 0;
    while (fread(&data, sizeof(ExtracurricularInfo), 1, file) == 1) {
        ExtracurricularNode* newNode = createExtracurricularNode(data);
        if (newNode != NULL) {
            newNode->next = head;
            head = newNode;
            count++;
        }
    }
    if (ferror(file)) {
        fprintf(stderr, "LOI: Co loi khi doc file '%s'.\n", filename);
        perror("Nguyen nhan");
        freeExtracurricularList(&head);
        head = NULL;
    }
    if (fclose(file) != 0) {
        fprintf(stderr, "LOI: Khong the dong file '%s'.\n", filename);
        perror("Nguyen nhan");
    }
    return head;
}

void freeExtracurricularList(ExtracurricularNode** head) {
    ExtracurricularNode* current = *head;
    while (current != NULL) {
        ExtracurricularNode* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}