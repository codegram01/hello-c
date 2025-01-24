#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

typedef int Person;

typedef struct Line
{
	int length;
	Person *persons;
} Line;

int addPerson(Line *line, Person p)
{
	(line->length)++;
	line->persons = realloc(line->persons, sizeof(Person) * line->length);
	if(line->persons == NULL) {
		return -1;
	}

	(line->persons)[line->length - 1] = p;

	return line->length;
}

int addPersons(Line *line, int lengthPerson, ...)
{
	va_list persons;
	va_start (persons, lengthPerson);
	for(int i = 0; i < lengthPerson; i++) {
		Person p = va_arg(persons, Person);
		if(addPerson(line, p) == -1) {
			return -1;
		}
	}
	return 0;
}

void logLine(Line *line)
{
	printf("Length: %d, Person:\n", line->length);

	for(int i = 0; i < line->length; i++) {
		printf("- %d ", (line->persons)[i]);
	}
	printf("\n");
}

void removeLine(Line *line)
{
	free(line->persons);
	free(line);
}

int main(void)
{
	int lengthLine = 3;
	Line *lines[] = {
		malloc(sizeof(Line)),
		malloc(sizeof(Line)),
		malloc(sizeof(Line))
	};

	lines[0]->length = 0;
	lines[0]->persons = NULL;
	lines[1]->length = 0;
	lines[1]->persons = NULL;
	lines[2]->length = 0;
	lines[2]->persons = NULL;

	if(addPersons(lines[0], 3, 111, 222, 333) == -1) {
		perror("Can't add persons");
	}

	if(addPersons(lines[1], 3, 444, 55, 777) == -1) {
		perror("Can't add persons");
	}

	if(addPersons(lines[2], 2, 555, 6666) == -1) {
		perror("Can't add persons");
	}

	for(int i = 0; i < lengthLine; i++) {
		printf("---> Line[%d]\n", i);
		logLine(lines[i]);
	}

	Line *minLine = lines[0];
	for(int i = 1; i < lengthLine; i++) {
		if(lines[i]->length < minLine->length) {
			minLine = lines[i];
		}
	}

	printf("-----------\nMin line:\n");
	logLine(minLine);

	for(int i = 0; i < lengthLine; i++) {
		removeLine(lines[i]);
	}

	return 0;
}
