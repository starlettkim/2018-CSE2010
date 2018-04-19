#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a, b) (a > b ? a : b)

struct AVLNode;
typedef struct AVLNode* AVLTree;
typedef struct AVLNode* Position;
typedef int	ElementType;
typedef struct AVLNode {
	ElementType element;
	AVLTree left;
	AVLTree right;
	int height;
} AVLNode;

int getHeight(Position node) {
	return node == NULL ? -1 : node->height;
}

int getMyHeight(Position node) {
	return MAX(getHeight(node->left), getHeight(node->right)) + 1;
}

int getHeightDiff(Position node) {
	return getHeight(node->left) - getHeight(node->right);
}

Position singleRotateWithLeft(Position node) {
	Position child = node->right;
	node->right = child->left;
	child->left = node;
	node->height = getMyHeight(node);
	child->height = getMyHeight(child);
	return child;
}

Position singleRotateWithRight(Position node) {
	Position child = node->left;
	node->left = child->right;
	child->right = node;
	node->height = getMyHeight(node);
	child->height = getMyHeight(child);
	return child;
}

Position doubleRotateWithLeft(Position node) {
	Position child = node->right;
	node->right = singleRotateWithRight(child);
	return singleRotateWithLeft(node);
}

Position doubleRotateWithRight(Position node) {
	Position child = node->left;
	node->left = singleRotateWithLeft(child);
	return singleRotateWithRight(node);
}

AVLTree insertNode(ElementType X, AVLTree T) {
	if (T == NULL) {
		AVLTree new_node = (AVLTree)calloc(1, sizeof(AVLNode));
		new_node->element = X;
		return new_node;
	}
	if (T->element > X) {
		T->left = insertNode(X, T->left);
	} else if (T->element < X) {
		T->right = insertNode(X, T->right);
	} else {
		fprintf(stderr, "Insertion error: There is already %d in the tree.\n", X);
	}
	
	// Rebalance the tree.
	if (getHeightDiff(T) > 1) {
		if (getHeightDiff(T->left) > 0)	{
			T = singleRotateWithRight(T);
		} else {
			T = doubleRotateWithRight(T);
		}
	} else if (getHeightDiff(T) < -1) {
		if (getHeightDiff(T->right) < 0) {
			T = singleRotateWithLeft(T);
		} else {
			T = doubleRotateWithLeft(T);
		}
	} else {
		T->height = getMyHeight(T);
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
