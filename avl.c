#ifndef _avltree_h

struct  avlnode;
typedef struct avlnode *position;
typedef struct avlnode *avltree;

avltree makeempty(avltree t);
position find(elementtype x, avltree t);
position findmin(avltree t);
position findmax(avltree t);
avltree insert(elementtype x, avltree t);
avltree delete(elementtype x, avltree t);
elementtype retrieve(position p);

#endif

struct avlnode
{
	elementtype element;
	avltree left;
	avltree right;
	int 	height;
};

static int height(position p)
{
	if (p == null)
		return -1;
	return p->height;
}

avltree insert(elementtype x, avltree t)
{
	
}