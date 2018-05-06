#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct _DisjointSets {
	int size_of_maze;
	int *array;
} DisjointSets;

void init(DisjointSets *sets, char wall[], int num) {
	sets->size_of_maze = num;
	sets->array = (int*)calloc(num * num, sizeof(int));
	int i;
	for (i = 0; i < num * num; i++) {
		sets->array[i] = i;
		wall[i] = 0;
	}
}

int find(DisjointSets *sets, int i) {
	if (sets->array[i] != i) {
		sets->array[i] = find(sets, sets->array[i]);
	}
	return sets->array[i];
}

void unionSets(DisjointSets *sets, int i, int j) {
	sets->array[find(sets, sets->array[i])] = find(sets, sets->array[j]);
}

// TODO: DFS로 Generate하니까 미로가 너무 쉬워짐.. 해결방법을 찾는 중
void dfs(DisjointSets *sets, char wall[], int num, int cur_pos) {
	if (cur_pos == num * num - 1) {
		wall[cur_pos] |= 1;
		return;
	}
	if (rand() % (num / 2) == 0) {
		return;
	}

	int dir[4], num_dir = 4;
	dir[0] = 1;
	dir[1] = num;
	dir[2] = -1;
	dir[3] = -num;
	
	int i;
	for (i = 0; i < 4; i++) {
		int index_picked_dir = rand() % num_dir--;
		int tmp = dir[index_picked_dir];
		dir[index_picked_dir] = dir[num_dir];
		dir[num_dir] = tmp;

		#define NEXT_POS (cur_pos + dir[num_dir])
		if (0 <= NEXT_POS && NEXT_POS < num * num && 
				!(cur_pos % num == 0 && dir[num_dir] == -1) &&
				!(cur_pos % num == num - 1 && dir[num_dir] == 1) &&
				find(sets, cur_pos) != find(sets, NEXT_POS)) {
			if      (dir[num_dir] == 1)    wall[cur_pos]  |= 1;
			else if (dir[num_dir] == num)  wall[cur_pos]  |= 1 << 1;
			else if (dir[num_dir] == -1)   wall[NEXT_POS] |= 1;
			else if (dir[num_dir] == -num) wall[NEXT_POS] |= 1 << 1; 
			unionSets(sets, cur_pos, NEXT_POS);
			dfs(sets, wall, num, NEXT_POS);
		}
		#undef NEXT_POS
	}
}

// (pseudo-)Randomly create maze using DFS with disjoint sets.
void createMaze(DisjointSets *sets, char wall[], int num) {
	int i, j;
	for (i = 0; i < num; i++) {
		for (j = 0; j < num; j++) {
			#define NOW (i * num + j)
			if (find(sets, 0) != find(sets, NOW)) {
				dfs(sets, wall, num, NOW);
			}
			#undef NOW
		}
	}
}

void printMaze(char wall[], int num) {
	int i, j;
	printf("┌───");
	for (i = 1; i < num; i++) {
		printf("%s───", wall[i - 1] & 1 ? "─" : "┬");
	}
	printf("┐\n");
	for (i = 0; i < num; i++) {
		#define NOW (i * num + j)
		printf("%s", i ? "│" : " ");
		for (j = 0; j < num; j++) {
			printf("   %s", wall[NOW] & 1 ? " " : "│");
		}
		printf("\n");
		char print_map[16][5] = { "ERR", "─", "│", "┌", "─", "─",
			"┐", "┬", "│", "└", "│", "├", "┘", "┴", "┤", "┼"};
		for (j = 0; j <= num; j++) {
			int print_value = 0;
			print_value |= (j != num && ((i == num - 1) || (wall[NOW] >> 1 == 0))) << 0;
			print_value |= (i != num - 1 && (j == 0 || j == num || (wall[NOW + num - 1] & 1) == 0)) << 1;
			print_value |= (j && ((i == num - 1) || (wall[NOW - 1] >> 1 == 0))) << 2;
			print_value |= (j == 0 || j == num || (wall[NOW - 1] & 1) == 0) << 3;
			printf("%s%s", print_map[print_value], (j == num || wall[NOW] >> 1) ? "   " : "───");
		}
		printf("\n");
		#undef NOW
	}
}

void freeMaze(DisjointSets *sets, char wall[]) {
	if (sets != NULL) {
		if (sets->array != NULL) {
			free(sets->array);
		}
		free(sets);
	}
}

int main(int argc, char *argv[]) {
	FILE *ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		fprintf(stderr, "Cannot open file: %s\n", argv[1]);
		return 1;
	}
	int num;
	fscanf(ifp, "%d", &num);
	
	DisjointSets *sets = (DisjointSets*)calloc(1, sizeof(DisjointSets));
	char *wall = (char*)calloc(num * num, sizeof(char));
	srand((unsigned int)time(NULL));
	
	init(sets, wall, num);
	createMaze(sets, wall, num);
	printMaze(wall, num);
	freeMaze(sets, wall);

	return 0;
}
