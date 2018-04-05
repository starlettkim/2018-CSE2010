#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Tree {
	int value;
	struct Tree *left, *right;
} Tree;

Tree* insertNode(Tree *root, int key) {
	if (root == NULL) {
		Tree *node = (Tree *)malloc(sizeof(Tree));
		node->value = key;
		node->left = NULL;
		node->right = NULL;
		printf("Inserted: %d\n", key);
		return node;
	}
	if (root->value > key) {
		root->left = insertNode(root->left, key);
	} else if (root->value < key) {
		root->right = insertNode(root->right, key);
	} else {
		fprintf(stderr, "Insertion error: There is already %d in the tree.\n", key);
	}
	return root;
}

void printInorder(Tree *root) {
	if (root->left != NULL) {
		printInorder(root->left);
	}
	printf("%d ", root->value);
	if (root->right != NULL) {
		printInorder(root->right);
	}
}

int main(int argc, char **argv) {
	FILE *ifp;
	if (argc == 1) {
		ifp = stdin;		
	} else if (argc == 2) {
		ifp = fopen(argv[1], "r");
	} else {
		fprintf(stderr, "Error\n");
		return 1;
	}
	
	Tree *root = NULL;
	char cmd[3];
	while (fscanf(ifp, "%s", cmd) != EOF) {
		if (strcmp(cmd, "i") == 0) {
			int key;
			fscanf(ifp, "%d", &key);
			root = insertNode(root, key);
		} else if (strcmp(cmd, "pi") == 0) {
			printInorder(root);
		}
	}
	printf("\n");

	return 0;
}
