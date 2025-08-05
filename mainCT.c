#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menureceipt.h"
#include "menuclass.h"
#include "menustudent.h"
#include "menuteacher.h"
#include "menuextracurricular.h"
#include "utils.h"
#include "define.h"
#include "login.h"
#include "menuhealth.h"

void syncClassCurrentSize(Class *LinkedListClass, Student *LinkedListStudent) {
    Class *currentClass = LinkedListClass;
    while (currentClass != NULL) {
        int count = 0;
        Student *currentStudent = LinkedListStudent;
        while (currentStudent != NULL) {
            if (strcmp(currentStudent->ID_Class, currentClass->classId) == 0) {
                count++;
            }
            currentStudent = currentStudent->next;
        }
        if (currentClass->currentSize != count) {
            printf("INFO: Dong bo si so lop %s: %d -> %d\n", currentClass->classId, currentClass->currentSize, count);
            currentClass->currentSize = count;
        }
        currentClass = currentClass->next;
    }
}

int main() {
    Node *danhSachPhieuThu = NULL;
    Class *danhSachLop = NULL;
    Student *danhSachHocSinh = NULL;
    Teacher *danhSachGiaoVien = NULL;
    Health *LinkedListHealth = NULL;

    LinkedListHealth = loadHealthFromFile("health_data.dat");
    ExtracurricularNode *extracurricularList = NULL;
    danhSachHocSinh = loadStudentsFromFile("students_data.dat");
    danhSachGiaoVien = loadTeachersFromFile("teachers_data.dat");
    danhSachLop = loadClassesFromFile("classes_data.dat");
    extracurricularList = loadExtracurricularFromFile("extracurricular_data.dat");
    loadReceiptsFromFile(&danhSachPhieuThu, "receipts_data.csv");
    syncClassCurrentSize(danhSachLop, danhSachHocSinh);
    system("cls");
    int luaChon;
    if (login()) {
        // Tiếp tục chương trình
        printf("Chao mung ban den he thong quan ly truong mam non.\n");
    } else {
        printf("Dang nhap that bai.\n");
        pauseScreen("Nhan Enter de thoat...");
        return 0;
    }
    do {
        
        system("cls");
        printf("+------------------------------------+\n");
        printf("|      MENU QUAN LY TRUONG HOC       |\n");
        printf("+------------------------------------+\n");
        printf("| 1. Quan ly phieu thu               |\n");
        printf("| 2. Quan ly lop hoc                 |\n");
        printf("| 3. Quan ly hoc sinh                |\n");
        printf("| 4. Quan ly giao vien               |\n");
        printf("| 5. Quan ly hoat dong ngoai khoa    |\n");
        printf("| 6. Suc khoe hoc sinh               |\n");
        printf("| 0. Thoat chuong trinh              |\n");
        printf("+------------------------------------+\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar(); // Xóa ký tự '\n' sau scanf

        switch (luaChon) {
            case 1:
                system("cls");
                menuReceipt(&danhSachPhieuThu);
                break;

            case 2:
                system("cls");
                menuClass(&danhSachLop, danhSachHocSinh, danhSachGiaoVien);
                break;

            case 3:
                system("cls");
                menuStudent(&danhSachHocSinh, danhSachLop);
                break;

            case 4:
                system("cls");
                menuTeacher(&danhSachGiaoVien, danhSachLop);
                break;

            case 5:
                system("cls");
                manageExtracurricularMenu(&extracurricularList, danhSachHocSinh);
                break;

            case 6:
                system("cls");
                menuHealth(&LinkedListHealth, danhSachHocSinh);
                break;

            case 0:
                system("cls");
                printf("Dang thoat chuong trinh...\n");
                break;

            default:
                system("cls");
                printf("Lua chon khong hop le\n");
                printf("\nNhan Enter de tiep tuc...");
                getchar();
        }

    } while (luaChon != 0);

    // Lưu dữ liệu trước khi thoát
    printf("\nDang luu du lieu...\n");
    saveReceiptsToFile(danhSachPhieuThu, "receipts.csv");
    saveClassesToFile(danhSachLop, "classes_data.dat");
    saveStudentsToFile(danhSachHocSinh, "students_data.dat");
    saveTeachersToFile(danhSachGiaoVien, "teachers_data.dat");

    // Giải phóng bộ nhớ
    printf("Dang giai phong bo nho...\n");
    freeReceiptList(&danhSachPhieuThu);
    freeClassList(&danhSachLop);
    freeStudentList(&danhSachHocSinh);
    freeTeacherList(&danhSachGiaoVien);

    printf("Da thoat chuong trinh.\n");
    pauseScreen(NULL);
    system("cls");

    return 0;
}