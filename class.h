#ifndef CLASS_H
#define CLASS_H

#include "define.h" 
#include <stdio.h> 
#include <stdbool.h> 


struct Student; 
typedef struct Student Student; 

struct Teacher; 
typedef struct Teacher Teacher; 

typedef struct Class {
    char classId[MAX_ID];       
    char className[MAX_NAME];
    int maxSize;
    int currentSize;           
    char maGVCN[MAX_ID];   
    struct Class* next;
} Class;




Class* createClassNode(const char* classId, const char* className, int maxSize, const char* maGVCN); 
void addClassToList(Class** LinkedListClass, Class* newClass); 
Class* findClassById(Class* LinkedListClass, const char* classId); 
void displayClassList(Class* LinkedListClass); 
int deleteClassById(Class** LinkedListClass, const char* classId, Student* LinkedListStudent); 
void freeClassList(Class** LinkedListClass); 
Class inputClassData(Teacher* LinkedListTeacher, Class* LinkedListClass);
void addNewClass(Class **LinkedListClass, Teacher *LinkedListTeacher);
void displayClassDetailsAndStudents(Class* targetClass, Student* LinkedListStudent);
bool incrementClassSize(Class* targetClass); 
void decrementClassSize(Class* targetClass);
void saveClassesToFile(Class* LinkedListClass, const char* filename);
Class* loadClassesFromFile(const char* filename);
#endif 