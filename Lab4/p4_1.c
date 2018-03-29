#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE	= 100;

typedef struct Stack {
	int *key;
	int top;
	int max_stack_size;
} Stack;

Stack* createStack(int max) {
	Stack *s = (Stack*)malloc(sizeof(Stack));
	if (max < 0 || s == NULL) {
		return NULL;
	}
	s->key = (int*)malloc(sizeof(int) * max);
	s->max_stack_size = max;
	s->top = -1;
	return s;
}

int isFull(Stack *s) {
	if (s->top + 1 == s->max_stack_size) {
		return 1;
	}
	return 0;
}

void push(Stack *s, int value) {
	if (isFull(s)) {
		printf("Stack is full\n");
		return;
	}
	s->key[++s->top] = value;
	printf("%d inserted\n", value);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		return 1;
	}
	FILE *ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		return 1;
	}

	Stack *stack = createStack(MAX_SIZE);
	char in;
	while (fscanf(ifp, "%c", &in), in != '#') {
		push(stack, in - '0');
	}

	return 0;
}
