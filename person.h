#ifndef PERSON_H
#define PERSON_H

#include "modules/uuid.h"

static const int MAX_NAME = 200;

typedef struct Person {
	char id[L_UUID];
	char name[MAX_NAME];
	unsigned int age;
} Person;

void printPerson(const Person * p);
void listPersons(const Person * persons, int lengthPersons);
void addPerson(Person ** persons, int *lengthPersons, int *capacityPersons);
void updatePerson(Person * persons, int lengthPersons);
void deletePerson(Person * persons, int *lengthPersons, int index);

#endif
