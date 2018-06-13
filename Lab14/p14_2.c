#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;

typedef struct Element {
	char is_valid;
	ElementType value;
} Element;

typedef struct HashTable {
	int table_size;
	Element *elements;
} HashTable;

Element *find(HashTable *hash_table, ElementType value) {
	int list_no = value % hash_table->table_size;
	int cnt = 0;
	while (hash_table->elements[list_no].is_valid == 1) {
		if (hash_table->elements[list_no].value == value) {
			return &hash_table->elements[list_no];
		}
		if (++cnt == hash_table->table_size) {
			return NULL;
		}
		list_no = (list_no + 1) % hash_table->table_size;
	}
	return NULL;
}

void insert(HashTable *hash_table, ElementType value) {
	int list_no = value % hash_table->table_size;
	if (hash_table->elements[list_no].is_valid == 1) {
		printf("%d insertion collision has been occured with number %d\n",
				value,
				hash_table->elements[list_no].value);
	}
	int cnt = 0;
	while (hash_table->elements[list_no].is_valid == 1) {
		if (hash_table->elements[list_no].value == value) {
			printf("%d is already in the table\n", value);
			return;
		}
		if (++cnt == hash_table->table_size) {
			printf("Table is full\n");
			return;
		}
		list_no = (list_no + 1) % hash_table->table_size;
	}
	hash_table->elements[list_no].is_valid = 1;
	hash_table->elements[list_no].value = value;
	printf("%d is inserted at address %d\n", value, list_no);
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
	hash_table->elements = (Element*)calloc(index_number, sizeof(Element));

	fgets(index, 100, ifp);
	ptr2 = strtok_r(index, " ", &ptrtmp[1]);
	while (ptr2 != NULL) {
		index_number = atoi(ptr2);
		insert(hash_table, index_number);
		ptr2 = strtok_r(NULL, " ", &ptrtmp[1]);
	}

	Element *tmp;
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
