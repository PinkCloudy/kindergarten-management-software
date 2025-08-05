#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include "define.h"
#include "class.h"


typedef struct Student  {
    char ID_Student[MAX_ID];
    char Name[MAX_NAME];
    char Date[MAX_DATE];
    char Gender[10];
    char NameParent[MAX_NAME];
    char PhoneParent[MAX_PHONE];
    char Address[MAX_ADDRESS];
    char ID_Class[MAX_ID];
    struct Student *next;
}   Student;

Student* createStudentNode(Student dataStudent);  
void addStudentToList(Student **LinkedListStudent, Student *newNode);
void displayStudentList(Student *LinkedList);
void displayStudentDetails(Student *student);
int findStudent(Student *LinkedList, const char* nameQuery);
Student* findStudentById(Student *LinkedList, const char* ID);
int editStudentById(Student **LinkedList, const char *ID, Class *LinkedListClass);
int deleteStudentByID(Student **LinkedList, const char* ID, Class *LinkedListClass); 
Student inputStudentData(Class* LinkedListClass);
void addNewStudent(Student **LinkedList, Class* LinkedListClass);
void freeStudentList(Student **LinkedList);
void saveStudentsToFile(Student *LinkedList, const char* filename);
Student* loadStudentsFromFile(const char* filename); 
#endif 
