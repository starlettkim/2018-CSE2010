#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (a > b ? a : b)

struct AVLNode;
typedef struct AVLNode* AVLTree;
typedef int	ElementType;
typedef struct AVLNode {
	ElementType element;
	AVLTree left;
	AVLTree right;
	int height;
} AVLNode;

AVLTree insertNode(ElementType X, AVLTree T) {
	if (T == NULL) {
		AVLTree new_node = (AVLTree)calloc(1, sizeof(AVLNode));
		new_node->element = X;
		return new_node;
	}
	if (T->element > X) {
		T->left = insertNode(X, T->left);
		T->height = MAX(T->left->height + 1, T->height);
	} else if (T->element < X) {
		T->right = insertNode(X, T->right);
		T->height = MAX(T->right->height + 1, T->height);
	} else {
		fprintf(stderr, "Insertion error: There is already %d in the tree.\n", X);
	}
	return T;
}

void printInorder(AVLTree T) {
	if (T->left != NULL) {
		printInorder(T->left);
	}
	printf("%d(%d) ", T->element, T->height);
	if (T->right != NULL) {
		printInorder(T->right);
	}
}

void deleteTree(AVLTree T) {
	if (T == NULL) {
		return;
	}
	deleteTree(T->left);
	deleteTree(T->right);
	free(T);
}

int main(int argc, char **argv) {
	FILE *ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		fprintf(stderr, "There is no file: %s\n", argv[1]);
		exit(1);
	}
	AVLTree root = NULL;
	int element;
	while (fscanf(ifp, "%d", &element) != EOF) {
		root = insertNode(element, root);
		printInorder(root);
		printf("\n");
	}
	deleteTree(root);
	return 0;
}
