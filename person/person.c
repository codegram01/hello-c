#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../modules/uuid.h"
#include "person.h"

int personApp(void)
{
	int lengthPersons = 0;
	int capacityPersons = 10;
	Person *persons = malloc(capacityPersons * sizeof(Person));

	if (!persons) {
		perror("Failed to allocate memory");
		return 1;
	}

	int choice = 0;
	while (choice != 5) {
		printf("-----------------------\n"
		       "What do you want to do:\n"
		       "1. List persons\n"
		       "2. Add person\n"
		       "3. Update person\n"
		       "4. Delete person\n" "5. Quit\n" "Chose: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			listPersons(persons, lengthPersons);
			break;
		case 2:
			addPerson(&persons, &lengthPersons, &capacityPersons);
			break;
		case 3:
			updatePerson(persons, lengthPersons);
			break;
		case 4:
			{
				printf("Enter index to delete: ");
				int index;
				scanf("%d", &index);
				deletePerson(persons, &lengthPersons, index);
				break;
			}
		case 5:
			printf("Goodbye!\n");
			break;
		default:
			printf("Please choose a valid option (1-5).\n");
			break;
		}
	}

	free(persons);
	return 0;
}

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

	getchar();		// fix for after scanf

	printf("Enter name: ");
	if (fgets(name, MAX_NAME, stdin) != NULL) {
		size_t len = strlen(name);
		if (len > 0 && name[len - 1] == '\n') {
			name[len - 1] = '\0';	// Remove the trailing newline
		}
	}

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
	if (fgets(name, MAX_NAME, stdin) != NULL) {
		size_t len = strlen(name);
		if (len > 0 && name[len - 1] == '\n') {
			name[len - 1] = '\0';
		}
	}

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
