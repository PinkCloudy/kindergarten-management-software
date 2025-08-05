#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menustudent.h"
#include "student.h"
#include "class.h"
#include "utils.h"
#include "define.h"

void menuStudent(Student **LinkedListStudent, Class *LinkedListClass) {
    int luaChon;
    char searchBuffer[MAX_NAME];
    Student *foundStudent = NULL;
    const char* STUDENT_DATA_FILE = "students_data.dat";

    // Tải danh sách học sinh khi bắt đầu
    *LinkedListStudent = loadStudentsFromFile(STUDENT_DATA_FILE);
    if (*LinkedListStudent == NULL) {
        printf("Khong tai duoc du lieu hoc sinh hoac file '%s' khong ton tai/rong.\n", STUDENT_DATA_FILE);
        printf("Bat dau voi danh sach hoc sinh rong.\n");
    } else {
        printf("Da tai du lieu hoc sinh thanh cong.\n");
    }
    pauseScreen("Nhan Enter de vao menu...");

    do {

        printf("+------------------------------------+\n");
        printf("|    MENU QUAN LY HOC SINH           |\n");
        printf("+------------------------------------+\n");
        printf("| 1. Them hoc sinh moi               |\n");
        printf("| 2. Hien thi danh sach hoc sinh     |\n");
        printf("| 3. Tim kiem hoc sinh theo ten      |\n");
        printf("| 4. Tim kiem hoc sinh theo ma       |\n");
        printf("| 5. Sua thong tin hoc sinh theo ma  |\n");
        printf("| 6. Xoa hoc sinh theo ma            |\n");
        printf("| 0. Thoat va luu                    |\n");
        printf("+------------------------------------+\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar(); 

        switch (luaChon) {
            case 1:
                system("cls");
                addNewStudent(LinkedListStudent, LinkedListClass);
                pauseScreen("Nhan Enter de quay lai menu Student...");
                break;

            case 2:
                system("cls");
                displayStudentList(*LinkedListStudent);
                pauseScreen("Nhan Enter de quay lai menu Student...");
                break;

            case 3:
                system("cls");
                printf("Nhap ten hoc sinh can tim: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                findStudent(*LinkedListStudent, searchBuffer);
                pauseScreen("Nhan Enter de quay lai menu Student...");
                break;

            case 4:
                system("cls");
                printf("Nhap ma hoc sinh can tim: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                foundStudent = findStudentById(*LinkedListStudent, searchBuffer);
                if (foundStudent != NULL) {
                    printf("Tim thay hoc sinh:\n");
                    displayStudentDetails(foundStudent);
                } else {
                    printf("Khong tim thay hoc sinh voi ma %s\n", searchBuffer);
                }
                pauseScreen("Nhan Enter de quay lai menu Student...");
                break;

            case 5:
                system("cls");
                printf("Nhap ma hoc sinh can sua: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                editStudentById(LinkedListStudent, searchBuffer, LinkedListClass);
                pauseScreen("Nhan Enter de quay lai menu Student...");
                break;

            case 6:
                system("cls");
                printf("Nhap ma hoc sinh can xoa: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                if (deleteStudentByID(LinkedListStudent, searchBuffer, LinkedListClass)) {
                    printf("Da xoa hoc sinh thanh cong\n");
                } else {
                    printf("Xoa that bai hoac khong tim thay hoc sinh\n");
                }
                pauseScreen("Nhan Enter de quay lai menu Student...");
                break;

            case 0:
                system("cls");
                printf("Chuan bi thoat khoi quan ly hoc sinh...\n");
                printf("\nDang luu du lieu hoc sinh...\n");
                saveStudentsToFile(*LinkedListStudent, STUDENT_DATA_FILE);
                break;

            default:
                system("cls");
                printf("Lua chon khong hop le\n");
                pauseScreen("Nhan Enter de quay lai menu Student...");
        }

    } while (luaChon != 0);
}