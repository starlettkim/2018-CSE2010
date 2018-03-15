#include <stdio.h>
int main() {
	char buf[128];
	printf("Enter your name: ");
	fgets(buf, 128, stdin);

	printf("Your name is %s", buf);
	return 0;
}
