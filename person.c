#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/uuid.h"
#include "person.h"

void printPerson(const Person *p)
{
	printf("Person:\n"
	       "- id   : %s\n"
	       "- name : %s\n" "- age  : %d\n", p->id, p->name, p->age);
}

void listPersons(const Person *persons, int lengthPersons)
{
	if (lengthPersons == 0) {
		printf("No persons to display.\n");
		return;
	}

	for (int i = 0; i < lengthPersons; i++) {
		printf("[%d] ", i);
		printPerson(&persons[i]);
	}
}

void addPerson(Person **persons, int *lengthPersons, int *capacityPersons)
{
	if (*lengthPersons >= *capacityPersons) {
		*capacityPersons *= 2;
		*persons = realloc(*persons, *capacityPersons * sizeof(Person));
		if (!*persons) {
			perror("Failed to allocate memory");
			exit(EXIT_FAILURE);
		}
	}

	char name[MAX_NAME];
	int age;

	printf("Enter name: ");
	scanf("%s", name);

	printf("Enter age: ");
	scanf("%d", &age);

	int index = *lengthPersons;

	generate_uuid((*persons)[index].id);
	strcpy((*persons)[index].name, name);
	(*persons)[index].age = age;

	printf("Added ");
	printPerson(&(*persons)[index]);
	(*lengthPersons)++;
}

void updatePerson(Person *persons, int lengthPersons)
{
	printf("Enter index to update: ");
	int index;
	scanf("%d", &index);

	if (index < 0 || index >= lengthPersons) {
		printf("Invalid index. Cannot update person.\n");
		return;
	}

	char name[MAX_NAME];
	int age;

	printf("Enter new name: ");
	scanf("%s", name);

	printf("Enter new age: ");
	scanf("%d", &age);

	strcpy(persons[index].name, name);
	persons[index].age = age;

	printf("Updated ");
	printPerson(&persons[index]);
}

void deletePerson(Person *persons, int *lengthPersons, int index)
{
	if (index < 0 || index >= *lengthPersons) {
		printf("Invalid index. Cannot delete person.\n");
		return;
	}

	for (int i = index; i < *lengthPersons - 1; i++) {
		persons[i] = persons[i + 1];
	}

	(*lengthPersons)--;
	printf("Person at index %d deleted successfully.\n", index);
}
