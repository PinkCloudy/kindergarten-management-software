#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menuhealth.h"
#include "health.h"
#include "utils.h"

void menuHealth(Health **LinkedListHealth, Student *LinkedListStudent) {
    int luaChon;
    char searchBuffer[MAX_ID];
    Health *foundHealth = NULL;
    const char* HEALTH_DATA_FILE = "health_data.dat";

    // Tải danh sách hồ sơ sức khỏe khi bắt đầu
    *LinkedListHealth = loadHealthFromFile(HEALTH_DATA_FILE);
    if (*LinkedListHealth == NULL) {
        printf("Khong tai duoc du lieu ho so suc khoe hoac file '%s' khong ton tai/rong.\n", HEALTH_DATA_FILE);
        printf("Bat dau voi danh sach ho so suc khoe rong.\n");
    } else {
        printf("Da tai du lieu ho so suc khoe thanh cong.\n");
    }
    pauseScreen("Nhan Enter de vao menu...");

    do {
        printf("+------------------------------------+\n");
        printf("|    MENU QUAN LY HO SO SUC KHOE     |\n");
        printf("+------------------------------------+\n");
        printf("| 1. Them ho so suc khoe moi         |\n");
        printf("| 2. Hien thi danh sach ho so        |\n");
        printf("| 3. Tim kiem ho so theo ma HS       |\n");
        printf("| 4. Tim kiem ho so theo ma ho so    |\n");
        printf("| 5. Sua thong tin ho so theo ma     |\n");
        printf("| 6. Xoa ho so theo ma               |\n");
        printf("| 0. Thoat va luu                    |\n");
        printf("+------------------------------------+\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar(); // Xóa ký tự '\n' sau scanf

        switch (luaChon) {
            case 1:
                system("cls");
                addNewHealth(LinkedListHealth, LinkedListStudent);
                pauseScreen("Nhan Enter de quay lai menu Health...");
                break;

            case 2:
                system("cls");
                displayHealthList(*LinkedListHealth);
                pauseScreen("Nhan Enter de quay lai menu Health...");
                break;

            case 3:
                system("cls");
                printf("Nhap ma hoc sinh can tim: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                findHealth(*LinkedListHealth, searchBuffer);
                pauseScreen("Nhan Enter de quay lai menu Health...");
                break;

            case 4:
                system("cls");
                printf("Nhap ma ho so suc khoe can tim: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                foundHealth = findHealthById(*LinkedListHealth, searchBuffer);
                if (foundHealth != NULL) {
                    printf("Tim thay ho so suc khoe:\n");
                    displayHealthDetails(foundHealth);
                } else {
                    printf("Khong tim thay ho so suc khoe voi ma %s\n", searchBuffer);
                }
                pauseScreen("Nhan Enter de quay lai menu Health...");
                break;

            case 5:
                system("cls");
                printf("Nhap ma ho so suc khoe can sua: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                editHealthById(LinkedListHealth, searchBuffer, LinkedListStudent);
                pauseScreen("Nhan Enter de quay lai menu Health...");
                break;

            case 6:
                system("cls");
                printf("Nhap ma ho so suc khoe can xoa: ");
                fgets(searchBuffer, sizeof(searchBuffer), stdin);
                searchBuffer[strcspn(searchBuffer, "\n")] = 0;
                if (deleteHealthById(LinkedListHealth, searchBuffer, LinkedListStudent)) {
                    printf("Da xoa ho so suc khoe thanh cong\n");
                } else {
                    printf("Xoa that bai hoac khong tim thay ho so suc khoe\n");
                }
                pauseScreen("Nhan Enter de quay lai menu Health...");
                break;

            case 0:
                system("cls");
                printf("Chuan bi thoat khoi quan ly ho so suc khoe...\n");
                printf("\nDang luu du lieu ho so suc khoe...\n");
                saveHealthToFile(*LinkedListHealth, HEALTH_DATA_FILE);
                break;

            default:
                system("cls");
                printf("Lua chon khong hop le\n");
                pauseScreen("Nhan Enter de quay lai menu Health...");
        }
    } while (luaChon != 0);
}