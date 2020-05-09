#ifndef TECHNOPARK_C_IZ1_TIMETABLE_H
#define TECHNOPARK_C_IZ1_TIMETABLE_H

#include "lesson.h"

void foo();
void input(unsigned int*, unsigned int*, unsigned int*);
void read_lessons(Lesson *lessons, unsigned int count);
void delete_lessons(Lesson *lessons, unsigned int count);
void sort_lessons(Lesson *lessons, unsigned int count);
void print_lesson_info(Lesson *lesson);
void restore_chronology(Lesson *lessons, unsigned int count, unsigned int courseNumber, unsigned int groupNumber);

#endif //TECHNOPARK_C_IZ1_TIMETABLE_H
