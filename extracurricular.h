#ifndef EXTRACURRICULAR_H
#define EXTRACURRICULAR_H
#include "define.h"


typedef struct {
    char activityId[MAX_ID];         
    char name[MAX_ID];   
    char date[MAX_DATE];           
    char location[MAX_ID];   
    char participants[MAX_ID]; 
} ExtracurricularInfo;

typedef struct ExtracurricularNode {
    ExtracurricularInfo data;
    struct ExtracurricularNode* next;
} ExtracurricularNode;

struct Student;

ExtracurricularNode* createExtracurricularNode(ExtracurricularInfo data);
void addExtracurricular(ExtracurricularNode** head, ExtracurricularInfo data);
void displayExtracurricular(ExtracurricularNode* head, const char* activityId, struct Student* studentList);
void updateExtracurricular(ExtracurricularNode* head, const char* activityId, struct Student* studentList);
void saveExtracurricularToFile(ExtracurricularNode* head, const char* filename);
ExtracurricularNode* loadExtracurricularFromFile(const char* filename);
void freeExtracurricularList(ExtracurricularNode** head);
void addNewExtracurricular(ExtracurricularNode** head, struct Student* studentList);

#endif