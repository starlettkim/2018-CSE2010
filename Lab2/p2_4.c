#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Error\n");
		return -1;
	}
	
	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);

	printf("Is %d zero? : %s\n", num1, (num1 ? "False" : "True"));
	printf("Is %d zero? : %s\n", num2, (num2 ? "False" : "True"));
	
	printf("Does %d equal to %d? : %s\n", num1, num2, (num1 == num2 ? "True" : "False"));
	
	printf("The next number of %d is %d\n", num1, (num1 == INT_MAX ? num1 : num1 + 1));
	printf("The next number of %d is %d\n", num2, (num2 == INT_MAX ? num2 : num2 + 1));
	
	printf("%d + %d = %d\n", num1, num2, (INT_MAX - num1 >= num2 ? num1 + num2 : INT_MAX));
	printf("%d - %d = %d\n", num1, num2, (num1 > num2 ? num1 - num2 : 0));

	return 0;
}
