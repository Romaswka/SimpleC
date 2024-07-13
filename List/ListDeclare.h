#ifndef _LIST_DECLARE_H_
#define _LIST_DECLARE_H_

#include "List.h"

struct Node;

typedef struct Node Node;

defineLinkType(Node);

struct _ListIterator
{
	Node* object;
};

struct Node
{
	Element value;
	Node* next;
};

struct _List
{
	Node *start, *end;
	Size count;
};

#define unpackSelf _List *self = (_List*)object.self; if(self == NULL) return False

#endif