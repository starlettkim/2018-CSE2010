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
	return (Node*)malloc(sizeof(Node));
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

	if (prev_key == -1) {
		newNode->next = head->next;
		head->next = newNode;
	} else {
		Node *np = find(head, key);
		if (np == NULL) {	// prev_key not found
			return 2;
		}
		newNode->next = np->next;
		np->next = newNode;	
	}
	
	return 0;
}

/* Delete the node with the key.
 * Returns	0 when succeeded,
 *			1 when key is not found.
 */
int delete(Node *head, KeyType key) {
	Node *pnp = head;		// previous node pointer
	Node *cnp = head->next;	// current node pointer
	while (cnp != NULL && cnp->key != key) {
		pnp = cnp;
		cnp = cnp->next;
	}
	if (cnp == NULL) {	// key not found
		return 1;
	}
	pnp->next = cnp->next;
	free(cnp);
	return 0;
}

/* Prints entire list by using standard output.
 */
void printList(Node *head) {
	Node *np = head->next;
	while (np != NULL) {
		printf("%d\t", np->key);
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
			int ret = insert(head, key, prev_key);
			if (ret == 1) {
				printf("Insertion failed with key(%d): Cannot allocate memory\n", key);
			} else if (ret == 2) {
				printf("Insertion failed with key(%d): Cannot find the key(%d).\n", key, prev_key);
			}

		} else if (cmd == 'd') {
			fscanf(ifp, "%d", &key);
			if (delete(head, key) == -1) {
				printf("Deletion(%d) failed.\n", key);
			}
		} else if (cmd == 'f') {
			fscanf(ifp, "%d", &key);
			int ret = findPrevious(head, key);
			if (ret == -1) {
				printf("Could not find previous node of the node with key %d.\n", key);
			} else {
				printf("Key of the previous node of %d is %d.\n", key, ret);
			}

		} else if (cmd == 'p') {
			printList(head);

		}
	}
	
	return 0;
}
