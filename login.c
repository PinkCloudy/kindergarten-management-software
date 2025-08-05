#include <stdio.h>
#include <string.h>
#include "login.h"

#define MAX_LINE 256

static bool checkLogin(const char* username, const char* password) {
    FILE* file = fopen("users.txt", "r");
    if (!file) {
        printf("Không thể mở file users.txt\n");
        return false;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        // loại bỏ newline cuối dòng
        line[strcspn(line, "\n")] = 0;

        // tách username và password từ line
        char fileUser[100], filePass[100];
        char* token = strtok(line, ",");
        if (token) {
            strcpy(fileUser, token);
            //strok dùng để tách chuỗi
            token = strtok(NULL, ",");
            if (token) {
                strcpy(filePass, token);
                // so sánh với username, password nhập vào
                if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
                    fclose(file);
                    return true;
                }
            }
        }
    }

    fclose(file);
    return false;
}
bool login() {
    char username[100];
    char password[100];
    int attempts = 3;

    while (attempts > 0) {
        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;

        if (checkLogin(username, password)) {
            printf("Dang nhap thanh cong!\n");
            return true;
        } else {
            attempts--;
            printf("Sai username hoac password! ban con %d lan thu.\n", attempts);
        }
    }
    printf("Ban da nhap sai qua so lan vui long thu lai sau !.\n");
    return false;
}
