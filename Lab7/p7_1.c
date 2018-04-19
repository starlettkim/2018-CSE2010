#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct HeapStruct {
	int capacity;
	int size;
	ElementType *elements;
} Heap;

void swap(ElementType *lhs, ElementType *rhs) {
	ElementType tmp;
	tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
}

Heap *createHeap(int heap_size) {
	Heap *new_heap = (Heap*)calloc(1, sizeof(Heap));
	new_heap->capacity = heap_size;
	new_heap->size = 0;
	new_heap->elements = (ElementType*)calloc(heap_size + 1, sizeof(ElementType));
	return new_heap;
}

void insert(Heap *heap, int value) {
	if (heap->size >= heap->capacity) {
		fprintf(stderr, "Insertion error: heap is full.\n");
		return;
	}
	if (find(heap, value)) {
		fprintf(stderr, "Insertion error: %d is already in the heap.\n", value);
		return;
	}
	int i;
	for (i = ++heap->size; i > 1 && heap->elements[i / 2] < value; i /= 2) {
		heap->elements[i] = heap->elements[i / 2];
	}
	heap->elements[i] = value;
	printf("%d inserted.\n", value);
}

int find(Heap *heap, int value) {
	int i;
	for (i = 1; i <= heap->size; i++) {
		if (heap->elements[i] == value) {
			return 1;
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	FILE *ifp = fopen(argv[1], "r");
	char cmd;
	int heap_size, key;
	Heap *max_heap;
	while (fscanf(ifp, "%c", &cmd) != EOF) {
		switch (cmd) {
		case 'n':
			fscanf(ifp,	"%d", &heap_size);
			max_heap = createHeap(heap_size);
			break;
		case 'i':
			fscanf(ifp, "%d", &key);
			insert(max_heap, key);
			break;
		case 'f':
			fscanf(ifp, "%d", &key);
			if (find(max_heap, key)) {
				printf("%d is in the heap.\n", key);
			} else {
				printf("%d is not in the heap.\n", key);
			}
			break;
		}
	}
	return 0;
}
