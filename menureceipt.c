#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menureceipt.h"

void menuReceipt(Node** danhSachPhieuThu) {
    int luaChon;
    char maPhieu[MAX_ID];

    // Load danh sach ngay khi vao menu
    loadReceiptsFromFile(danhSachPhieuThu, "receipts.csv");

    do {
        system("cls");
        printf("+------------------------------------+\n");
        printf("|      MENU PHIEU THU                |\n");
        printf("+------------------------------------+\n");
        printf("| 1. Them phieu thu                  |\n");
        printf("| 2. Hien thi tat ca phieu thu       |\n");
        printf("| 3. Tim kiem phieu thu theo ma      |\n");
        printf("| 4. Xoa phieu thu theo ma           |\n");
        printf("| 5. Cap nhat phieu thu theo ma      |\n");
        printf("| 6. Tinh tong doanh thu             |\n");
        printf("| 0. Quay lai menu chinh             |\n");
        printf("+------------------------------------+\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar(); // Xóa ký tự '\n' sau scanf

        switch (luaChon) {
            case 1:
                system("cls");
                addReceipt(danhSachPhieuThu);
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 2:
                system("cls");
                displayAllReceipts(*danhSachPhieuThu);
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 3:
                system("cls");
                printf("Nhap ma phieu thu can tim: ");
                fgets(maPhieu, MAX_ID, stdin);
                maPhieu[strcspn(maPhieu, "\n")] = 0;
                {
                    Node* timThay = searchReceiptByID(*danhSachPhieuThu, maPhieu);
                    if (timThay) {
                        printf("Tim thay: %s | %s | %s | %.2lf | %d/%d | %s\n",
                            timThay->data.ID_Receipt, timThay->data.ID_Student, timThay->data.Date,
                            timThay->data.Amount, timThay->data.Month, timThay->data.Year, timThay->data.Status);
                    } else {
                        printf("Khong tim thay phieu thu\n");
                    }
                }
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 4:
                system("cls");
                printf("Nhap ma phieu thu can xoa: ");
                fgets(maPhieu, MAX_ID, stdin);
                maPhieu[strcspn(maPhieu, "\n")] = 0;
                if (deleteReceiptByID(danhSachPhieuThu, maPhieu)) {
                    printf("Da xoa phieu thu thanh cong\n");
                } else {
                    printf("Khong tim thay phieu thu can xoa\n");
                }
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 5:
                system("cls");
                printf("Nhap ma phieu thu can cap nhat: ");
                fgets(maPhieu, MAX_ID, stdin);
                maPhieu[strcspn(maPhieu, "\n")] = 0;
                updateReceiptByID(*danhSachPhieuThu, maPhieu);
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 6:
                system("cls");
                printf("Tong doanh thu la: %.2f\n", calculateTotalRevenue(*danhSachPhieuThu));
                printf("\nNhan Enter de tiep tuc...");
                getchar();
                break;

            case 0:
                system("cls");
                printf("Dang quay lai menu chinh...\n");
                saveReceiptsToFile(*danhSachPhieuThu, "receipts.csv");
                break;

            default:
                printf("Lua chon khong hop le\n");
                printf("\nNhan Enter de tiep tuc...");
                getchar();
        }

    } while (luaChon != 0);
}