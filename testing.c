#include "testing.h"

#define my_assert(x) if (!(x)) return 1;

int my_unit_test() {
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
		my_assert(lesson.dayOfWeek == MONDAY);
		my_assert(strcmp(getDayOfWeek(lesson.dayOfWeek), "Понедельник") == 0);
		my_assert(startTimeHours == lesson.startTime / 60);
		my_assert(startTimeMinutes == lesson.startTime % 60);
		my_assert(lesson.type == LECTION);
		my_assert(strcmp(getLessonType(&lesson), "Лекция") == 0);
		my_assert(strcmp(lesson.subject, "C Programming") == 0);
		my_assert(strcmp(lesson.teacher, "Ivanov") == 0);
		my_assert(strcmp(lesson.audienceCipher, "501A") == 0);
		my_assert(lesson.courseNumber == 2);
		my_assert(lesson.groupNumber == 3);
	}
	{
		Lesson lesson;
		lesson.dayOfWeek = 0;
		my_assert(strcmp(getDayOfWeek(lesson.dayOfWeek), "unknown") == 0);
	}
	return 0;
}

int test_sorting(Lesson *lessons, unsigned int count) {
	if (count) {
		Lesson *last = &lessons[0];
		for (unsigned int i = 0; i < count; i++) {
			if (last->dayOfWeek > lessons[i].dayOfWeek || last->startTime > lessons[i].startTime) {
				return 0;
			}
			last = &lessons[i];
		}
	}
	return 1;
}
