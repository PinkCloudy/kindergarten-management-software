#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
#include "utils.h"
#include "class.h"

Student* createStudentNode(Student dataStudent) {
    Student *newNode = (Student*)malloc(sizeof(Student));
    strcpy(newNode->ID_Student, dataStudent.ID_Student);
    strcpy(newNode->Name, dataStudent.Name);
    strcpy(newNode->Date, dataStudent.Date);
    strcpy(newNode->Gender, dataStudent.Gender);
    strcpy(newNode->Address, dataStudent.Address);
    strcpy(newNode->NameParent, dataStudent.NameParent);
    strcpy(newNode->PhoneParent, dataStudent.PhoneParent);
    strcpy(newNode->ID_Class, dataStudent.ID_Class);
    newNode->next = NULL;
    return newNode;
}

void addStudentToList(Student **LinkedListStudent, Student *newNode) {
    newNode->next = *LinkedListStudent;
    *LinkedListStudent = newNode;
}

void displayStudentList(Student *LinkedList) {
    Student *ptr = LinkedList;
    int count = 0;
    printf("\nDANH SACH HOC SINH\n");
    if (ptr == NULL) {
        printf("Danh sach hoc sinh rong.\n");
    } else {
        printf("STT  Ma HS      Ho Ten                       Lop\n");
        while (ptr != NULL) {
            count++;
            printf("%-5d%-11s%-29s%-10s\n", count, ptr->ID_Student, ptr->Name, ptr->ID_Class);
            ptr = ptr->next;
        }
        printf("Tong so hoc sinh: %d\n", count);
    }
}

void displayStudentDetails(Student *student) {
    if (student == NULL) {
        printf("\nKhong co thong tin cua hoc sinh.\n");
        return;
    }
    printf("\nTHONG TIN HOC SINH\n");
    printf("Ma HS: %s\n", student->ID_Student);
    printf("Ho Ten: %s\n", student->Name);
    printf("Ngay sinh: %s\n", student->Date);
    printf("Gioi tinh: %s\n", student->Gender);
    printf("Dia chi: %s\n", student->Address);
    printf("Ten phu huynh: %s\n", student->NameParent);
    printf("SDT phu huynh: %s\n", student->PhoneParent);
    printf("Lop: %s\n", student->ID_Class);
}

int findStudent(Student *LinkedList, const char* nameQuery) {
    Student *ptr = LinkedList;
    int count = 0;
    int foundCount = 0;
    printf("\nKET QUA TIM KIEM\n");
    if (LinkedList == NULL) {
        printf("Danh sach rong.\n");
        return 0;
    }
    if (nameQuery == NULL || strlen(nameQuery) == 0) {
        printf("Vui long nhap ten hoc sinh can tim.\n");
        return 0;
    }
    char *lowerNameQuery = stringLowerCopy(nameQuery);
    printf("STT  Ma HS      Ho Ten                       Ma Lop\n");
    while (ptr != NULL) {
        count++;
        char *lowerPtrName = stringLowerCopy(ptr->Name);
        if (lowerPtrName != NULL) {
            if (strstr(lowerPtrName, lowerNameQuery) != NULL) {
                foundCount++;
                printf("%-5d%-11s%-29s%-10s\n", foundCount, ptr->ID_Student, ptr->Name, ptr->ID_Class);
            }
            free(lowerPtrName);
        }
        ptr = ptr->next;
    }
    free(lowerNameQuery);
    if (foundCount == 0) {
        printf("Khong tim thay hoc sinh nao co ten chua '%s'.\n", nameQuery);
    }
    printf("Tim thay %d hoc sinh.\n", foundCount);
    return foundCount;
}


