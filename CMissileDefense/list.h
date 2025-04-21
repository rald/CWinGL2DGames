#ifndef MISSILELIST_H
#define MISSILELIST_H

#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

typedef void(*ListDeleteCallback)(void*);

typedef struct ListNode ListNode;
struct ListNode {
	void *data;
	bool active;
	struct ListNode *next;
	ListDeleteCallback deleteCallBack;
};

void List_Push(ListNode **head,void *data,ListDeleteCallback deleteCallBack);
void List_RemoveInactive(ListNode **head);
void List_Clear(ListNode **head);
void ListNode_Delete(ListNode *node);

#endif
