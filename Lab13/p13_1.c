#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
	int num;
	int **weight;
	int *check_visit;
} Graph;

typedef struct Stack {
	int *content;
	int top;
	int max_stack_size;
} Stack;

typedef struct CircularQueue {
	int *content;
	int first;
	int rear;
	int size;
	int max_size;
} Queue;

Graph *makeGraph(FILE *ifp) {
	if (ifp == NULL) return NULL;
	Graph *new_graph = (Graph*)calloc(1, sizeof(Graph));
	if (new_graph == NULL) return NULL;
	int num;
	fscanf(ifp, "%d ", &num);
	new_graph->num = num;
	new_graph->weight = (int**)calloc(num + 1, sizeof(int*));
	int i;
	for (i = 0; i <= num; i++)
		new_graph->weight[i] = (int*)calloc(num + 1, sizeof(int));
	new_graph->check_visit = (int*)calloc(num + 1, sizeof(int));
	return new_graph;
}

Queue *createQueue(int size) {
	Queue *new_queue = (Queue*)calloc(1, sizeof(Queue));
	if (new_queue == NULL) return NULL;
	new_queue->max_size = size;
	new_queue->size = 0;
	new_queue->first = 0;
	new_queue->rear = -1;
	new_queue->content = (int*)calloc(size, sizeof(int));
	if (new_queue->content == NULL) return NULL;
	return new_queue;
}

void enQueue(Queue *queue, int value) {
	if (queue->size == queue->max_size) return;
	queue->size++;
	queue->rear = (queue->rear + 1) % queue->max_size;
	queue->content[queue->rear] = value;
}

int deQueue(Queue *queue) {
	if (queue->size == 0) return -1;
	queue->size--;
	int ret = queue->content[queue->first];
	queue->first = (queue->first + 1) % queue->max_size;
	return ret;
}

void closeQueue(Queue *queue) {
	if (queue == NULL) return;
	if (queue->content != NULL)
		free(queue->content);
	free(queue);
}

int main(int argc, char *argv[]) {
	FILE *ifp = fopen(argv[1], "r");
	Graph *graph = makeGraph(ifp);
	
	int start, end;
	char c = 0;
	while (c != '\n') {
		fscanf(ifp, " %d-%d%c", &start, &end, &c);
		if (start < 1 || start > graph->num || end < 1 || end > graph->num) continue;
		graph->weight[start][end] = 1;
	}
	fscanf(ifp, " %d-%d", &start, &end);

	printf("BFS:");
	if (start < 1 || start > graph->num)
		printf(" cannot find");
	Queue *queue = createQueue(graph->num);
	enQueue(queue, start);
	graph->check_visit[start] = 1;
	int now;
	while (queue->size != 0) {
		now = deQueue(queue);
		printf(" %d", now);
		if (now == end) break;
		int i;
		for (i = 1; i <= graph->num; i++) {
			if (graph->weight[now][i] != 0 && graph->check_visit[i] == 0) {
				enQueue(queue, i);
				graph->check_visit[i] = 1;
			}
		}
	}

	if (end < 1 || end > graph->num || now != end)
		printf(" cannot find");
	printf("\n");
	return 0;
}
