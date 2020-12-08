#include <iostream>
#include <math.h>
using namespace std;

struct Heapnode {
	char chara = NULL;
	int order = NULL;
	Heapnode* rightnode = NULL, * leftnode = NULL, * parent = NULL;
	Heapnode* rightsibling = NULL;
};
void insert(char a, int ord, Heapnode** root, int nextMode) {
	nextplace = new Heapnode;
	nextplace->rightnode->parent = nextplace;
	nextplace->leftnode->parent = nextplace;
	nextplace->chara = a;
	nextplace->order = ord;
	Heapnode *currentnode = nextplace;
	if (nextMode == 1) {
		nextplace = (*root)->leftnode;
		while (nextplace != NULL) {
			nextplace = nextplace->leftnode;
		}
	}
	else if (nextMode == 2) {
		nextplace = nextplace->parent->rightnode;
		currentnode->rightsibling = nextplace;
	}
	else {
		nextplace = nextplace->parent->rightsibling->leftnode;
		currentnode->rightsibling = nextplace;
	}
	//sort
	while (currentnode->order < currentnode->parent->order && currentnode->parent != NULL) {
		swap(currentnode->order, currentnode->parent->order);
		swap(currentnode->chara, currentnode->parent->chara);
	}
}
void Delete(Heapnode** root) {

}
Heapnode* nextplace;
Heapnode* ith_node(Heapnode* root, const size_t i)
{
	size_t  b = i;

	/* Sanity check: If no tree, always return NULL. */
	if (!root || i < 1)
		return NULL;

	/* If i is 1, we return the root. */
	if (i == 1)
		return root;

	/* Set b to the value of the most significant binary digit
	   set in b. This is a known trick. */
	while (b & (b - 1))
		b &= b - 1;

	/* We ignore that highest binary digit. */
	b >>= 1;

	/* Walk down the tree as directed by b. */
	while (b) {
		if (i & b) {
			if (root->rightnode)
				root = root->rightnode;
			else
				return NULL; /* Not a complete tree, or outside the tree. */
		}
		else {
			if (root->leftnode)
				root = root->leftnode;
			else
				return NULL; /* Not a complete tree, or outside the tree. */
		}

		/* Next step. */
		b >>= 1;
	}

	/* This is where we arrived at. */
	return root;
}
int main() {
	char inputOrder;
	char inputCh;
	char trash;
	Heapnode *root = NULL;
	int nodenum = 0;
	while (cin >> inputCh) {
		cin.ignore();
		inputOrder=getchar();
		trash = getchar();
		nodenum++;
		if (root == NULL) {
			root = new Heapnode;
			root->chara = inputCh;
			root->order = (int)inputOrder;
			nextplace = root->leftnode;
			root->leftnode->parent = root;
			root->rightnode->parent = root;
		}
		else {
			int n = 1;
			int level = 0;
			int count = 0;
			int mode = 0;
			int nextmode = 0;
			while (n < nodenum) {
				level++;
				count = pow(2, level);
				n += count;
			}
			if (nodenum == n + 1) {
				mode = 1;
				nextmode = 2;
			}
			else if (nodenum % 2 == 1) {
				mode = 2;
				nextmode = 1;
			}
			else if (nodenum % 2 == 0) {
				mode = 3;
				nextmode = 2;
			}//complete tree insert place
			insert(inputCh, inputOrder, &root, nextmode);
			 //insert

		}
	}
}