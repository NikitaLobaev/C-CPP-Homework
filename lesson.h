#ifndef IZ1_LESSON_H
#define IZ1_LESSON_H

#include <assert.h>
#include <stdio.h>
#include <string.h>

enum {
	MONDAY = 1u, TUESDAY = 2u, WEDNESDAY = 3u, THURSDAY = 4u, FRIDAY = 5u, SATURDAY = 6u, SUNDAY = 7u
};

enum {
	LECTION = 0u, SEMINAR = 1u
};

typedef struct {
	unsigned int dayOfWeek: 3,
			startTime: 11,
			type: 1,
			length: 11,
			courseNumber: 3,
			groupNumber: 3;
	char *subject, *teacher, *audienceCipher;
} Lesson;

char *getDayOfWeek(unsigned int);

char *getLessonType(Lesson *);

int compareLessons(const void *, const void *);

void logicTest();

#endif
