#ifndef TEACHER_H
#define TEACHER_H

#include <stdio.h>
#include "define.h"
#include "class.h"

typedef struct Teacher {
    char ID_Teacher[MAX_ID];
    char Name[MAX_NAME];
    char DateOfBirth[MAX_DATE];
    char Gender[10];
    char Address[MAX_ADDRESS];
    char PhoneNumber[MAX_PHONE];
    char DateJoined[MAX_DATE];
    char ID_Class_Assigned[MAX_ID];
    struct Teacher *next;
} Teacher;

// Function Prototypes
Teacher* createTeacherNode(Teacher dataTeacher);
void addTeacherToList(Teacher **LinkedListTeacher, Teacher *newNode);
void displayTeacherList(Teacher *LinkedListTeacher);
void displayTeacherDetails(Teacher *teacher);
int findTeacher(Teacher *LinkedListTeacher, const char* nameQuery);
Teacher* findTeacherById(Teacher *LinkedListTeacher, const char* ID);
int editTeacherById(Teacher **LinkedListTeacher, const char *ID, Class *LinkedListClass);
int deleteTeacherByID(Teacher **LinkedListTeacher, const char* ID, Class *LinkedListClass);
Teacher inputTeacherData(Class *LinkedListClass);
void addNewTeacher(Teacher **LinkedListTeacher, Class *LinkedListClass);
void freeTeacherList(Teacher **LinkedListTeacher);
void saveTeachersToFile(Teacher *LinkedListTeacher, const char* filename);
Teacher* loadTeachersFromFile(const char* filename);

#endif 