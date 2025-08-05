#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menuteacher.h"
#include "teacher.h"
#include "class.h"
#include "utils.h"
#include "define.h"

void menuTeacher(Teacher **LinkedListTeacher, Class *LinkedListClass) {
    int luaChon;
    char searchBuffer[MAX_NAME];
    Teacher *foundTeacher = NULL;
    const char* TEACHER_DATA_FILE = "teachers_data.dat";

    // Tải danh sách giáo viên khi bắt đầu
    *LinkedListTeacher = loadTeachersFromFile(TEACHER_DATA_FILE);
    if (*LinkedListTeacher == NULL) {
        printf("Khong tai duoc du lieu giao vien hoac file '%s' khong ton tai/rong.\n", TEACHER_DATA_FILE);
        printf("Bat dau voi danh sach giao vien rong.\n");
    } else {
        printf("Da tai du lieu giao vien thanh cong.\n");
    }
    pauseScreen("Nhan Enter de vao menu...");

    do {
        system("cls");
        printf("+------------------------------------+\n");
        printf("|    MENU QUAN LY GIAO VIEN          |\n");
        printf("+------------------------------------+\n");
        printf("| 1. Them giao vien moi              |\n");
        printf("| 2. Hien thi danh sach giao vien    |\n");
        printf("| 3. Tim kiem giao vien theo ten     |\n");
        printf("| 4. Tim kiem giao vien theo ma      |\n");
        printf("| 5. Sua thong tin giao vien theo ma |\n");
        printf("| 6. Xoa giao vien theo ma           |\n");
        printf("| 0. Thoat va luu                    |\n");
        printf("+------------------------------------+\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar(); 

        switch (luaChon) {
            case 1:
                system("cls");
                addNewTeacher(LinkedListTeacher, LinkedListClass);
                pauseScreen("Nhan Enter de quay lai menu Teacher...");
                break;

            case 2:
                system("cls");
                displayTeacherList(*LinkedListTeacher);
                pauseScreen("Nhan Enter de quay lai menu Teacher...");
                break;

            case 3:
                system("cls");
                printf("Nhap ten giao vien can tim: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                findTeacher(*LinkedListTeacher, searchBuffer);
                pauseScreen("Nhan Enter de quay lai menu Teacher...");
                break;

            case 4:
                system("cls");
                printf("Nhap ma giao vien can tim: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                foundTeacher = findTeacherById(*LinkedListTeacher, searchBuffer);
                if (foundTeacher != NULL) {
                    printf("Tim thay giao vien:\n");
                    displayTeacherDetails(foundTeacher);
                } else {
                    printf("Khong tim thay giao vien voi ma %s\n", searchBuffer);
                }
                pauseScreen("Nhan Enter de quay lai menu Teacher...");
                break;

            case 5:
                system("cls");
                printf("Nhap ma giao vien can sua: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                editTeacherById(LinkedListTeacher, searchBuffer, LinkedListClass);
                pauseScreen("Nhan Enter de quay lai menu Teacher...");
                break;

            case 6:
                system("cls");
                printf("Nhap ma giao vien can xoa: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                if (deleteTeacherByID(LinkedListTeacher, searchBuffer, LinkedListClass)) {
                    printf("Da xoa giao vien thanh cong\n");
                } else {
                    printf("Xoa that bai hoac khong tim thay giao vien\n");
                }
                pauseScreen("Nhan Enter de quay lai menu Teacher...");
                break;

            case 0:
                system("cls");
                printf("Chuan bi thoat khoi quan ly giao vien...\n");
                printf("\nDang luu du lieu giao vien...\n");
                saveTeachersToFile(*LinkedListTeacher, TEACHER_DATA_FILE);
                break;

            default:
                printf("Lua chon khong hop le\n");
                pauseScreen("Nhan Enter de quay lai menu Teacher...");
        }

    } while (luaChon != 0);
}