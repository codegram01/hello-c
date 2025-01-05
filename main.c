#include <stdio.h>
#include <stdlib.h>
#include "person.h"

int main(void)
{
	int lengthPersons = 0;
	int capacityPersons = 10;
	Person *persons = malloc(capacityPersons * sizeof(Person));

	if (!persons) {
		perror("Failed to allocate memory");
		return EXIT_FAILURE;
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
			printf("Enter index to delete: ");
			int index;
			scanf("%d", &index);
			deletePerson(persons, &lengthPersons, index);
			break;
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
