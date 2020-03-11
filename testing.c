#include "testing.h"

int testSorting(Lesson *lessons, unsigned int count) {
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
