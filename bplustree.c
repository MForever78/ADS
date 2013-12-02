//wrong: **keys

#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 10000

typedef struct node
{
	void **children;
	int **keys;
	struct node *parent;
	int isLeaf;
	int numChild;
	struct node *next;
} node;

const int childSize = 3;

/* Search */

node *find();
node *findLeaf();

/* Intert */

node *newNode();
node *newLeaf();
node *newTree();
node *newRoot();
node *insert();
node *insertToParent();
node *insertToNodeSplit();
node *insertToLeafSplit();
void insertToNode();
void insertToLeaf();

/* Print */

void treePrint();

int main()
{
	int i, n;
	int num[MAXNUM];
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &num[i]);

	/* Insert one by one, judge the duplication */

	node *root = NULL;	

	printf("success\n");
	for (i = 0; i < n; i++){
		printf("inserting: %d\n", num[i]);
		root = insert(root, num[i]);
		printf("success\n");
	}
	treePrint(root);
}

node *find(node *root, int key)
{
	int i;
	node *leaf;
	leaf = findLeaf(root, key);
	if (leaf == NULL)
		return NULL;
	for (i = 0; i < leaf->numChild && leaf->keys[i] != key; i++){}
	if (i == leaf->numChild)
		return NULL;
	return (node *)leaf->children[i];
}

node *findLeaf(node *root, int key)
{
	node *nd;
	int i;
	if (root == NULL)
		return NULL;
	nd = root;
	while (nd->isLeaf == 0){
		for (i = 0; i < nd->numChild && nd->keys[i] <= key; i++){}
		nd = (node *)nd->children[i];
	}
	return nd;
}

node *SetNewNode()
{
	node *nd;
	nd = (node *)malloc(sizeof(node));
	nd->children = malloc(childSize * sizeof(void *));
	nd->keys = malloc(childSize * sizeof(int *));
	nd->parent = NULL;
	nd->numChild = 0;
	nd->isLeaf = 0;
	nd->next = NULL;
	return nd;
}

node *SetNewLeaf()
{
	node *leaf;
	leaf = SetNewNode();
	leaf->isLeaf = 1;
	return leaf;
}

node *SetNewTree(int *key)
{
	node *root;
	root = SetNewLeaf();
	root->children[0] = NULL;
	root->keys[0] = malloc(sizeof(int));
	root->keys[0] = key;
	root->children[childSize-1] = NULL;
	root->numChild++;
	return root;
}

node *SetNewRoot(node *l, node *r, int *key)
{
	node *root;
	root = SetNewNode();
	root->children[0] = l;
	root->children[1] = r;
	root->keys[0] = malloc(sizeof(int));
	root->keys[0] = key;
	root->numChild++;
	l->parent = root;
	r->parent = root;
	return root;
}

node *insert(node *root, int *key)
{
	node *leaf;
	int index;
	leaf = findLeaf(root, key);
	if (leaf == NULL){
		return SetNewTree(key);
	}
	for (index = 0; index < leaf->numChild && key < leaf->keys[index]; index++){}
	if (key == leaf->keys[index]){
		printf("Key %d is duplicated\n", *key);
	}
	if (leaf->numChild < childSize-1){
		insertToLeaf(leaf, index, key);
		return root;
	}
	return insertToLeafSplit(root, leaf, index, key);
}

void insertToLeaf(node *leaf, int index, int *key)
{
	int i;
	for (i = leaf->numChild; i > index; i--){
		leaf->keys[i] = leaf->keys[i-1];
		leaf->children[i] = leaf->children[i-1];
	}
	leaf->keys[index] = malloc(sizeof(int));
	leaf->keys[index] = key;
	leaf->numChild++;
}

