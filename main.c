#include <stdio.h>
#include <stdlib.h>
#include "lesson.h"

void input(unsigned int *, unsigned int *, unsigned int *);
void readLessons(Lesson *, unsigned int);
void deleteLessons(Lesson *, unsigned int);
void sortLessons(Lesson *, unsigned int);
void printLessonInfo(Lesson *);
void restoreChronology(Lesson *, unsigned int, unsigned int, unsigned int);

int main(int argc, char **argv) {
	unsigned int count, courseNumber, groupNumber;
	input(&count, &courseNumber, &groupNumber);
	Lesson *lessons = (Lesson *) malloc(count * sizeof(Lesson));
	readLessons(lessons, count);
	sortLessons(lessons, count);
	restoreChronology(lessons, count, courseNumber, groupNumber); //здесь выводится расписание в хронологическом порядке
	deleteLessons(lessons, count);
	free(lessons); //т.к. malloc в ф-ции main, то и free тоже в ф-ции main, а не в ф-ции deleteLessons
	return 0;
}

void input(unsigned int *count, unsigned int *courseNumber, unsigned int *groupNumber) {
	printf("Количество занятий: ");
	scanf("%u", count);
	printf("Курс: ");
	scanf("%u", courseNumber);
	printf("Группа: ");
	scanf("%u", groupNumber);
}

void readLessons(Lesson *lessons, unsigned int count) {
	printf("Вводите данные через пробел в формате: день_недели время_начала вид продолжительность дисциплина "
		   "преподаватель аудитория курс группа\nгде день_недели - номер дня недели (от 1 до 7),\n"
		   "\tвремя_начала - например, 8:30 (через двоеточие),\n"
		   "\tвид - лекция 0; семинар 1,\n"
		   "\tпродолжительность - время в минутах,\n"
		   "\tаудитория - шифр аудитории (строка),\n"
		   "\tкурс - номер курса (цифра),\n"
		   "\tгруппа - номер группы (цифра)\n");
	for (unsigned int i = 0; i < count; i++) {
		unsigned int dayOfWeek, startTimeHours, startTimeMinutes, type, length, courseNumber, groupNumber;
		lessons[i].subject = (char *) malloc(100 * sizeof(char));
		lessons[i].teacher = (char *) malloc(100 * sizeof(char));
		lessons[i].audienceCipher = (char *) malloc(100 * sizeof(char));
		if (lessons[i].subject == NULL || lessons[i].teacher == NULL || lessons[i].audienceCipher == NULL) {
		
		}
		scanf("%u %u:%u %u %u %s %s %s %u %u", &dayOfWeek, &startTimeHours, &startTimeMinutes, &type, &length,
			  lessons[i].subject, lessons[i].teacher, lessons[i].audienceCipher, &courseNumber, &groupNumber);
		lessons[i].dayOfWeek = dayOfWeek;
		lessons[i].startTime = startTimeHours * 60 + startTimeMinutes;
		lessons[i].type = type;
		lessons[i].length = length;
		lessons[i].courseNumber = courseNumber;
		lessons[i].groupNumber = groupNumber;
	}
}

void deleteLessons(Lesson *lessons, unsigned int count) {
	while (count--) {
		free(lessons[count].subject);
		free(lessons[count].teacher);
		free(lessons[count].audienceCipher);
	}
}

void sortLessons(Lesson *lessons, unsigned int count) {
	qsort(lessons, count, sizeof(Lesson), &compareLessons);
}

void printLessonInfo(Lesson *lesson) {
	printf("---Занятие---\nДень недели: %s\nВремя начала: %u:%u\nВид: %s\nДлительность: %u\nПредмет: %s\n"
		   "Преподаватель: %s\nШифр аудитории: %s\nКурс: %u\nГруппа: %u\n\n", getDayOfWeek(lesson->dayOfWeek),
		   lesson->startTime / 60, lesson->startTime % 60, getLessonType(lesson), lesson->length, lesson->subject,
		   lesson->teacher, lesson->audienceCipher, lesson->courseNumber, lesson->groupNumber);
}

void restoreChronology(Lesson *lessons, unsigned int count, unsigned int courseNumber, unsigned int groupNumber) {
	printf("Хронология посещений занятий курса %u группы %u:\n", courseNumber, groupNumber);
	Lesson *last = NULL;
	for (unsigned i = 0; i < count; i++) {
		if (lessons[i].courseNumber != courseNumber || lessons[i].groupNumber != groupNumber) {
			continue;
		}
		if (last == NULL || last->dayOfWeek != lessons[i].dayOfWeek ||
			last->startTime + last->length < lessons[i].startTime) {
			last = &lessons[i];
			printLessonInfo(last);
		}
	}
}
