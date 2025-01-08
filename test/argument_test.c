#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	int opt;

	// Define the long options
	static struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"output", required_argument, 0, 'o'},
		{"verbose", no_argument, 0, 'v'},
		{"debug", optional_argument, 0, 'd'},	// d option with optional argument
		{0, 0, 0, 0}	// End of options
	};

	// Parse command line arguments
	while ((opt =
		getopt_long(argc, argv, "ho:v::d::", long_options,
			    NULL)) != -1) {
		switch (opt) {
		case 'h':
			printf("Help option is selected.\n");
			break;
		case 'o':
			printf("Output file is: %s\n", optarg);
			break;
		case 'v':
			printf("Verbose mode is enabled.\n");
			break;
		case 'd':
			if (optarg) {
				printf("Option -d is: %s\n", optarg);	// If -d has a value
			} else {
				printf("Option -d is enabled without argument.\n");	// If -d has no value
			}
			break;
		case '?':
			// If an unrecognized option is encountered
			printf("Invalid option or missing argument.\n");
			break;
		default:
			break;
		}
	}

	// Handle non-option arguments
	for (int i = optind; i < argc; i++) {
		printf("Non-option argument: %s\n", argv[i]);
	}

	return 0;
}
