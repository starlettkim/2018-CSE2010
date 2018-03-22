#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct Node {
	KeyType key;
	struct Node *next;
} Node;

/* Makes empty singly linked list.
 * Returns	pointer of head node	when succeeded,
 *			null pointer			when failed with allocating memory.
 */
Node* makeEmptyList() {
	Node* head = (Node*)malloc(sizeof(Node));
	head->key = -1;
	return head;
}

int isEmptyList(Node *head) {
	return head->next == NULL;
}

/* Finds the previous node of the node with arg[key].
 * Returns	pointer of the node	when succeeded,
 *			null pointer		when failed.
 */
Node* findPrevious(Node *head, KeyType key) {
	Node *np = head;
	while (np->next != NULL && np->next->key != key) {
		np = np->next;
	}
	if (np->next == NULL) {
		return NULL;
	}
	return np;
}

/* Finds the node with arg[key].
 * Returns	pointer of the node	when succeeded,
 *			null pointer		when failed.
 */
Node* find(Node *head, KeyType key) {
	if (key == -1) return head;
	Node *np = findPrevious(head, key);
	return (np == NULL ? NULL : np->next);
}

/* Insert the key next to the first node that has prev_key.
 * If prev_key is -1, insert the key next to the header node.
 * Returns	0 when succeeded,
 *			1 when failed to allocate memory,
 *			2 when prev_key is not found.
 */
int insert(Node *head, KeyType key, KeyType prev_key) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		return 1;
	}
	newNode->key = key;

	Node *np = find(head, prev_key);
	if (np == NULL) {	// prev_key not found
		return 2;
	}
	newNode->next = np->next;
	np->next = newNode;	
	
	return 0;
}

/* Delete the node with the key.
 * Returns	0 when succeeded,
 *			1 when key is not found.
 */
int delete(Node *head, KeyType key) {
	Node *pnp = findPrevious(head, key);	// Previous node pointer
	if (pnp == NULL) {
		return 1;
	}
	Node *cnp = pnp->next;					// Current node pointer
	pnp->next = cnp->next;
	free(cnp);
	return 0;
}

/* Prints entire list by using standard output.
 */
void printList(Node *head) {
	Node *np = head->next;
	while (np != NULL) {
		printf("%d ", np->key);
		np = np->next;
	}
	printf("\n");
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Error\n");
		return 1;
	}

	FILE *ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		fprintf(stderr, "Error while opening file: %s\n", argv[1]);
		return 1;
	}

	Node *head = makeEmptyList();
	if (head == NULL) {
		fprintf(stderr, "Failed to make empty list.\n");
		return 1;
	}

	char cmd;
	while (fscanf(ifp, "%c", &cmd) != EOF) {
		KeyType key, prev_key;
		if (cmd == 'i') {
			fscanf(ifp, "%d %d", &key, &prev_key);
			printf("Insertion - ");
			fflush(stdout);
			int ret = insert(head, key, prev_key);
			if (ret == 1) {
				printf("Error while inserting(%d): Cannot allocate memory.\n", key);
			} else if (ret == 2) {
				printf("Error while inserting(%d): Cannot find the key(%d).\n", key, prev_key);
			} else {
				printf("Successfully inserted the node with key(%d).\n", key);
			}

		} else if (cmd == 'd') {
			fscanf(ifp, "%d", &key);
			printf("Deletion - ");
			fflush(stdout);
			int ret = delete(head, key);
			if (ret == 1) {
				printf("Error while deleting(%d): Cannot find the key.\n", key);
			} else {
				printf("Successfully deleted the node with key(%d).\n", key);
			}

		} else if (cmd == 'f') {
			fscanf(ifp, "%d", &key);
			printf("Finding - ");
			fflush(stdout);
			Node *pnp = findPrevious(head, key);
			if (pnp == NULL) {
				printf("Could not find the key(%d).\n", key);
			} else if (pnp == head) {
				printf("The previous key of the key(%d) is header.\n", key);
			} else {
				printf("The previous key of the key(%d) is %d.\n", key, pnp->key);
			}

		} else if (cmd == 'p') {
			printf("Printing list - ");
			if (isEmptyList(head)) {
				printf("List is empty.\n");
			}
			printList(head);
		}
	}
	
	return 0;
}
