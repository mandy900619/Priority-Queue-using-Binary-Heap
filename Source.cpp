#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;

struct Heapnode {
	char chara = NULL;
	int order = NULL;
	Heapnode* rightnode = NULL, * leftnode = NULL, * parent = NULL;
	Heapnode* rightsibling = NULL;
};
Heapnode* ith_node(Heapnode* root, const size_t i)
{
	Heapnode* node = root;
	size_t  b = i;

	if (i == 1)
		return node;

	while (b & (b - 1))
		b &= b - 1;

	b >>= 1;

	while (b) {
		if (i & b) {
			if (node->rightnode)
				node = node->rightnode;
		}
		else {
			if (node->leftnode)
				node = node->leftnode;
		}

		b >>= 1;
	}

	return node;
}
void insert(char a, int ord, Heapnode** root, int nodeNUM) {
	Heapnode* currentnode;
	currentnode = ith_node(*root, nodeNUM);
	currentnode->leftnode = new Heapnode;
	currentnode->rightnode = new Heapnode;
	currentnode->rightnode->parent = currentnode;
	currentnode->leftnode->parent = currentnode;
	currentnode->chara = a;
	currentnode->order = ord;
	//sort
	while (currentnode->parent != NULL) {
		if (currentnode->order < currentnode->parent->order) {
			swap(currentnode->order, currentnode->parent->order);
			swap(currentnode->chara, currentnode->parent->chara);
			currentnode = currentnode->parent;
		}
		else {
			break;
		}
	}
}
void Delete(Heapnode** root, int nodeNUM) {
	Heapnode* currentnode;
	cout << (*root)->chara;
	currentnode = ith_node(*root, nodeNUM);
	(*root)->order = currentnode->order;
	(*root)->chara = currentnode->chara;
	currentnode->order = NULL;
	Heapnode* current = (*root);
	while (current->leftnode->order != NULL || current->rightnode->order != NULL) {
		if (current->leftnode->order != NULL && current->rightnode->order != NULL) {
			if (current->order > current->leftnode->order && current->order > current->rightnode->order) {
				if (current->leftnode->order > current->rightnode->order) {
					swap(current->order, current->rightnode->order);
					swap(current->chara, current->rightnode->chara);
					current = current->rightnode;
				}
				else {
					swap(current->order, current->leftnode->order);
					swap(current->chara, current->leftnode->chara);
					current = current->leftnode;
				}
			}
			else if (current->order > current->leftnode->order) {
				swap(current->order, current->leftnode->order);
				swap(current->chara, current->leftnode->chara);
				current = current->leftnode;
			}
			else if (current->order > current->rightnode->order) {
				swap(current->order, current->rightnode->order);
				swap(current->chara, current->rightnode->chara);
				current = current->rightnode;
			}
			else {
				break;
			}
		}
		else if (current->leftnode->order != NULL) {
			if (current->order > current->leftnode->order) {
				swap(current->order, current->leftnode->order);
				swap(current->chara, current->leftnode->chara);
				current = current->leftnode;
			}
			else {
				break;
			}
		}
		else {
			if (current->order > current->rightnode->order) {
				swap(current->order, current->rightnode->order);
				swap(current->chara, current->rightnode->chara);
				current = current->rightnode;
			}
			else {
				break;
			}
		}

	}
	
}
int main() {
	stringstream ss;
	ss.clear();
	ss.str("");
	int inputOrder;
	char inputCh;
	char trash;
	string input;
	Heapnode* root = NULL;
	int nodenum = 0;
	getline(cin, input);
	ss << input;
	while (ss >> inputCh >> inputOrder >> trash) {
		nodenum++;
		if (root == NULL) {
			root = new Heapnode;
			root->chara = inputCh;
			root->order = inputOrder;
			root->leftnode = new Heapnode;
			root->rightnode = new Heapnode;
			root->leftnode->parent = root;
			root->rightnode->parent = root;
		}
		else {
			insert(inputCh, inputOrder, &root, nodenum);
			//insert
		}
	}
	nodenum++;
	ss >> inputCh >> inputOrder;
	insert(inputCh, inputOrder, &root, nodenum);

	while (nodenum!=0)
	{
		if (nodenum == 1) {
			cout << root->chara;
			nodenum--;
		}
		else {
			Delete(&root, nodenum);
			nodenum--;
		}
	}
}