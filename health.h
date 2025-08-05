#ifndef HEALTH_H
#define HEALTH_H

#include <stdio.h>
#include "define.h"
#include "student.h"

typedef struct Health {
    char ID_Health[MAX_ID];
    char ID_Student[MAX_ID];
    float Height;
    float Weight;
    char MedicalCondition[MAX_TEXT];
    char Vaccination[MAX_TEXT];
    char Notes[MAX_TEXT];
    struct Health *next;
} Health;

Health* createHealthNode(Health dataHealth);
void addHealthToList(Health **LinkedListHealth, Health *newNode);
void displayHealthList(Health *LinkedList);
void displayHealthDetails(Health *health);
int findHealth(Health *LinkedList, const char* ID_Student);
Health* findHealthById(Health *LinkedList, const char* ID);
int editHealthById(Health **LinkedList, const char *ID, Student *LinkedListStudent);
int deleteHealthById(Health **LinkedList, const char* ID, Student *LinkedListStudent);
Health inputHealthData(Student *LinkedListStudent);
void addNewHealth(Health **LinkedListHealth, Student *LinkedListStudent);
void freeHealthList(Health **LinkedList);
void saveHealthToFile(Health *LinkedList, const char* filename);
Health* loadHealthFromFile(const char* filename);

#endif