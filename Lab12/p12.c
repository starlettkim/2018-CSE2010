#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INF = (int)2e9;

typedef struct Node {
	int vertex;
	int dist;
	int prev;
} Node;

typedef struct Graph {
	int size;
	int **vertices;
	Node *nodes;
} Graph;

typedef struct Heap {
	int capacity;
	int size;
	Node *elements;
} Heap;

Graph *createGraph(int size) {
	Graph *new_graph = (Graph*)calloc(1, sizeof(Graph));
	new_graph->size = size;
	new_graph->vertices = (int**)calloc(size + 1, sizeof(int*));
	new_graph->nodes = (Node*)calloc(size + 1, sizeof(Node));
	int i;
	for (i = 1; i <= size; i++) {
		new_graph->vertices[i] = (int*)calloc(size + 1, sizeof(int));
		new_graph->nodes[i].vertex = i;
		new_graph->nodes[i].dist = INF;
		new_graph->nodes[i].prev = i;
	}
	return new_graph;
}

Heap *createMinHeap(int heap_size) {
	Heap *new_heap = (Heap*)calloc(1, sizeof(Heap));
	new_heap->capacity = heap_size;
	new_heap->size = 0;
	new_heap->elements = (Node*)calloc(heap_size + 1, sizeof(Node));
	return new_heap;
}

void insertToMinHeap(Heap *min_heap, int vertex, int distance) {
	if (min_heap->size >= min_heap->capacity) {
		return;
	}
	Node new_node;
	new_node.vertex = vertex;
	new_node.dist = distance;
	int i;
	for (i = ++min_heap->size; i > 1 && min_heap->elements[i / 2].dist > distance; i /= 2) {
		min_heap->elements[i] = min_heap->elements[i / 2];
	}
	min_heap->elements[i] = new_node;
}

Node deleteMin(Heap *min_heap) {
	Node min_element = min_heap->elements[1];
	Node last_element = min_heap->elements[min_heap->size--];
	int i, child;
	for (i = 1; i * 2 <= min_heap->size; i = child) {
		child = i * 2;
		if (child < min_heap->size && min_heap->elements[child].dist > min_heap->elements[child + 1].dist) {
			child++;
		}
		if (last_element.dist > min_heap->elements[child].dist) {
			min_heap->elements[i] = min_heap->elements[child];
		} else break;
	}
	min_heap->elements[i] = last_element;
	return min_element;
}

void printShortestPath(Graph *graph) {
	Heap *min_heap = createMinHeap(graph->size * graph->size);
	insertToMinHeap(min_heap, 1, 0);
	graph->nodes[1].dist = 0;
	while (min_heap->size != 0) {
		Node now = deleteMin(min_heap);
		int i;
		for (i = 1; i <= graph->size; i++) {
			if (graph->vertices[now.vertex][i] > 0 &&
					graph->nodes[i].dist > now.dist + graph->vertices[now.vertex][i]) {
				graph->nodes[i].dist = now.dist + graph->vertices[now.vertex][i];
				graph->nodes[i].prev = now.vertex;
				insertToMinHeap(min_heap, i, graph->nodes[i].dist);
			}
		}
	}

	int end;
	for (end = 2; end <= graph->size; end++) {
		int *stack = calloc(graph->size, sizeof(int));
		int idx = 0, now = end;
		while (now != 1) {
			stack[idx++] = now;
			now = graph->nodes[now].prev;
		}
		printf("1");
		while (idx) {
			printf("->%d", stack[--idx]);
		}
		printf(" (cost: %d)\n", graph->nodes[end].dist);
	}
}

int main(int argc, char *argv[]) {
	FILE *ifp = fopen(argv[1], "r");
	Graph *graph;

	int size;
	fscanf(ifp, "%d", &size);
	graph = createGraph(size);

	int node1, node2, weight;
	while (fscanf(ifp, " %d-%d-%d", &node1, &node2, &weight) != EOF) {
		graph->vertices[node1][node2] = weight;
	}
	printShortestPath(graph);

	return 0;
}
