#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teacher.h"
#include "utils.h"
#include "class.h"

Teacher* createTeacherNode(Teacher dataTeacher) {
    Teacher *newNode = (Teacher*)malloc(sizeof(Teacher));
    if (newNode == NULL) {
        fprintf(stderr, "LOI: Khong the cap phat bo nho cho giao vien moi.\n");
        return NULL;
    }
    strcpy(newNode->ID_Teacher, dataTeacher.ID_Teacher);
    strcpy(newNode->Name, dataTeacher.Name);
    strcpy(newNode->DateOfBirth, dataTeacher.DateOfBirth);
    strcpy(newNode->Gender, dataTeacher.Gender);
    strcpy(newNode->Address, dataTeacher.Address);
    strcpy(newNode->PhoneNumber, dataTeacher.PhoneNumber);
    strcpy(newNode->DateJoined, dataTeacher.DateJoined);
    strcpy(newNode->ID_Class_Assigned, dataTeacher.ID_Class_Assigned);
    newNode->next = NULL;
    return newNode;
}

void addTeacherToList(Teacher **LinkedListTeacher, Teacher *newNode) {
    if (newNode == NULL) return;
    newNode->next = *LinkedListTeacher;
    *LinkedListTeacher = newNode;
}

void displayTeacherList(Teacher *LinkedListTeacher) {
    Teacher *ptr = LinkedListTeacher;
    int count = 0;
    printf("\n--- DANH SACH GIAO VIEN ---\n");
    if (ptr == NULL) {
        printf("Danh sach giao vien rong.\n");
        printf("--------------------------\n");
        return;
    }
    printf("%-5s %-10s %-25s %-15s\n", "STT", "Ma GV", "Ho Ten", "Lop P.Trach");
    printf("-------------------------------------------------------\n");
    while (ptr != NULL) {
        count++;
        printf("%-5d %-10s %-25s %-15s\n",
               count,
               ptr->ID_Teacher,
               ptr->Name,
               (strlen(ptr->ID_Class_Assigned) > 0 ? ptr->ID_Class_Assigned : "Chua P.Cong"));
        ptr = ptr->next;
    }
    printf("-------------------------------------------------------\n");
    printf("Tong so giao vien: %d\n", count);
    printf("-------------------------------------------------------\n");
}

void displayTeacherDetails(Teacher *teacher) {
    if (teacher == NULL) {
        printf("Khong co thong tin cua giao vien.\n");
        return;
    }
    printf("\n--- THONG TIN GIAO VIEN ---\n");
    printf("Ma GV: %s\n", teacher->ID_Teacher);
    printf("Ho Ten: %s\n", teacher->Name);
    printf("Ngay sinh: %s\n", teacher->DateOfBirth);
    printf("Gioi tinh: %s\n", teacher->Gender);
    printf("Dia chi: %s\n", teacher->Address);
    printf("So Dien Thoai: %s\n", teacher->PhoneNumber);
    printf("Ngay Vao Lam: %s\n", teacher->DateJoined);
    printf("Lop Phu Trach: %s\n", (strlen(teacher->ID_Class_Assigned) > 0 ? teacher->ID_Class_Assigned : "Chua P.Cong"));
    printf("--------------------------\n");
}

int findTeacher(Teacher *LinkedListTeacher, const char* nameQuery) {
    int foundCount = 0;
    printf("\n--- KET QUA TIM KIEM GIAO VIEN ---\n");
    if (LinkedListTeacher == NULL) {
        printf("Danh sach rong.\n");
        printf("-----------------------------------------\n");
        return 0;
    }
    if (nameQuery == NULL || strlen(nameQuery) == 0) {
        printf("Vui long nhap ten giao vien can tim.\n");
        printf("-----------------------------------------\n");
        return 0;
    }
    char *lowerNameQuery = stringLowerCopy(nameQuery);
    printf("%-5s %-10s %-25s %-15s\n", "STT", "Ma GV", "Ho Ten", "Lop P.Trach");
    printf("-------------------------------------------------------\n");
    Teacher *ptr = LinkedListTeacher;
    while (ptr != NULL) {
        char *lowerPtrName = stringLowerCopy(ptr->Name);
        if (lowerPtrName != NULL) {
            if (strstr(lowerPtrName, lowerNameQuery) != NULL) {
                foundCount++;
                printf("%-5d %-10s %-25s %-15s\n",
                       foundCount,
                       ptr->ID_Teacher,
                       ptr->Name,
                       (strlen(ptr->ID_Class_Assigned) > 0 ? ptr->ID_Class_Assigned : "Chua P.Cong"));
            }
            free(lowerPtrName);
        }
        ptr = ptr->next;
    }
    free(lowerNameQuery);
    if (foundCount == 0) {
        printf("Khong tim thay giao vien nao co ten chua '%s'.\n", nameQuery);
    }
    printf("-------------------------------------------------------\n");
    printf("Tim thay %d giao vien.\n", foundCount);
    printf("-----------------------------------------\n");
    return foundCount;
}

