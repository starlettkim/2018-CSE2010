#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode;
struct HashTable;

typedef int ElementType;
typedef struct ListNode* Position;

typedef struct ListNode {
	ElementType element;
	Position next;
} ListNode;

typedef struct HashTable {
	int table_size;
	ListNode **lists;
} HashTable;

Position find(HashTable *hash_table, ElementType element) {
	int list_no = element % hash_table->table_size;
	Position node = hash_table->lists[list_no];
	while (node != NULL) {
		if (node->element == element) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void insert(HashTable *hash_table, ElementType element) {
	if (find(hash_table, element) != NULL) {
		printf("%d is already in the table\n", element);
		return;
	}
	int list_no = element % hash_table->table_size;
	ListNode *first_node = hash_table->lists[list_no];
	ListNode *new_node = (ListNode*)calloc(1, sizeof(ListNode));
	new_node->element = element;
	if (first_node != NULL) {
		printf("%d insertion collision has been occurred with number %d\n",
				element,
				hash_table->lists[list_no]->element);
	}
	new_node->next = first_node;
	hash_table->lists[list_no] = new_node;
	printf("%d is inserted\n", element);
}

int main(int argc, char *argv[]) {
	FILE *ifp = fopen(argv[1], "r");
	char index[100];
	int index_number;
	char *ptr1, *ptr2, *ptr3;
	char *ptrtmp[3];

	fgets(index, sizeof(index) / sizeof(char), ifp);
	ptr1 = strtok_r(index, " ", &ptrtmp[0]);
	
	index_number = atoi(ptr1);
	HashTable *hash_table = (HashTable*)calloc(1, sizeof(HashTable));
	hash_table->table_size = index_number;
	hash_table->lists = (ListNode**)calloc(index_number, sizeof(ListNode*));
	int i;
	for (i = 0; i < index_number; i++) {
		hash_table->lists[i] = NULL;
	}

	fgets(index, 100, ifp);
	ptr2 = strtok_r(index, " ", &ptrtmp[1]);
	while (ptr2 != NULL) {
		index_number = atoi(ptr2);
		insert(hash_table, index_number);
		ptr2 = strtok_r(NULL, " ", &ptrtmp[1]);
	}

	Position tmp;
	fgets(index, 100, ifp);
	ptr3 = strtok_r(index, " ", &ptrtmp[2]);
	while (ptr3 != NULL) {
		index_number = atoi(ptr3);
		tmp = find(hash_table, index_number);
		printf("%d is %sin the table\n", index_number, (tmp == NULL ? "not " : ""));
		ptr3 = strtok_r(NULL, " ", &ptrtmp[2]);
	}

	return 0;
}
