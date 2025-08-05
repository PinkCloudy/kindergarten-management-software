#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menuclass.h"
#include "class.h"
#include "student.h"
#include "teacher.h"
#include "utils.h"
#include "define.h"

void menuClass(Class **LinkedListClass, Student *LinkedListStudent, Teacher *LinkedListTeacher) {
    int luaChon;
    char maLop[MAX_ID];
    const char* CLASS_DATA_FILE = "classes_data.dat";

    do {
        system("cls");
        printf("+------------------------------------+\n");
        printf("|       MENU QUAN LY LOP HOC         |\n");
        printf("+------------------------------------+\n");
        printf("| 1. Them lop hoc moi                |\n");
        printf("| 2. Hien thi tat ca lop hoc         |\n");
        printf("| 3. Tim kiem lop hoc theo ma        |\n");
        printf("| 4. Xoa lop hoc theo ma             |\n");
        printf("| 5. Cap nhat thong tin lop hoc      |\n");
        printf("| 0. Quay lai menu chinh             |\n");
        printf("+------------------------------------+\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar(); // Xóa ký tự '\n' sau scanf

        switch (luaChon) {
            case 1:
                system("cls");
                addNewClass(LinkedListClass, LinkedListTeacher);
                saveClassesToFile(*LinkedListClass, CLASS_DATA_FILE);
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 2:
                system("cls");
                displayClassList(*LinkedListClass);
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 3:
                system("cls");
                printf("Nhap ma lop hoc can tim: ");
                fgets(maLop, MAX_ID, stdin);
                maLop[strcspn(maLop, "\n")] = 0;
                {
                    Class *foundClass = findClassById(*LinkedListClass, maLop);
                    if (foundClass) {
                        displayClassDetailsAndStudents(foundClass, LinkedListStudent);
                    } else {
                        printf("Khong tim thay lop hoc voi ma %s\n", maLop);
                    }
                }
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 4:
                system("cls");
                printf("Nhap ma lop hoc can xoa: ");
                fgets(maLop, MAX_ID, stdin);
                maLop[strcspn(maLop, "\n")] = 0;
                if (deleteClassById(LinkedListClass, maLop, LinkedListStudent)) {
                    printf("Da xoa lop hoc thanh cong\n");
                    saveClassesToFile(*LinkedListClass, CLASS_DATA_FILE);
                } else {
                    printf("Xoa lop hoc that bai\n");
                }
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 5:
                system("cls");
                printf("Nhap ma lop hoc can cap nhat: ");
                fgets(maLop, MAX_ID, stdin);
                maLop[strcspn(maLop, "\n")] = 0;
                printf("Chuc nang cap nhat thong tin lop hoc chua duoc trien khai (can updateClassInfoById).\n");
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 0:
                system("cls");
                printf("Dang quay lai menu chinh...\n");
                printf("\nDang luu du lieu lop hoc...\n");
                saveClassesToFile(*LinkedListClass, CLASS_DATA_FILE);
                break;

            default:
                system("cls");
                printf("Lua chon khong hop le\n");
                printf("\nNhan Enter de tiep tuc...");
                getchar();
        }

    } while (luaChon != 0);
}