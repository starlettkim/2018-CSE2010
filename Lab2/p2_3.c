#include <stdio.h>
#include <stdlib.h>

const int MAX_LEN_NAME	= 100;

int main(int argc, char **argv) {
	
	if (argc != 2) {
		printf("Error\n");
		return 1;
	}
	
	int num_of_names = atoi(argv[1]);
	char **names = (char**)malloc(num_of_names * sizeof(char*));
	int i;
	for (i = 0; i < num_of_names; i++) {
		names[i] = (char*)malloc(MAX_LEN_NAME * sizeof(char));
	}

	printf("Enter %d names: ", num_of_names);
	for (i = 0; i < num_of_names; i++) {
		scanf("%s", names[i]);
	}

	printf("The names you entered:\n");
	for (i = 0; i < num_of_names; i++) {
		printf("%s\n", names[i]);
	}
	
	return 0;
}
