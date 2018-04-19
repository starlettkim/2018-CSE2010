#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct HeapStruct {
	int capacity;
	int size;
	ElementType *elements;
} Heap;

Heap *createHeap(int heap_size) {

}

void insert(Heap *heap, int value) {

}

int find(Heap *heap, int value) {

}

int main(int argc, char **argv) {
	FILE *ifp = fopen(argv[1], "r");
	char cmd;
	Heap *max_heap;
	while (fscanf(ifp, "%c", &cmd) != EOF) {
		switch (cmd) {
		case 'n':
			int heap_size;
			fscanf(ifp,	"%d", &heap_size);
			max_heap = createHeap(heap_size);
			break;
		case 'i':
			int key;
			fscanf(ifp, "%d", &key);
			insert(max_heap, key);
			break;
		case 'f':
			int key;
			fscanf(ifp, "%d", &key);
			if (find(max_heap, key)) {
				printf("%d is in the tree.\n", key);
			} else {
				printf("%d is not int the tree.\n", key);
			}
			break;
		}
	}
	return 0;
}
