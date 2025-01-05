#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "uuid.h"

void generate_uuid(char *uuid_str)
{
	unsigned char uuid[16];
	struct timeval tv;

	// Seed the random number generator
	gettimeofday(&tv, NULL);
	srand(tv.tv_usec * tv.tv_sec);

	// Generate 16 random bytes
	for (int i = 0; i < 16; i++) {
		uuid[i] = rand() % 256;
	}

	// Set the version to 4 (random UUID)
	uuid[6] = (uuid[6] & 0x0F) | 0x40;

	// Set the variant to DCE 1.1 (RFC 4122)
	uuid[8] = (uuid[8] & 0x3F) | 0x80;

	// Convert to UUID string format
	snprintf(uuid_str, 37,
		 "%02x%02x%02x%02x-"
		 "%02x%02x-"
		 "%02x%02x-"
		 "%02x%02x-"
		 "%02x%02x%02x%02x%02x%02x",
		 uuid[0], uuid[1], uuid[2], uuid[3],
		 uuid[4], uuid[5],
		 uuid[6], uuid[7],
		 uuid[8], uuid[9],
		 uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
}
