#include <string.h>
#include "lesson.h"

char *getDayOfWeek(unsigned int d) {
	switch (d) {
		case MONDAY:
			return "Понедельник";
		case TUESDAY:
			return "Вторник";
		case WEDNESDAY:
			return "Среда";
		case THURSDAY:
			return "Четверг";
		case FRIDAY:
			return "Пятница";
		case SATURDAY:
			return "Суббота";
		case SUNDAY:
			return "Воскресенье";
		default:
			return "unknown";
	}
}

char *getLessonType(Lesson *lesson) {
	return lesson->type == LECTION ? "Лекция" : "Семинар";
}

int compareLessons(const void *x, const void *y) {
	Lesson *lesson1 = (Lesson *) x, *lesson2 = (Lesson *) y;
	if (lesson1->dayOfWeek != lesson2->dayOfWeek) {
		return lesson1->dayOfWeek - lesson2->dayOfWeek;
	} else if (lesson1->startTime / 60 != lesson2->startTime / 60) {
		return lesson1->startTime / 60 - lesson2->startTime / 60;
	} else {
		return lesson1->startTime % 60 - lesson2->startTime % 60;
	}
}

void unitTest() {
	{
		unsigned int startTimeHours = 12, startTimeMinutes = 30;
		Lesson lesson;
		lesson.dayOfWeek = MONDAY;
		lesson.startTime = startTimeHours * 60 + startTimeMinutes;
		lesson.type = LECTION;
		lesson.subject = "C Programming";
		lesson.teacher = "Ivanov";
		lesson.audienceCipher = "501A";
		lesson.courseNumber = 2;
		lesson.groupNumber = 3;
		assert(lesson.dayOfWeek == MONDAY);
		assert(strcmp(getDayOfWeek(lesson.dayOfWeek), "Понедельник") == 0);
		assert(startTimeHours == lesson.startTime / 60);
		assert(startTimeMinutes == lesson.startTime % 60);
		assert(lesson.type == LECTION);
		assert(strcmp(getLessonType(&lesson), "Лекция") == 0);
		assert(strcmp(lesson.subject, "C Programming") == 0);
		assert(strcmp(lesson.teacher, "Ivanov") == 0);
		assert(strcmp(lesson.audienceCipher, "501A") == 0);
		assert(lesson.courseNumber == 2);
		assert(lesson.groupNumber == 3);
	}
	{
		Lesson lesson;
		lesson.dayOfWeek = 0;
		assert(strcmp(getDayOfWeek(lesson.dayOfWeek), "unknown") == 0);
	}
	printf("Unit test OK\n");
}

void logicTest() {

}