#include "priority_tree.h"

SrchTupleNode * createNode(int value){
    SrchTupleNode * newNode =  (SrchTupleNode *)malloc(sizeof(SrchTupleNode));
	uint32_t*	col_lenAr;
	char**		col_valAr;
    newNode->value = value;
    newNode->right= NULL;
    newNode->left = NULL;
    return newNode;
}
void insert_node(SrchTupleNode **sr, SrchTupleNode *new_node)
{
	int m = new_node->marks;
	while (*sr)
	{
	   if (m < (*sr)->marks)
		   sr = &(*sr)->left;
	   else
		   sr = &(*sr)->right;
	}
	*sr = new_node;
	new_node->left = new_node->right = NULL;
}
/*
void insert_node(SrchTupleNode **sr, SrchTupleNode *new_node)
{
	char exist = 0;
	int m = new_node->marks;
	while (*sr)
	{
	   if (m < (*sr)->marks)//1			5	6	7	8	9	10	11	12
		   sr = &(*sr)->left;
	   else if(m > (*sr)->marks)
		   sr = &(*sr)->right;
	   else if(new_node->id == (*sr)->id)	{ exist = 1; break;}
	   else sr = &(*sr)->right;
	}
	if(!exist)
	{
		*sr = new_node;
		new_node->left = new_node->right = NULL;
	}
	return exist;
}
*/
void get_smallest_node(SrchTupleNode *root,  SrchTwinNode *smallest)
{
		SrchTwinNode *small = smallest;
		SrchTupleNode *x, *p;
		p = x = root;
		while(x -> left != NULL) {p = x; x = x -> left; }
		small->par = p;
		small->node = x;
}

void del_smallest_node(SrchTupleNode **root,  SrchTwinNode *smallest)
{
		SrchTupleNode *x, *p;
		SrchTwinNode *small = smallest;	
		p = small->par;
		x = small->node;		
		
		if(p->left ) {
			if(x->right)	p->leftchild = x->right;
			else p -> left = NULL;
			 }
		else *root = p->right;		
		//free(x);		
}

///////////////////////////////////////////////////

void inorder_srch_desc(thr)
{
	int i=1;// because the first element contains the length.
	SrchTupleNode *root = thr->root;

	size_t ub		= thr->total_nodes-1;
	SrchTupleNode**		= thr->srch_nodeAr;

	SrchTupleNode *stack[STACK_SIZE];	int top = -1;
	SrchTupleNode *curNode  = root;
	while(top > -1 || curNode ){
		if(curNode)
		{
			stack[++top] = curNode;
			curNode = curNode->right;
		}
		else//12
		{
			curNode	= stack[ top--];
			SrchTupleNode[i++]	= curNode->scr;
			//printf("%d  ", curNode->value);
			curNode = curNode->left;
		}
	}
}


void clear_marks_array()
{
	for(int i=0; i<total_nodes; i++){
		WIDSIZE_T wid = dic_nodesAr[i]->wid;
		marksAr[wid&AI_BITS][wid&EI_BITS] = 0;
	}
}