Student* findStudentById(Student *LinkedList, const char* ID) {
    if (ID == NULL) {
        fprintf(stderr, "ERROR (findStudentById): Ma Hoc Sinh can tim la NULL.\n");
        return NULL;
    }
    if (LinkedList == NULL) {
        return NULL;
    }
    Student *current = LinkedList;
    while (current != NULL) {
        if (strcmp(current->ID_Student, ID) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int deleteStudentByID(Student **LinkedList, const char* ID, Class *LinkedListClass) {
    if (ID == NULL || *LinkedList == NULL) {
        printf("\nLOI: Du lieu dau vao khong hop le.\n");
        return 0;
    }

    Student *nodeToDelete = *LinkedList;
    Student *previousNode = NULL;
    char idLopCuaHocSinh[MAX_ID] = "";

    if (strcmp(nodeToDelete->ID_Student, ID) == 0) {
        strcpy(idLopCuaHocSinh, nodeToDelete->ID_Class);
        *LinkedList = nodeToDelete->next;
        printf("\nDa xoa hoc sinh: MaHS %s - Ten %s\n", nodeToDelete->ID_Student, nodeToDelete->Name);
        free(nodeToDelete);
        if (strlen(idLopCuaHocSinh) > 0) {
            Class* classNode = findClassById(LinkedListClass, idLopCuaHocSinh);
            if (classNode != NULL) {
                decrementClassSize(classNode);
                saveClassesToFile(LinkedListClass, "classes_data.dat");
            }
        }
        saveStudentsToFile(*LinkedList, "students_data.dat");
        return 1;
    }

    previousNode = nodeToDelete;
    nodeToDelete = nodeToDelete->next;
    while (nodeToDelete != NULL) {
        if (strcmp(nodeToDelete->ID_Student, ID) == 0) {
            strcpy(idLopCuaHocSinh, nodeToDelete->ID_Class);
            previousNode->next = nodeToDelete->next;
            printf("\nDa xoa hoc sinh: MaHS %s - Ten %s\n", nodeToDelete->ID_Student, nodeToDelete->Name);
            free(nodeToDelete);
            if (strlen(idLopCuaHocSinh) > 0) {
                Class* classNode = findClassById(LinkedListClass, idLopCuaHocSinh);
                if (classNode != NULL) {
                    decrementClassSize(classNode);
                    saveClassesToFile(LinkedListClass, "classes_data.dat");
                }
            }
            saveStudentsToFile(*LinkedList, "students_data.dat");
            return 1;
        }
        previousNode = nodeToDelete;
        nodeToDelete = nodeToDelete->next;
    }
    printf("\nKhong tim thay hoc sinh voi Ma HS '%s'.\n", ID);
    return 0;
}

int editStudentById(Student **LinkedList, const char *ID, Class *LinkedListClass) {
    if (ID == NULL) {
        fprintf(stderr, "ERROR (editStudentById): Ma Hoc Sinh can sua la NULL.\n");
        return 0;
    }

    Student *studentToUpdate = findStudentById(*LinkedList, ID);
    if (studentToUpdate == NULL) {
        printf("\nKhong tim thay hoc sinh co Ma HS: %s de sua.\n", ID);
        return 0;
    }

    printf("\nTHONG TIN HIEN TAI CUA HOC SINH %s\n", studentToUpdate->ID_Student);
    displayStudentDetails(studentToUpdate);

    printf("\nNHAP THONG TIN MOI (De trong va Enter de giu nguyen)\n");

    char buffer[256];
    char oldClassId[MAX_ID]; 
    strcpy(oldClassId, studentToUpdate->ID_Class); 

    while (getchar() != '\n'); 

    printf("Ho Ten hien tai: %s\nNhap Ho Ten moi: ", studentToUpdate->Name);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(studentToUpdate->Name, buffer);

    printf("Ngay Sinh hien tai: %s\nNhap Ngay Sinh moi: ", studentToUpdate->Date);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(studentToUpdate->Date, buffer);

    printf("Gioi Tinh hien tai: %s\nNhap Gioi Tinh moi: ", studentToUpdate->Gender);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(studentToUpdate->Gender, buffer);

    printf("Ten Phu Huynh hien tai: %s\nNhap Ten Phu Huynh moi: ", studentToUpdate->NameParent);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(studentToUpdate->NameParent, buffer);

    printf("SDT Phu Huynh hien tai: %s\nNhap SDT Phu Huynh moi: ", studentToUpdate->PhoneParent);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(studentToUpdate->PhoneParent, buffer);

    printf("Dia Chi hien tai: %s\nNhap Dia Chi moi: ", studentToUpdate->Address);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(studentToUpdate->Address, buffer);

    printf("Ma Lop hien tai: %s\nNhap Ma Lop moi: ", studentToUpdate->ID_Class);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    if (strlen(buffer) > 0 && strcmp(buffer, studentToUpdate->ID_Class) != 0) {
        if (LinkedListClass != NULL) {
            Class* targetClass = findClassById(LinkedListClass, buffer);
            if (targetClass == NULL) {
                printf("Loi: Ma Lop '%s' khong ton tai.\n", buffer);
            } else if (targetClass->currentSize >= targetClass->maxSize) {
                printf("Loi: Lop '%s' da day (%d/%d).\n", targetClass->classId, targetClass->currentSize, targetClass->maxSize);
            } else {
                if (strlen(oldClassId) > 0 && strcmp(oldClassId, "CHUA_XEP") != 0) {
                    Class* oldClass = findClassById(LinkedListClass, oldClassId);
                    if (oldClass != NULL) {
                        decrementClassSize(oldClass);
                    }
                }
                incrementClassSize(targetClass);
                strcpy(studentToUpdate->ID_Class, buffer);
                saveClassesToFile(LinkedListClass, "classes_data.dat");
            }
        } else {
            printf("Loi: Khong co ds lop de kiem tra.\n");
        }
    }

    saveStudentsToFile(*LinkedList, "students_data.dat");

    printf("\nDa cap nhat thong tin cho hoc sinh %s.\n", studentToUpdate->ID_Student);
    displayStudentDetails(studentToUpdate);
    return 1;
}

Student inputStudentData(Class* LinkedListClass) {
    Student newStudentData;
    char tempIdClass[MAX_ID];
    bool classIsValidAndAvailable = false;

    newStudentData.ID_Student[0] = '\0';

    printf("\nNHAP THONG TIN HOC SINH MOI\n");
    printf("(Nhap 'huy' vao Ma HS de huy)\n");

    do {
        printf("Nhap Ma Hoc Sinh (vd: HS001): ");
        fgets(newStudentData.ID_Student, sizeof(newStudentData.ID_Student), stdin);
        newStudentData.ID_Student[strcspn(newStudentData.ID_Student, "\n")] = 0;

        if (strcmp(newStudentData.ID_Student, "huy") == 0) {
            printf("Da huy bo them hoc sinh.\n");
            newStudentData.ID_Student[0] = '\0';
            return newStudentData;
        }

        if (strlen(newStudentData.ID_Student) == 0) {
            printf("Ma Hoc Sinh khong duoc de trong.\n");
        }
    } while (strlen(newStudentData.ID_Student) == 0);

    printf("Nhap Ho Ten: ");
    fgets(newStudentData.Name, sizeof(newStudentData.Name), stdin);
    newStudentData.Name[strcspn(newStudentData.Name, "\n")] = 0;
    while (strlen(newStudentData.Name) == 0) {
        printf("Ho Ten khong duoc de trong.\n");
        printf("Nhap lai Ho Ten: ");
        fgets(newStudentData.Name, sizeof(newStudentData.Name), stdin);
        newStudentData.Name[strcspn(newStudentData.Name, "\n")] = 0;
    }

    printf("Nhap Ngay Sinh (dd/mm/yyyy): ");
    fgets(newStudentData.Date, sizeof(newStudentData.Date), stdin);
    newStudentData.Date[strcspn(newStudentData.Date, "\n")] = 0;

    printf("Nhap Gioi Tinh (Nam/Nu/Khac): ");
    fgets(newStudentData.Gender, sizeof(newStudentData.Gender), stdin);
    newStudentData.Gender[strcspn(newStudentData.Gender, "\n")] = 0;

    printf("Nhap Ten Phu Huynh: ");
    fgets(newStudentData.NameParent, sizeof(newStudentData.NameParent), stdin);
    newStudentData.NameParent[strcspn(newStudentData.NameParent, "\n")] = 0;

    printf("Nhap SDT Phu Huynh: ");
    fgets(newStudentData.PhoneParent, sizeof(newStudentData.PhoneParent), stdin);
    newStudentData.PhoneParent[strcspn(newStudentData.PhoneParent, "\n")] = 0;

    printf("Nhap Dia Chi: ");
    fgets(newStudentData.Address, sizeof(newStudentData.Address), stdin);
    newStudentData.Address[strcspn(newStudentData.Address, "\n")] = 0;

    if (LinkedListClass == NULL) {
        printf("CANH BAO: Khong co ds lop.\n");
        strcpy(newStudentData.ID_Class, "CHUA_XEP");
        classIsValidAndAvailable = true;
    } else {
        do {
            printf("Nhap Ma Lop (ID_Class): ");
            fgets(tempIdClass, sizeof(tempIdClass), stdin);
            tempIdClass[strcspn(tempIdClass, "\n")] = 0;

            if (strlen(tempIdClass) == 0) {
                printf("Ma Lop khong duoc de trong.\n");
                continue;
            }

            Class* targetClass = findClassById(LinkedListClass, tempIdClass);
            if (targetClass == NULL) {
                printf("LOI: Ma Lop '%s' khong ton tai.\n", tempIdClass);
            } else if (targetClass->currentSize >= targetClass->maxSize) {
                printf("LOI: Lop '%s' da day (%d/%d).\n", targetClass->classId, targetClass->currentSize, targetClass->maxSize);
            } else {
                strcpy(newStudentData.ID_Class, tempIdClass);
                classIsValidAndAvailable = true;
            }
        } while (!classIsValidAndAvailable);
    }

    printf("Da hoan tat nhap thong tin.\n");
    return newStudentData;
}

void addNewStudent(Student **LinkedListStudent, Class *LinkedListClass) {
    printf("\nTHEM HOC SINH MOI\n");

    Student studentDataFromUser = inputStudentData(LinkedListClass);
    if (strlen(studentDataFromUser.ID_Student) == 0) {
        return;
    }

    if (findStudentById(*LinkedListStudent, studentDataFromUser.ID_Student) != NULL) {
        printf("LOI: Ma HS '%s' da ton tai.\n", studentDataFromUser.ID_Student);
        pauseScreen(NULL);
        return;
    }

    Student *newNode = createStudentNode(studentDataFromUser);
    if (newNode == NULL) {
        fprintf(stderr, "LOI: Khong the cap phat bo nho.\n");
        pauseScreen(NULL);
        return;
    }

    addStudentToList(LinkedListStudent, newNode);
    Class* targetClass = findClassById(LinkedListClass, newNode->ID_Class);
    if (targetClass != NULL) {
        if (incrementClassSize(targetClass)) {
            printf("Da them HS '%s' (Ma: %s) vao lop '%s' thanh cong!\n", newNode->Name, newNode->ID_Student, targetClass->className);
            printf("Si so: %d/%d.\n", targetClass->currentSize, targetClass->maxSize);
            saveClassesToFile(LinkedListClass, "classes_data.dat");
        } else {
            fprintf(stderr, "LOI: Lop '%s' da day.\n", targetClass->className);
        }
    }
    saveStudentsToFile(*LinkedListStudent, "students_data.dat");
    pauseScreen(NULL);
}

void freeStudentList(Student **LinkedList) {
    Student *current = *LinkedList;
    Student *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *LinkedList = NULL;
}

void saveStudentsToFile(Student *LinkedList, const char* filename) {
    FILE *file_ptr = fopen(filename, "wb");
    if (file_ptr == NULL) {
        fprintf(stderr, "LOI (saveStudentsToFile): Khong the mo file '%s' de ghi.\n", filename);
        perror("Nguyen nhan");
        return;
    }

    Student *current = LinkedList;
    int count = 0;
    while (current != NULL) {
        if (fwrite(current, sizeof(Student), 1, file_ptr) != 1) {
            fprintf(stderr, "LOI (saveStudentsToFile): Khong the ghi du lieu hoc sinh '%s' vao file.\n", current->ID_Student);
            break;
        }
        count++;
        current = current->next;
    }

    if (fclose(file_ptr) == EOF) {
        fprintf(stderr, "LOI (saveStudentsToFile): Khong the dong file '%s' sau khi ghi.\n", filename);
        perror("Nguyen nhan");
    }
}

Student* loadStudentsFromFile(const char* filename) {
    FILE *file_ptr = fopen(filename, "rb");
    Student *dsLoadedHead = NULL;
    Student tempStudentData;

    if (file_ptr == NULL) {
        return NULL;
    }

    int count = 0;
    while (fread(&tempStudentData, sizeof(Student), 1, file_ptr) == 1) {
        Student *newNode = createStudentNode(tempStudentData);
        if (newNode == NULL) {
            fprintf(stderr, "LOI (loadStudentsFromFile): Khong the cap phat bo nho cho node khi tai tu file.\n");
            continue;
        }
        addStudentToList(&dsLoadedHead, newNode);
        count++;
    }

    if (ferror(file_ptr)) {
        fprintf(stderr, "LOI (loadStudentsFromFile): Co loi xay ra khi doc du lieu tu file '%s'.\n", filename);
        perror("Nguyen nhan");
        freeStudentList(&dsLoadedHead);
        dsLoadedHead = NULL;
    }

    if (fclose(file_ptr) == EOF) {
        fprintf(stderr, "LOI (loadStudentsFromFile): Khong the dong file '%s' sau khi tai.\n", filename);
        perror("Nguyen nhan");
    }

    return dsLoadedHead;
}