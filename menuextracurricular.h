#ifndef MENU_EXTRACURRICULAR_H
#define MENU_EXTRACURRICULAR_H

#include "extracurricular.h"
#include "student.h"

struct Student;
struct ExtracurricularNode;

void manageExtracurricularMenu(ExtracurricularNode** extracurricularList, struct Student* studentList);

#endif