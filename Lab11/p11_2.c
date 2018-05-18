#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue {
	int *key;
	int first;
	int rear;
	int size;
	int max_queue_size;
};

struct _Graph {
	int size;
	int *node;
	int **matrix;
};

Graph createGraph(int nodes[], int num_nodes) {
	if (nodes == NULL) return NULL;
	Graph new_graph = (Graph)calloc(1, sizeof(struct _Graph));
	new_graph->size = num_nodes;
	new_graph->node = (int*)calloc(num_nodes, sizeof(int));
	new_graph->matrix = (int**)calloc(num_nodes, sizeof(int*));
	int i;
	for (i = 0; i < num_nodes; i++) {
		new_graph->node[i] = nodes[i];
		new_graph->matrix[i] = (int*)calloc(num_nodes, sizeof(int));
	}
	return new_graph;
}

void insertEdge(Graph graph, int a, int b) {
	if (graph == NULL) return;
	int a_index = -1, b_index = -1, i;
	for (i = 0; i < graph->size; i++) {
		if (graph->node[i] == a) a_index = i;
		if (graph->node[i] == b) b_index = i;
	}
	if (a_index < 0 || b_index < 0) return;
	graph->matrix[a_index][b_index] = 1;
}

void deleteGraph(Graph graph) {
	if (graph == NULL) return;
	int i;
	for (i = 0; i < graph->size; i++) {
		free(graph->matrix[i]);
	}
	free(graph->node);
	free(graph);
}

Queue createQueue(int max_size) {
	Queue new_queue = (Queue)calloc(1, sizeof(struct _Queue));
	new_queue->key = (int*)calloc(max_size, sizeof(int));
	new_queue->first = 0;
	new_queue->rear = -1;
	new_queue->size = 0;
	new_queue->max_queue_size = max_size;
	return new_queue;
}

int isEmpty(Queue queue) {
	return queue->size == 0;
}

int isFull(Queue queue) {
	return queue->size == queue->max_queue_size;
}

int deQueue(Queue queue) {
	if (isEmpty(queue)) return -1;
	queue->size--;
	int ret = queue->key[queue->first];
	queue->first = (queue->first + 1) % queue->max_queue_size;
	return ret;
}

void enQueue(Queue queue, int value) {
	if (isFull(queue)) return;
	queue->size++;
	queue->rear = (queue->rear + 1) % queue->max_queue_size;
	queue->key[queue->rear] = value;
}

void deleteQueue(Queue queue) {	
	free(queue->key);
	free(queue);
}

void topSort(Graph graph) {
	if (graph == NULL) return;
	int *in_degree = (int*)calloc(graph->size, sizeof(int));
	int i, j;
	for (i = 0; i < graph->size; i++)
		for (j = 0; j < graph->size; j++)
			in_degree[i] += graph->matrix[j][i];
	
	Queue queue = createQueue(graph->size);
	for (i = 0; i < graph->size; i++)
		if (in_degree[i] == 0)
			enQueue(queue, i);

	while (!isEmpty(queue)) {
		int node = deQueue(queue);
		printf("%d ", graph->node[node]);
		for (i = 0; i < graph->size; i++)
			if (graph->matrix[node][i] && --in_degree[i] == 0)
				enQueue(queue, i);
	}

	printf("\n");
	deleteQueue(queue);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage:\n$%s <input_file>\n", argv[0]);
		return 1;
	}
	FILE *ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		fprintf(stderr, "Cannot open file: %s", argv[1]);
		return 1;
	}

	char in;
	int *nodes = NULL, num_nodes = 0;
	while (fscanf(ifp, "%c", &in), in != '\n') {
		if (isdigit(in)) {
			num_nodes++;
			int *new_nodes = (int*)realloc(nodes, num_nodes * sizeof(int));
			nodes = new_nodes;
			nodes[num_nodes - 1] = in - '0';
		}
	}
	Graph graph = createGraph(nodes, num_nodes);

	int a, b;
	while (fscanf(ifp, " %d-%d", &a, &b) != EOF) {
		insertEdge(graph, a, b);
	}
	
	topSort(graph);
	
	return 0;
}
