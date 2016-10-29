/*
 Name: Kevin Qian
 Lab: COEN 12 - Project 4
 Time: T 2:15 - 5:00
 Summary: Implementation for solving a maze game using linked lists to manage the stack
*/

#include<stdio.h>
#include<string.h> 
#include "deque.h"
#include<stdlib.h>
#include<assert.h>

typedef struct node NODE;
struct node{
	int data;
	NODE *next; 
	NODE *prev; 
};

struct deque{
	int count; 
	NODE *head;
};
// Create deque as a circular linked list. O(1)
DEQUE *createDeque(void)
{
	DEQUE *dp; 
	dp = malloc(sizeof(DEQUE));
	assert(dp!=NULL);
	dp->count=0;
	dp->head = malloc(sizeof(NODE));
	assert(dp->head != NULL);
	dp->head->next = dp->head;
	dp->head->prev = dp->head;
	return dp; 	

}

// Free nodes one by one starting from head->next. O(n)
void destroyDeque(DEQUE *dp)
{
	assert(dp!=NULL);
	NODE *freed = dp->head->next; 
	NODE *nextfree = freed->next;
	while(dp->count>0)
	{
		free(freed);
		freed=nextfree;
		nextfree = freed->next;
		dp->count--;
	}
}

// Count the number of items in deque. O(1)
int numItems(DEQUE *dp)
{
	assert(dp!=NULL);
	return dp->count;
}

// Add x as the first item in the deque pointed by dp.
// first item becomes new node following sentinel.
//O(1)
void addFirst(DEQUE *dp, int x)
{
	assert(dp!=NULL);
	NODE *add = malloc(sizeof(NODE));
	add->data = x;
	add->next = dp->head->next; 
	add->prev = dp->head; 
	dp->head->next->prev = add; 
	dp->head->next = add; 
	dp->count++;  
}
// Add x as the last item in the deque pointed by dp.
// Last item needs to point back to head to maintain circular linked list
// O(1)
void addLast(DEQUE *dp, int x)
{
	assert(dp!=NULL);
	NODE *add = malloc(sizeof(NODE));		
	add->data=x;
	add->next=dp->head;
	add->prev= dp->head->prev; 
	dp->head->prev->next=add;
	dp->head->prev=add;
	dp->count++;
}
// Set dummy node to avoid changing head pointer and remove first item following dummny node by freeing that node.
// O(1)
int removeFirst(DEQUE *dp)
{
	assert(dp!=NULL); 
	assert(dp->count>0);
	int data;  
	NODE *dummy = dp->head;
	NODE *del = dummy->next;
	dummy->next = dummy->next->next;
	del->next->prev = dummy; 
	data = del->data; 
	free(del);
	dp->count--;
	return data; 
}

// Access node to delete by calling the prev pointer from the dummy node.
// O(1)
int removeLast(DEQUE *dp)
{
	assert(dp!=NULL);
	assert(dp->count>0);
	int data;
	NODE *dummy = dp->head;
	NODE *del = dummy->prev;
	dummy->prev = dummy->prev->prev;
	del->prev->next=dummy;
	data = del->data;
	free(del);
	dp->count--;
	return data; 
}
// Get the value of the first node in linked list after the dummy node.
//O(1)
int getFirst(DEQUE *dp)
{
	assert(dp!=NULL);
	assert(dp->count>0);
	int data;
	data = dp->head->next->data;
	return data;
}

// Get the value of the last node in the linked list which is the previous node to the dummy node.
//O(1)
int getLast(DEQUE *dp)
{
	assert(dp!=NULL);
	assert(dp->count>0);
	int data;
	data = dp->head->prev->data;
	return data; 
}
