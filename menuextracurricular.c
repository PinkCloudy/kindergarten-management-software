#include <stdio.h>
#include "menuextracurricular.h"
#include "extracurricular.h"
#include "student.h"
#include "utils.h"

void manageExtracurricularMenu(ExtracurricularNode** extracurricularList, struct Student* studentList) {
    int choice;
    char activityId[MAX_ID];
    ExtracurricularInfo extracurricularData;

    do {
        system("cls");
        printf("+------------------------------------+\n");
        printf("|       MENU HOAT DONG NK            |\n");
        printf("+------------------------------------+\n");
        printf("| 1. Them hoat dong moi              |\n");
        printf("| 2. Hien thi thong tin hoat dong     |\n");
        printf("| 3. Cap nhat thong tin hoat dong    |\n");
        printf("| 0. Quay lai menu chinh             |\n");
        printf("+------------------------------------+\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); // Xóa bộ đệm

        switch (choice) {
            case 1: // Thêm hoạt động ngoại khóa
                system("cls");
                addNewExtracurricular(extracurricularList, studentList);
                pauseScreen("Nhan enter de tiep tuc");
                break;

            case 2: // Hiển thị thông tin hoạt động
                system("cls");
                printf("\nHIEN THI THONG TIN HOAT DONG\n");
                printf("Nhap Ma Hoat Dong: ");
                fgets(activityId, MAX_ID, stdin);
                activityId[strcspn(activityId, "\n")] = 0;

                displayExtracurricular(*extracurricularList, activityId, studentList);
                pauseScreen("Nhan enter de tiep tuc");
                break;

            case 3: // Cập nhật thông tin hoạt động
                system("cls");
                printf("\nCAP NHAT THONG TIN HOAT DONG\n");
                printf("Nhap Ma Hoat Dong: ");
                fgets(activityId, MAX_ID, stdin);
                activityId[strcspn(activityId, "\n")] = 0;

                updateExtracurricular(*extracurricularList, activityId, studentList);
                saveExtracurricularToFile(*extracurricularList, "extracurricular_data.dat");
                pauseScreen("Nhan enter de tiep tuc");
                break;

            case 0:
                break;

            default:
                system("cls");
                printf("Lua chon khong hop le. Vui long nhap lai!\n");
                pauseScreen("Nhan enter de tiep tuc");
        }
    } while (choice != 0);
}