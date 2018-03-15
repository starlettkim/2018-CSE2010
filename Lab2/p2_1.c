#include <stdio.h>

void swap(int *num1, int *num2) {
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

int main(int argc, char **argv) {
	int num1, num2;
	printf("Enter two integers: ");
	scanf("%d %d", &num1, &num2);

	swap(&num1, &num2);
	printf("Swapped: %d %d\n", num1, num2);
	return 0;
}