Teacher* findTeacherById(Teacher *LinkedListTeacher, const char* ID) {
    if (ID == NULL) {
        fprintf(stderr, "LOI (findTeacherById): Ma Giao Vien can tim la NULL.\n");
        return NULL;
    }
    if (LinkedListTeacher == NULL) {
        return NULL;
    }
    Teacher *current = LinkedListTeacher;
    while (current != NULL) {
        if (strcmp(current->ID_Teacher, ID) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int deleteTeacherByID(Teacher **LinkedListTeacher, const char* ID, Class *LinkedListClass) {
    if (ID == NULL) {
        fprintf(stderr, "LOI (deleteTeacherByID): Ma GV can xoa la NULL.\n");
        return 0;
    }
    if (*LinkedListTeacher == NULL) {
        return 0;
    }

    Teacher *nodeToDelete = *LinkedListTeacher;
    Teacher *previousNode = NULL;
    char idLopCuaGiaoVien[MAX_ID];
    idLopCuaGiaoVien[0] = '\0';

    if (strcmp(nodeToDelete->ID_Teacher, ID) == 0) {
        if (strlen(nodeToDelete->ID_Class_Assigned) > 0) {
            strcpy(idLopCuaGiaoVien, nodeToDelete->ID_Class_Assigned);
        }
        *LinkedListTeacher = nodeToDelete->next;
        printf("INFO: Da xoa giao vien: MaGV %s - Ten %s\n", nodeToDelete->ID_Teacher, nodeToDelete->Name);
        free(nodeToDelete);

        if (strlen(idLopCuaGiaoVien) > 0 && LinkedListClass != NULL) {
            Class *classNode = findClassById(LinkedListClass, idLopCuaGiaoVien);
            if (classNode != NULL && strcmp(classNode->maGVCN, ID) == 0) {
                classNode->maGVCN[0] = '\0';
                printf("INFO: Da xoa ma GVCN khoi lop %s.\n", classNode->classId);
            }
        }
        return 1;
    }

    previousNode = nodeToDelete;
    nodeToDelete = nodeToDelete->next;
    while (nodeToDelete != NULL) {
        if (strcmp(nodeToDelete->ID_Teacher, ID) == 0) {
            if (strlen(nodeToDelete->ID_Class_Assigned) > 0) {
                strcpy(idLopCuaGiaoVien, nodeToDelete->ID_Class_Assigned);
            }
            previousNode->next = nodeToDelete->next;
            printf("INFO: Da xoa giao vien: MaGV %s - Ten %s\n", nodeToDelete->ID_Teacher, nodeToDelete->Name);
            free(nodeToDelete);

            if (strlen(idLopCuaGiaoVien) > 0 && LinkedListClass != NULL) {
                Class *classNode = findClassById(LinkedListClass, idLopCuaGiaoVien);
                if (classNode != NULL && strcmp(classNode->maGVCN, ID) == 0) {
                    classNode->maGVCN[0] = '\0';
                    printf("INFO: Da xoa ma GVCN khoi lop %s.\n", classNode->classId);
                }
            }
            return 1;
        }
        previousNode = nodeToDelete;
        nodeToDelete = nodeToDelete->next;
    }
    printf("INFO: Khong tim thay giao vien co Ma GV '%s' de xoa.\n", ID);
    return 0;
}

int editTeacherById(Teacher **LinkedListTeacher, const char *ID, Class *LinkedListClass) {
    if (ID == NULL) {
        fprintf(stderr, "LOI (editTeacherById): Ma Giao Vien can sua la NULL.\n");
        return 0;
    }

    Teacher *teacherToUpdate = findTeacherById(*LinkedListTeacher, ID);
    if (teacherToUpdate == NULL) {
        printf("Khong tim thay giao vien co Ma GV: %s de sua.\n", ID);
        return 0;
    }

    printf("\n--- THONG TIN HIEN TAI CUA GIAO VIEN %s ---\n", teacherToUpdate->ID_Teacher);
    displayTeacherDetails(teacherToUpdate);
    printf("\n--- NHAP THONG TIN MOI (De trong va Enter de giu nguyen gia tri cu) ---\n");

    char buffer[256];
    while (getchar() != '\n');

    printf("Ho Ten hien tai: %s\n", teacherToUpdate->Name);
    printf("Nhap Ho Ten moi: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(teacherToUpdate->Name, buffer);

    printf("Ngay Sinh hien tai: %s\n", teacherToUpdate->DateOfBirth);
    printf("Nhap Ngay Sinh moi (dd/mm/yyyy): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(teacherToUpdate->DateOfBirth, buffer);

    printf("Gioi Tinh hien tai: %s\n", teacherToUpdate->Gender);
    printf("Nhap Gioi Tinh moi: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(teacherToUpdate->Gender, buffer);

    printf("Dia Chi hien tai: %s\n", teacherToUpdate->Address);
    printf("Nhap Dia Chi moi: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(teacherToUpdate->Address, buffer);

    printf("SDT hien tai: %s\n", teacherToUpdate->PhoneNumber);
    printf("Nhap SDT moi: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(teacherToUpdate->PhoneNumber, buffer);

    printf("Ngay Vao Lam hien tai: %s\n", teacherToUpdate->DateJoined);
    printf("Nhap Ngay Vao Lam moi (dd/mm/yyyy): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(teacherToUpdate->DateJoined, buffer);

    char oldClassAssigned[MAX_ID];
    strcpy(oldClassAssigned, teacherToUpdate->ID_Class_Assigned);
    printf("Ma Lop Phu Trach hien tai: %s\n", (strlen(teacherToUpdate->ID_Class_Assigned) > 0 ? teacherToUpdate->ID_Class_Assigned : "Chua P.Cong"));
    printf("Nhap Ma Lop Phu Trach moi (de trong neu bo phan cong): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    if (strlen(buffer) > 0) {
        if (LinkedListClass != NULL) {
            Class *targetClass = findClassById(LinkedListClass, buffer);
            if (targetClass != NULL) {
                if (strlen(targetClass->maGVCN) > 0 && strcmp(targetClass->maGVCN, ID) != 0) {
                    printf("LOI: Lop %s da co GVCN (%s). Vui long chon lop khac hoac bo phan cong GVCN cu.\n", buffer, targetClass->maGVCN);
                } else {
                    if (strlen(oldClassAssigned) > 0 && strcmp(oldClassAssigned, buffer) != 0) {
                        Class *oldClass = findClassById(LinkedListClass, oldClassAssigned);
                        if (oldClass != NULL && strcmp(oldClass->maGVCN, ID) == 0) {
                            oldClass->maGVCN[0] = '\0';
                            printf("INFO: Da xoa ma GVCN khoi lop %s.\n", oldClassAssigned);
                        }
                    }
                    strcpy(teacherToUpdate->ID_Class_Assigned, buffer);
                    strcpy(targetClass->maGVCN, ID);
                    printf("INFO: Da cap nhat GVCN cho lop %s.\n", buffer);
                }
            } else {
                printf("LOI: Ma Lop '%s' khong ton tai. Ma Lop Phu Trach khong duoc thay doi.\n", buffer);
            }
        } else {
            printf("LOI: Khong co danh sach lop hoc de kiem tra. Ma Lop Phu Trach khong duoc thay doi.\n");
        }
    } else {
        if (strlen(oldClassAssigned) > 0) {
            Class *oldClass = findClassById(LinkedListClass, oldClassAssigned);
            if (oldClass != NULL && strcmp(oldClass->maGVCN, ID) == 0) {
                oldClass->maGVCN[0] = '\0';
                printf("INFO: Da xoa ma GVCN khoi lop %s.\n", oldClassAssigned);
            }
        }
        teacherToUpdate->ID_Class_Assigned[0] = '\0';
        printf("INFO: Giao vien da duoc bo phan cong lop.\n");
    }

    printf("\n=> Da cap nhat thong tin cho giao vien %s.\n", teacherToUpdate->ID_Teacher);
    displayTeacherDetails(teacherToUpdate);
    return 1;
}

Teacher inputTeacherData(Class *LinkedListClass) {
    Teacher newTeacherData;
    newTeacherData.ID_Teacher[0] = '\0';
    newTeacherData.ID_Class_Assigned[0] = '\0';

    printf("\n--- NHAP THONG TIN GIAO VIEN MOI ---\n");
    printf("(Nhap 'huy' vao Ma Giao Vien de huy bo thao tac)\n");

    do {
        printf("Nhap Ma Giao Vien (vd: GV001, hoac 'huy' de huy): ");
        fgets(newTeacherData.ID_Teacher, sizeof(newTeacherData.ID_Teacher), stdin);
        newTeacherData.ID_Teacher[strcspn(newTeacherData.ID_Teacher, "\n")] = 0;

        if (strcmp(newTeacherData.ID_Teacher, "huy") == 0) {
            printf("Da huy bo them giao vien.\n");
            newTeacherData.ID_Teacher[0] = '\0';
            return newTeacherData;
        }
        if (strlen(newTeacherData.ID_Teacher) == 0) {
            printf("Ma Giao Vien khong duoc de trong. Vui long nhap lai.\n");
        }
    } while (strlen(newTeacherData.ID_Teacher) == 0);

    printf("Nhap Ho Ten: ");
    fgets(newTeacherData.Name, sizeof(newTeacherData.Name), stdin);
    newTeacherData.Name[strcspn(newTeacherData.Name, "\n")] = 0;
    while (strlen(newTeacherData.Name) == 0) {
        printf("Ho Ten khong duoc de trong. Vui long nhap lai: ");
        fgets(newTeacherData.Name, sizeof(newTeacherData.Name), stdin);
        newTeacherData.Name[strcspn(newTeacherData.Name, "\n")] = 0;
    }

    printf("Nhap Ngay Sinh (dd/mm/yyyy): ");
    fgets(newTeacherData.DateOfBirth, sizeof(newTeacherData.DateOfBirth), stdin);
    newTeacherData.DateOfBirth[strcspn(newTeacherData.DateOfBirth, "\n")] = 0;

    printf("Nhap Gioi Tinh (Nam/Nu/Khac): ");
    fgets(newTeacherData.Gender, sizeof(newTeacherData.Gender), stdin);
    newTeacherData.Gender[strcspn(newTeacherData.Gender, "\n")] = 0;

    printf("Nhap Dia Chi: ");
    fgets(newTeacherData.Address, sizeof(newTeacherData.Address), stdin);
    newTeacherData.Address[strcspn(newTeacherData.Address, "\n")] = 0;

    printf("Nhap So Dien Thoai: ");
    fgets(newTeacherData.PhoneNumber, sizeof(newTeacherData.PhoneNumber), stdin);
    newTeacherData.PhoneNumber[strcspn(newTeacherData.PhoneNumber, "\n")] = 0;

    printf("Nhap Ngay Vao Lam (dd/mm/yyyy): ");
    fgets(newTeacherData.DateJoined, sizeof(newTeacherData.DateJoined), stdin);
    newTeacherData.DateJoined[strcspn(newTeacherData.DateJoined, "\n")] = 0;

    if (LinkedListClass == NULL) {
        printf("CANH BAO: Khong co danh sach lop de chon. Ma lop phu trach se duoc de trong.\n");
    } else {
        bool validClassEntered = false;
        char tempIdClass[MAX_ID];
        do {
            printf("Nhap Ma Lop Phu Trach (de trong neu khong phan cong): ");
            fgets(tempIdClass, sizeof(tempIdClass), stdin);
            tempIdClass[strcspn(tempIdClass, "\n")] = 0;

            if (strlen(tempIdClass) == 0) {
                validClassEntered = true;
                break;
            }

            Class *targetClass = findClassById(LinkedListClass, tempIdClass);
            if (targetClass == NULL) {
                printf("LOI: Ma Lop '%s' khong ton tai. Vui long nhap lai hoac de trong.\n", tempIdClass);
            } else if (strlen(targetClass->maGVCN) > 0) {
                printf("LOI: Lop %s da co GVCN (%s). Vui long chon lop khac hoac de trong.\n", tempIdClass, targetClass->maGVCN);
            } else {
                strcpy(newTeacherData.ID_Class_Assigned, tempIdClass);
                validClassEntered = true;
            }
        } while (!validClassEntered);
    }
    return newTeacherData;
}

void addNewTeacher(Teacher **LinkedListTeacher, Class *LinkedListClass) {
    printf("\n--- THEM GIAO VIEN MOI ---\n");
    Teacher teacherDataFromUser = inputTeacherData(LinkedListClass);

    if (strlen(teacherDataFromUser.ID_Teacher) == 0) {
        printf("Thao tac them giao vien da duoc huy bo.\n");
        pauseScreen(NULL);
        return;
    }

    if (findTeacherById(*LinkedListTeacher, teacherDataFromUser.ID_Teacher) != NULL) {
        printf("LOI: Ma Giao Vien '%s' da ton tai trong he thong. Vui long nhap ma khac.\n", teacherDataFromUser.ID_Teacher);
        pauseScreen(NULL);
        return;
    }

    Teacher *newNode = createTeacherNode(teacherDataFromUser);
    if (newNode == NULL) {
        fprintf(stderr, "LOI: Khong the cap phat bo nho de tao giao vien moi!\n");
        pauseScreen(NULL);
        return;
    }

    addTeacherToList(LinkedListTeacher, newNode);

    if (strlen(newNode->ID_Class_Assigned) > 0) {
        Class *targetClass = findClassById(LinkedListClass, newNode->ID_Class_Assigned);
        if (targetClass != NULL && strlen(targetClass->maGVCN) == 0) {
            strcpy(targetClass->maGVCN, newNode->ID_Teacher);
            printf("=> Da them giao vien moi '%s' (Ma GV: %s) va phan cong vao lop '%s' (%s) thanh cong!\n",
                   newNode->Name, newNode->ID_Teacher, targetClass->classId, targetClass->className);
        } else {
            printf("=> Da them giao vien moi '%s' (Ma GV: %s) thanh cong. LOP PHU TRACH KHONG HOP LE!\n",
                   newNode->Name, newNode->ID_Teacher);
            newNode->ID_Class_Assigned[0] = '\0';
        }
    } else {
        printf("=> Da them giao vien moi '%s' (Ma GV: %s) thanh cong. (Chua phan cong lop)\n",
               newNode->Name, newNode->ID_Teacher);
    }
    pauseScreen(NULL);
}

void freeTeacherList(Teacher **LinkedListTeacher) {
    Teacher *current = *LinkedListTeacher;
    Teacher *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *LinkedListTeacher = NULL;
}

void saveTeachersToFile(Teacher *LinkedListTeacher, const char* filename) {
    FILE *file_ptr = fopen(filename, "wb");
    if (file_ptr == NULL) {
        fprintf(stderr, "LOI (saveTeachersToFile): Khong the mo file '%s' de ghi.\n", filename);
        perror("Nguyen nhan");
        return;
    }
    printf("Dang luu danh sach giao vien vao file '%s'...\n", filename);

    Teacher *current = LinkedListTeacher;
    int count = 0;
    while (current != NULL) {
        if (fwrite(current, sizeof(Teacher), 1, file_ptr) != 1) {
            fprintf(stderr, "LOI (saveTeachersToFile): Khong the ghi du lieu giao vien '%s' vao file.\n", current->ID_Teacher);
            break;
        }
        count++;
        current = current->next;
    }

    if (fclose(file_ptr) == EOF) {
        fprintf(stderr, "LOI (saveTeachersToFile): Khong the dong file '%s' sau khi ghi.\n", filename);
        perror("Nguyen nhan");
    } else if (current == NULL && count > 0) {
        printf("Da luu %d giao vien vao file '%s' thanh cong.\n", count, filename);
    } else if (count == 0) {
        printf("Danh sach giao vien rong, khong luu gi vao file '%s'.\n", filename);
    }
}

Teacher* loadTeachersFromFile(const char* filename) {
    FILE *file_ptr = fopen(filename, "rb");
    Teacher *dsLoadedHead = NULL;
    Teacher tempTeacherData;

    if (file_ptr == NULL) {
        return NULL;
    }
    printf("Dang tai danh sach giao vien tu file '%s'...\n", filename);

    int count = 0;
    while (fread(&tempTeacherData, sizeof(Teacher), 1, file_ptr) == 1) {
        Teacher *newNode = createTeacherNode(tempTeacherData);
        if (newNode == NULL) {
            fprintf(stderr, "LOI (loadTeachersFromFile): Khong the cap phat bo nho cho node khi tai tu file.\n");
            continue;
        }
        addTeacherToList(&dsLoadedHead, newNode);
        count++;
    }

    if (ferror(file_ptr)) {
        fprintf(stderr, "LOI (loadTeachersFromFile): Co loi xay ra khi doc du lieu tu file '%s'.\n", filename);
        perror("Nguyen nhan");
        freeTeacherList(&dsLoadedHead);
        dsLoadedHead = NULL;
    }

    if (fclose(file_ptr) == EOF) {
        fprintf(stderr, "LOI (loadTeachersFromFile): Khong the dong file '%s' sau khi tai.\n", filename);
        perror("Nguyen nhan");
    }

    if (dsLoadedHead != NULL && !ferror(file_ptr)) {
        printf("Da tai %d giao vien tu file '%s' thanh cong.\n", count, filename);
    } else if (!ferror(file_ptr) && count == 0) {
        printf("File '%s' rong hoac khong chua du lieu giao vien hop le.\n", filename);
    }
    return dsLoadedHead;
}