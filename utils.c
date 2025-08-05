#include "utils.h"

// Hàm này dùng để xóa dữ liệu trong buffer
void clear_stdin_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Hàm này dùng để chuyển hết về chữ thường
char* stringLowerCopy(const char* str)  {
    size_t size  = strlen(str);
    char *lowerStr = (char*)malloc(size + 1);
    for(size_t i = 0; i <= size; i++)  {
        char oriChar = str[i];
        char convertChar = oriChar;
        if(oriChar >= 'A' && oriChar <= 'Z')    {
            convertChar = oriChar + 32;
        }
        lowerStr[i] = convertChar;
    }
    return lowerStr;
}

void clearScreen() {
    // Kiểm tra hệ điều hành để dùng lệnh phù hợp
    // _WIN32 và _WIN64 thường được định nghĩa bởi các trình biên dịch trên Windows
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        // Giả sử là các hệ thống dựa trên UNIX (Linux, macOS)
        system("clear");
    #endif
}

void pauseScreen(const char* message) {
    // 1. Hiển thị thông điệp tùy chọn (nếu có)
    if (message != NULL && strlen(message) > 0) {
        printf("%s\n", message);
    }
    //printf("Nhan Enter de tiep tuc...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == '\n') break; // Đã "ăn" được newline rồi thì dừng
    }
}