node *insertToLeafSplit(node *root, node *leaf, int index, int *key)
{
	node *newLeaf;
	int *newKey, **tempKey;
	int i, split;

	tempKey = malloc(childSize * sizeof(int *));
	for (i = 0; i < childSize; i++){
		if (i == index){
			tempKey[i] = malloc(sizeof(int));
			tempKey[i] = key;
		}
		else if (i < index)
			tempKey[i] = leaf->keys[i];
		else
			tempKey[i] = leaf->keys[i-1];
	}

	split = childSize / 2;
	leaf->numChild = split;
	for (i = 0; i < split; i++)
		leaf->keys[i] = tempKey[i];

	newLeaf = SetNewLeaf();
	newLeaf->numChild = childSize - split;
	for (i = split; i < childSize; i++)
		newLeaf->keys[i - split] = tempKey[i];

	newLeaf->parent = leaf->parent;
	leaf->children[childSize-1] = newLeaf;
	free(tempKey);
	newKey = newLeaf->keys[0];
	return insertToParent(root, leaf, newLeaf, newKey);
}

node *insertToParent(node *root, node *l, node *r, int *key)
{
	node *parent;
	int index, i;
	parent = l->parent;

	if (parent == NULL){
		return SetNewRoot(l, r, key);
	}

	for (index = 0; index < parent->numChild && parent->children[index] != l; index++){}
	if (parent->numChild < childSize - 1){
		insertToNode(parent, r, index, key);
		return root;
	}
	return insertToNodeSplit(root, parent, r, index, key);
}

void insertToNode(node *nd, node *r, int index, int *key)
{
	int i;
	for (i = nd->numChild; i > index; i--){
		nd->keys[i] = nd->keys[i-1];
		nd->children[i+1] = nd->children[i];
	}
	nd->keys[index] = malloc(sizeof(int));
	nd->keys[index] = key;
	nd->children[index+1] = r;
	nd->numChild++;
}

node *insertToNodeSplit(node *root, node *nd, node *r, int index, int *key)
{
	int i, split;
	node **tempChild, *newNode, *child;
	int **tempKey, *newKey;
	tempChild = malloc((childSize + 1) * sizeof(node *));
	tempKey = malloc(childSize * sizeof(int *));

	for (i = 0; i < childSize+1; i++){
		if (i == index + 1)
			tempChild[i] = r;
		else if (i < index+1)
			tempChild[i] = nd->children[i];
		else
			tempChild[i] = nd->children[i-1];
	}
	for (i = 0; i < childSize; i++){
		if (i == index){
			tempKey[i] = malloc(sizeof(int));
			tempKey[i] = key;
		}
		else if (i < index)
			tempKey[i] = nd->keys[i];
		else
			tempKey[i] = nd->keys[i-1];
	}

	split = childSize % 2 ? childSize / 2 + 1 : childSize / 2;
	nd->numChild = split - 1;
	for (i = 0; i < split - 1; i++){
		nd->children[i] = tempChild[i];
		nd->keys[i] = tempKey[i];
	}
	nd->children[i] = tempChild[i];
	newKey = tempKey[i];

	newNode = SetNewNode();
	newNode->numChild = childSize - split;
	for (++i; i < childSize; i++){
		newNode->children[i - split] = tempChild[i];
		newNode->keys[i - split] = tempKey[i];
	}
	newNode->children[i - split] = tempChild[i];
	newNode->parent = nd->parent;
	for (i = 0; i <= newNode->numChild; i++){
		child = (node *)(newNode->children[i]);
		child->parent = newNode;
	}
	newNode->next = nd->next;
	nd->next = newNode;

	free(tempChild);
	free(tempKey);
	return insertToParent(root, nd, newNode, newKey);
}

void treePrint(node *root)
{
	node *p, *p1;
	int i;
	if (!root){
		return;
	}
	p = root;
	p1 = root;
	while (!p->isLeaf){
		printf("[");
		for (i = 0; i < p->numChild - 1; i++)
			printf("%d,", p->keys[i]);
		printf("%d]", p->keys[i]);
		p = p->next;
		if (!p){
			p1 = p1->children[0];
			p = p1;
			printf("\n");
		}
	}

	while (p){
		printf("[");
		for (i = 0; i < p->numChild - 1; i++)
			printf("%d,", p->keys[i]);
		printf("%d]", p->keys[i]);
		p = p->children[childSize - 1];
	}
	printf("\n");
}