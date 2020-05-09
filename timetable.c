#include <stdio.h>
#include <stdlib.h>
#include "lesson.h"
#include "timetable.h"

void foo() {
	unsigned int count, courseNumber, groupNumber;
	input(&count, &courseNumber, &groupNumber);
	Lesson *lessons = (Lesson *) malloc(count * sizeof(Lesson));
	read_lessons(lessons, count);
	sort_lessons(lessons, count);
	restore_chronology(lessons, count, courseNumber, groupNumber); //здесь выводится расписание в хронологическом порядке
	delete_lessons(lessons, count);
	free(lessons); //т.к. malloc в ф-ции main, то и free тоже в ф-ции main, а не в ф-ции deleteLessons
}

void restore_chronology(Lesson *lessons, unsigned int count, unsigned int courseNumber, unsigned int groupNumber) {
	printf("Хронология посещений занятий курса %u группы %u:\n", courseNumber, groupNumber);
	Lesson *last = NULL;
	printf("\ncount = %u\n", count);
	for (unsigned int i = 0; i < count; i++) {
		if (lessons[i].courseNumber != courseNumber || lessons[i].groupNumber != groupNumber) {
			continue;
		}
		if (last == NULL || (unsigned int) last->dayOfWeek != (unsigned int) lessons[i].dayOfWeek ||
		    (unsigned int) last->startTime + (unsigned int) last->length < (unsigned int) lessons[i].startTime) {
			last = &lessons[i];
			print_lesson_info(last);
		}
	}
}

void input(unsigned int *count, unsigned int *courseNumber, unsigned int *groupNumber) {
	printf("Количество занятий: ");
	scanf("%u", count);
	printf("Курс: ");
	scanf("%u", courseNumber);
	printf("Группа: ");
	scanf("%u", groupNumber);
}

void read_lessons(Lesson *lessons, unsigned int count) {
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
		if (lessons[i].subject == NULL) {
			printf("ОШИБКА: Не указан предмет.");
			exit(1);
		}
		if (lessons[i].teacher == NULL) {
			printf("ОШИБКА: Не указан преподаватель.");
			exit(1);
		}
		if (lessons[i].audienceCipher == NULL) {
			printf("ОШИБКА: Не указан шифр аудитории.");
			exit(1);
		}
		scanf("%u %u:%u %u %u %s %s %s %u %u", &dayOfWeek, &startTimeHours, &startTimeMinutes, &type, &length,
		      lessons[i].subject, lessons[i].teacher, lessons[i].audienceCipher, &courseNumber, &groupNumber);
		if (dayOfWeek < 1 || dayOfWeek > 7) {
			printf("ОШИБКА: Некорректно задан день недели.");
			exit(1);
		}
		if (startTimeHours >= 24) {
			printf("ОШИБКА: Некорректно указаны часы начала занятия.");
			exit(1);
		}
		if (startTimeMinutes >= 60) {
			printf("ОШИБКА: Некорректно указаны минуты начала занятия.");
			exit(1);
		}
		if (dayOfWeek < 1 || dayOfWeek > 7) {
			printf("ОШИБКА: Некорректно указан тип занятия (0 - лекция; 1 - семинар).");
			exit(1);
		}
		lessons[i].dayOfWeek = dayOfWeek;
		lessons[i].startTime = startTimeHours * 60 + startTimeMinutes;
		lessons[i].type = type;
		lessons[i].length = length;
		lessons[i].courseNumber = courseNumber;
		lessons[i].groupNumber = groupNumber;
	}
}

void delete_lessons(Lesson *lessons, unsigned int count) {
	while (count--) {
		free(lessons[count].subject);
		free(lessons[count].teacher);
		free(lessons[count].audienceCipher);
	}
}

void sort_lessons(Lesson *lessons, unsigned int count) {
	qsort(lessons, count, sizeof(Lesson), &compareLessons);
}

void print_lesson_info(Lesson *lesson) {
	printf("---Занятие---\nДень недели: %s\nВремя начала: %u:%u\nВид: %s\nДлительность: %u\nПредмет: %s\n"
	       "Преподаватель: %s\nШифр аудитории: %s\nКурс: %u\nГруппа: %u\n\n", getDayOfWeek(lesson->dayOfWeek),
	       lesson->startTime / 60u, lesson->startTime % 60u, getLessonType(lesson), (unsigned int) lesson->length,
	       lesson->subject, lesson->teacher, lesson->audienceCipher, (unsigned int) lesson->courseNumber,
	       (unsigned int) lesson->groupNumber);
}
