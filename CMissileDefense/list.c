#include "list.h"

void List_Push(ListNode **head,void *data,ListDeleteCallback deleteCallBack) {
	ListNode *listNode=malloc(sizeof(*listNode));
	listNode->data=data;
	listNode->active=true;
	listNode->next=(*head);
	listNode->deleteCallBack=deleteCallBack;
	(*head)=listNode;
}

void List_RemoveInactive(ListNode **head) {
    ListNode *temp=*head,*prev;

		while(temp!=NULL && !temp->active) {
        *head=temp->next;
        free(temp);
        temp=*head;
    }

    while(temp!=NULL) {
        while(temp!=NULL && temp->active) {
            prev=temp;
            temp=temp->next;
        }
        if (temp==NULL) return;
        prev->next=temp->next;
				temp->deleteCallBack(temp->data);
        free(temp);
        temp=prev->next;
    }
}

void List_Clear(ListNode **head) {
	ListNode *curr=*head,*next;
	while(curr) {
		next=curr->next;
		ListNode_Delete(curr);
		curr=next;
 	}
}

void ListNode_Delete(ListNode *node) {
	node->deleteCallBack(node->data);
	free(node);
	node=NULL;
}
