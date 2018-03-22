#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node *next;
} Node;

/* Insert the key next to the first node that has prev_key.
 * If prev_key is -1, insert the key next to the header node.
 * Returns 0 when succeeded, -1 when failed.
 */
int insert(Node *head, int key, int prev_key) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		return -1;
	}
	newNode->key = key;

	if (prev_key == -1) {
		newNode->next = head->next;
		head->next = newNode;
	} else {
		Node *np = head->next;
		while (np != NULL && np->key != prev_key) {
			np = np->next;
		}
		if (np == NULL) {	// prev_key not found
			return -1;
		}
		newNode->next = np->next;
		np->next = newNode;	
	}
	
	return 0;
}

/* Delete the node with the key.
 * Returns 0 when succeeded, -1 when failed.
 */
int delete(Node *head, int key) {
	Node *pnp = head;		// previous node pointer
	Node *cnp = head->next;	// current node pointer
	while (cnp != NULL && cnp->key != key) {
		pnp = cnp;
		cnp = cnp->next;
	}
	if (cnp == NULL) {	// key not found
		return -1;
	}
	pnp->next = cnp->next;
	free(cnp);
	return 0;
}

/* Print the key of the previous node of the node with the key.
 * Returns key of the previous node when succeeded, -1 when failed.
 */
int findPrevious(Node *head, int key) {
	Node *np = head;
	while (np->next != NULL && np->next->key != key) {
		np = np->next;
	}
	if (np->next == NULL || np == head) {
		return -1;
	}
	return np->key;
}

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
	Node *head = (Node*)malloc(sizeof(Node));
	if (ifp == NULL || head == NULL) {
		fprintf(stderr, "Error\n");
		return 1;
	}

	char cmd;
	while (fscanf(ifp, "%c", &cmd) != EOF) {
		int key, prev_key;
		if (cmd == 'i') {
			fscanf(ifp, "%d %d", &key, &prev_key);
			if (insert(head, key, prev_key) == -1) {
				printf("Insertion(%d) failed.\n", key);
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
