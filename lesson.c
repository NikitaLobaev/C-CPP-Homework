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

int compareLessons(const void *lesson1_, const void *lesson2_) {
	Lesson *lesson1 = (Lesson *) lesson1_, *lesson2 = (Lesson *) lesson2_;
	if (lesson1->dayOfWeek != lesson2->dayOfWeek) {
		return lesson1->dayOfWeek - lesson2->dayOfWeek;
	} else if (lesson1->startTime / 60 != lesson2->startTime / 60) {
		return lesson1->startTime / 60 - lesson2->startTime / 60;
	} else {
		return lesson1->startTime % 60 - lesson2->startTime % 60;
	}
}
