#include "class.h"
#include "student.h" 
#include "utils.h" 
#include "teacher.h"  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Các hàm CRUD cơ bản cho Class ---

Class* createClassNode(const char* classId, const char* className, int maxSize, const char* maGVCN) {
    if (classId == NULL || className == NULL || maGVCN == NULL) { // Kiểm tra đầu vào cơ bản
        fprintf(stderr, "Loi (createClassNode): Du lieu dau vao khong hop le.\n");
        return NULL;
    }
    Class* newClassNode = (Class*)malloc(sizeof(Class));
    if (newClassNode == NULL) {
        perror("Loi (createClassNode): Khong the cap phat bo nho");
        return NULL;
    }
    strcpy(newClassNode->classId, classId);
    strcpy(newClassNode->className, className);
    newClassNode->maxSize = maxSize;
    newClassNode->currentSize = 0; // Sĩ số 
    strcpy(newClassNode->maGVCN, maGVCN);
    // Bỏ: newClassNode->studentList = NULL;
    newClassNode->next = NULL;
    return newClassNode;
}

void addClassToList(Class** LinkedListClass, Class* newClassNode) {
    if (newClassNode == NULL) return;
    newClassNode->next = *LinkedListClass;
    *LinkedListClass = newClassNode;
}

Class* findClassById(Class* LinkedListClass, const char* classId) {
    if (classId == NULL) return NULL;
    Class* current = LinkedListClass;
    while (current != NULL) {
        if (strcmp(current->classId, classId) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayClassList(Class* LinkedListClass) {
    printf("\n--- DANH SACH LOP HOC ---\n");
    if (LinkedListClass == NULL) {
        printf("Chua co lop hoc nao.\n");
        printf("---------------------------\n");
        return;
    }
    printf("| %-8s | %-20s | %-10s | %-6s / %-6s |\n", "Ma Lop", "Ten Lop", "GVCN", "Si So", "Toi Da");
    printf("-------------------------------------------------------------------\n");
    Class* current = LinkedListClass;
    while (current != NULL) {
        printf("| %-8s | %-20s | %-10s | %-6d / %-6d |\n",
               current->classId,
               current->className,
               current->maGVCN,
               current->currentSize,
               current->maxSize);
        current = current->next;
    }
    printf("-------------------------------------------------------------------\n");
}

int deleteClassById(Class** LinkedListClass, const char* classId, Student* LinkedListStudent) {
    if (classId == NULL || *LinkedListClass == NULL) {
        return 0;
    }

    // 1. Kiểm tra xem có học sinh nào thuộc lớp này không
    Student* currentStudent = LinkedListStudent;
    while (currentStudent != NULL) {
        // Dùng đúng tên trường mã lớp trong struct Student của Dũng
        // Ví dụ: currentStudent->Class hoặc currentStudent->ID_Class
        if (strcmp(currentStudent->ID_Class, classId) == 0) {
            printf("LOI: Khong the xoa lop '%s' vi van con hoc sinh (Ma HS: %s) trong lop.\n",
                   classId, currentStudent->ID_Student);
            printf("Vui long chuyen hoac xoa hoc sinh khoi lop truoc.\n");
            return 0; // Không cho xóa
        }
        currentStudent = currentStudent->next;
    }

    // 2. Nếu không còn học sinh, tiến hành xóa lớp
    Class *currentClass = *LinkedListClass;
    Class *previousClass = NULL;

    // Xóa node đầu
    if (strcmp(currentClass->classId, classId) == 0) {
        *LinkedListClass = currentClass->next;
        printf("INFO: Da xoa lop: %s - %s\n", currentClass->classId, currentClass->className);
        free(currentClass);
        return 1;
    }

    // Tìm node cần xóa và node trước đó
    previousClass = currentClass;
    currentClass = currentClass->next;
    while (currentClass != NULL) {
        if (strcmp(currentClass->classId, classId) == 0) {
            previousClass->next = currentClass->next;
            printf("INFO: Da xoa lop: %s - %s\n", currentClass->classId, currentClass->className);
            free(currentClass);
            return 1;
        }
        previousClass = currentClass;
        currentClass = currentClass->next;
    }
    printf("INFO: Khong tim thay lop co Ma Lop '%s' de xoa.\n", classId);
    return 0; // Không tìm thấy lớp
}

void freeClassList(Class** LinkedListClass) {
    Class *current = *LinkedListClass;
    Class *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *LinkedListClass = NULL;
}


Class inputClassData(Teacher* LinkedListTeacher, Class* LinkedListClass) {
    Class newClassData;
    char buffer[256]; 
    int tempMaxSize;
    bool validInput;

    // Khởi tạo classId rỗng để nhận biết nếu người dùng hủy
    newClassData.classId[0] = '\0';

    printf("\n--- NHAP THONG TIN LOP HOC MOI ---\n");
    printf("(Nhap 'huy' vao Ma Lop de huy bo thao tac)\n");

    // 1. Nhập Mã Lớp (classId)
    do {
        validInput = false;
        printf("Nhap Ma Lop (vd: L01, hoac 'huy' de huy): ");
        fgets(newClassData.classId, sizeof(newClassData.classId), stdin);
        newClassData.classId[strcspn(newClassData.classId, "\n")] = 0;

        if (strcmp(newClassData.classId, "huy") == 0) {
            printf("Da huy bo them lop hoc.\n");
            newClassData.classId[0] = '\0'; // Đảm bảo ID rỗng
            return newClassData;
        }

        if (strlen(newClassData.classId) == 0) {
            printf("Ma Lop khong duoc de trong. Vui long nhap lai.\n");
        } else if (findClassById(LinkedListClass, newClassData.classId) != NULL) {
            printf("LOI: Ma Lop '%s' da ton tai. Vui long nhap ma khac.\n", newClassData.classId);
        } else {
            validInput = true;
        }
    } while (!validInput);

    // 2. Nhập Tên Lớp (className)
    do {
        printf("Nhap Ten Lop: ");
        fgets(newClassData.className, sizeof(newClassData.className), stdin);
        newClassData.className[strcspn(newClassData.className, "\n")] = 0;
        if (strlen(newClassData.className) == 0) {
            printf("Ten Lop khong duoc de trong. Vui long nhap lai.\n");
        }
    } while (strlen(newClassData.className) == 0);

    // 3. Nhập Sĩ Số Tối Đa (maxSize)
    do {
        validInput = false;
        printf("Nhap Si So Toi Da cho lop: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        // Cố gắng chuyển đổi sang số
        if (sscanf(buffer, "%d", &tempMaxSize) == 1 && tempMaxSize > 0) {
            newClassData.maxSize = tempMaxSize;
            validInput = true;
        } else {
            printf("Si So Toi Da khong hop le. Vui long nhap mot so nguyen duong.\n");
        }
    } while (!validInput);

    // 4. Nhập Mã Giáo Viên Chủ Nhiệm (maGVCN)
    if (LinkedListTeacher == NULL) {
        printf("CANH BAO: Khong co danh sach giao vien de kiem tra Ma GVCN.\n");
        printf("Nhap Ma GVCN (se khong duoc kiem tra tinh hop le): ");
        fgets(newClassData.maGVCN, sizeof(newClassData.maGVCN), stdin);
        newClassData.maGVCN[strcspn(newClassData.maGVCN, "\n")] = 0;
        if (strlen(newClassData.maGVCN) == 0) { // Nếu không bắt buộc GVCN thì có thể bỏ trống
            printf("Ma GVCN duoc de trong.\n"); // Hoặc báo lỗi nếu bắt buộc
        }
    } else {
        do {
            validInput = false;
            printf("Nhap Ma GVCN (de trong neu khong co): ");
            fgets(newClassData.maGVCN, sizeof(newClassData.maGVCN), stdin);
            newClassData.maGVCN[strcspn(newClassData.maGVCN, "\n")] = 0;

            if (strlen(newClassData.maGVCN) == 0) {
                printf("Lop khong co GVCN.\n"); // Cho phép không có GVCN
                validInput = true;
            } else if (findTeacherById(LinkedListTeacher, newClassData.maGVCN) != NULL) { // Gọi hàm từ module Teacher
                validInput = true;
            } else {
                printf("LOI: Ma GVCN '%s' khong ton tai. Vui long nhap lai hoac de trong.\n", newClassData.maGVCN);
                // Có thể hiển thị danh sách GV hợp lệ ở đây (displayTeacherList(dsGiaoVien))
            }
        } while (!validInput);
    }

    // Sĩ số hiện tại của lớp mới luôn là 0
    newClassData.currentSize = 0;
    // newClassData.next sẽ được xử lý bởi hàm addClassToList

    printf("Da hoan tat nhap thong tin cho lop hoc.\n");
    return newClassData;
}


void addNewClass(Class **LinkedListClass, Teacher *LinkedListTeacher) {
    printf("\n--- THEM LOP HOC MOI ---\n");

    // 1. Gọi hàm inputClassData để lấy thông tin từ người dùng.
    //    Hàm inputClassData cũng nên kiểm tra trùng classId bên trong nó
    //    (bằng cách nhận *p_dsClass làm tham số) để tránh việc người dùng
    //    nhập nhiều lần nếu bị trùng.
    Class classDataFromUser = inputClassData(LinkedListTeacher, *LinkedListClass); // Truyền *p_dsClass (Class*)

    // 2. Kiểm tra xem người dùng có hủy bỏ thao tác không
    if (strlen(classDataFromUser.classId) == 0) {
        // inputClassData đã in thông báo hủy rồi.
        pauseScreen(NULL);
        return;
    }

    // 3. Kiểm tra trùng Mã Lớp một lần nữa (phòng trường hợp inputClassData không kiểm tra,
    //    hoặc để đảm bảo an toàn hơn). Nếu inputClassData đã kiểm tra kỹ, bước này có thể bỏ.
    if (findClassById(*LinkedListClass, classDataFromUser.classId) != NULL) {
        printf("LOI: Ma Lop '%s' da ton tai trong he thong. Thao tac them that bai.\n", classDataFromUser.classId);
        pauseScreen(NULL);
        return;
    }

    // 4. Tạo node lớp mới
    Class *newNode = createClassNode(classDataFromUser.classId,
                                     classDataFromUser.className,
                                     classDataFromUser.maxSize,
                                     classDataFromUser.maGVCN);

    if (newNode == NULL) {
        fprintf(stderr, "LOI: Khong the cap phat bo nho de tao lop hoc moi!\n");
        pauseScreen(NULL);
        return;
    }

    // 5. Thêm node lớp mới vào danh sách
    addClassToList(LinkedListClass, newNode);

    printf("=> Da them lop hoc moi '%s' (Ma Lop: %s) thanh cong!\n",
           newNode->className, newNode->classId);
    printf("   Si so toi da: %d, GVCN: %s\n", newNode->maxSize, (strlen(newNode->maGVCN) > 0 ? newNode->maGVCN : "Chua co"));

    pauseScreen(NULL);
}

// --- Hàm hiển thị chi tiết và học sinh trong lớp ---
void displayClassDetailsAndStudents(Class* targetClass, Student* LinkedList) {
    if (targetClass == NULL) {
        printf("Lop hoc khong ton tai de hien thi chi tiet.\n");
        return;
    }

    printf("\n--- THONG TIN CHI TIET LOP HOC ---\n");
    printf("Ma Lop        : %s\n", targetClass->classId);
    printf("Ten Lop       : %s\n", targetClass->className);
    printf("GVCN          : %s\n", targetClass->maGVCN);
    printf("Si So Hien Tai: %d\n", targetClass->currentSize);
    printf("Si So Toi Da  : %d\n", targetClass->maxSize);
    printf("------------------------------------\n");

    printf("\n--- DANH SACH HOC SINH TRONG LOP %s ---\n", targetClass->className);
    if (LinkedList == NULL && targetClass->currentSize > 0) {
         printf("Luu y: Danh sach hoc sinh toan cuc rong, khong the liet ke hoc sinh cua lop.\n");
    } else if (targetClass->currentSize == 0) {
        printf("Lop hien chua co hoc sinh nao.\n");
    } else {
        Student *currentStudent = LinkedList;
        int count = 0;
        printf("%-5s %-10s %-25s\n", "STT", "Ma HS", "Ho Ten");
        printf("----------------------------------------------\n");
        while (currentStudent != NULL) {
            // Dùng đúng tên trường mã lớp trong struct Student của Dũng
            if (strcmp(currentStudent->ID_Class, targetClass->classId) == 0) {
                count++;
                // Dùng đúng tên các trường của struct Student
                printf("%-5d %-10s %-25s\n", count, currentStudent->ID_Student, currentStudent->Name);
            }
            currentStudent = currentStudent->next;
        }
        if (count == 0 && targetClass->currentSize > 0) {
            // Điều này có thể xảy ra nếu currentSize của lớp không khớp với số HS thực tế có mã lớp đó
             printf("Khong tim thay hoc sinh nao thuoc lop nay trong danh sach hoc sinh toan cuc (Co the du lieu chua dong bo).\n");
        } else if (count == 0) {
             printf("Lop khong co hoc sinh nao.\n");
        }
        printf("----------------------------------------------\n");
        printf("Tong so hoc sinh trong lop (theo danh sach toan cuc): %d\n", count);
    }
    printf("------------------------------------\n");
}


// --- Các hàm cập nhật sĩ số ---
bool incrementClassSize(Class* targetClass) {
    if (targetClass == NULL) {
        fprintf(stderr, "LOI (incrementClassSize): Lop hoc la NULL.\n");
        return false;
    }
    if (targetClass->currentSize < targetClass->maxSize) {
        targetClass->currentSize++;
        return true;
    } else {
        printf("THONG BAO: Lop '%s' da day, khong the them hoc sinh.\n", targetClass->className);
        return false; // Lớp đã đầy
    }
}

void decrementClassSize(Class* targetClass) {
    if (targetClass == NULL) {
        fprintf(stderr, "LOI (decrementClassSize): Lop hoc la NULL.\n");
        return;
    }
    if (targetClass->currentSize > 0) {
        targetClass->currentSize--;
    } else {
        printf("CANH BAO (decrementClassSize): Si so lop '%s' da la 0.\n", targetClass->className);
    }
}

void saveClassesToFile(Class* LinkedListClass, const char* filename) {
    FILE *file_ptr = fopen(filename, "wb");
    if (file_ptr == NULL) {
        fprintf(stderr, "LOI (saveClassesToFile): Khong the mo file '%s' de ghi.\n", filename);
        perror("Nguyen nhan");
        return;
    }
    printf("Dang luu danh sach lop hoc vao file '%s'...\n", filename);

    Class *current = LinkedListClass;
    int count = 0;
    while (current != NULL) {
        // Tạo bản sao của node hiện tại, nhưng bỏ con trỏ next
        Class tempClass = *current;
        tempClass.next = NULL;
        if (fwrite(&tempClass, sizeof(Class), 1, file_ptr) != 1) {
            fprintf(stderr, "LOI (saveClassesToFile): Khong the ghi du lieu lop '%s' vao file.\n", current->classId);
            break;
        }
        count++;
        current = current->next;
    }

    if (fclose(file_ptr) == EOF) {
        fprintf(stderr, "LOI (saveClassesToFile): Khong the dong file '%s' sau khi ghi.\n", filename);
        perror("Nguyen nhan");
    } else if (current == NULL && count > 0) {
        printf("Da luu %d lop hoc vao file '%s' thanh cong.\n", count, filename);
    } else if (count == 0) {
        printf("Danh sach lop hoc rong, khong luu gi vao file '%s'.\n", filename);
    }
}

Class* loadClassesFromFile(const char* filename) {
    FILE *file_ptr = fopen(filename, "rb");
    Class *dsLoadedHead = NULL;
    Class tempClassData;

    if (file_ptr == NULL) {
        fprintf(stderr, "LOI (loadClassesFromFile): Khong the mo file '%s' de doc.\n", filename);
        perror("Nguyen nhan");
        return NULL;
    }
    printf("Dang tai danh sach lop hoc tu file '%s'...\n", filename);

    int count = 0;
    while (fread(&tempClassData, sizeof(Class), 1, file_ptr) == 1) {
        // Đảm bảo con trỏ next của tempClassData là NULL trước khi tạo node
        tempClassData.next = NULL;
        Class *newNode = createClassNode(tempClassData.classId,
                                         tempClassData.className,
                                         tempClassData.maxSize,
                                         tempClassData.maGVCN);
        if (newNode == NULL) {
            fprintf(stderr, "LOI (loadClassesFromFile): Khong the cap phat bo nho cho node khi tai tu file.\n");
            continue;
        }
        addClassToList(&dsLoadedHead, newNode);
        count++;
    }

    if (ferror(file_ptr)) {
        fprintf(stderr, "LOI (loadClassesFromFile): Co loi xay ra khi doc du lieu tu file '%s'.\n", filename);
        perror("Nguyen nhan");
        freeClassList(&dsLoadedHead);
        dsLoadedHead = NULL;
    }

    if (fclose(file_ptr) == EOF) {
        fprintf(stderr, "LOI (loadClassesFromFile): Khong the dong file '%s' sau khi tai.\n", filename);
        perror("Nguyen nhan");
    }

    if (dsLoadedHead != NULL && !ferror(file_ptr)) {
        printf("Da tai %d lop hoc tu file '%s' thanh cong.\n", count, filename);
    } else if (!ferror(file_ptr) && count == 0) {
        printf("File '%s' rong hoac khong chua du lieu lop hoc hop le.\n", filename);
    }
    return dsLoadedHead;
}

// --- (Sau này) Các hàm nhập liệu và cập nhật cho Class ---
// Class inputClassData(/* GiaoVien* dsGiaoVien */) { ... }
// int updateClassInfoById(Class* LinkedListClass, const char* classId /*, dsGiaoVien */) { ... }