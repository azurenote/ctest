#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "compile.h"

#ifdef COMPILE_4

#define MAX_STRING 30


typedef struct element_t
{
	int id;
	char name[MAX_STRING];
	char address[MAX_STRING];
}element;
//typedef int element;

//implement of list//======================================

typedef struct DlistNode_t
{
	element data;
	struct DlistNode_t* perv;
	struct DlistNode_t* next;
} DlistNode;


typedef struct Dlist_t
{
	DlistNode* head;
	DlistNode* tail;
	int length;
} DlinkedList;

void error(char* msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

void list_initialize(DlinkedList* list)
{
	list->head = 0;
	list->tail = 0;
	list->length = 0;
}



DlistNode* list_at(DlinkedList* list, int pos)
{
	DlistNode* current;

	int i;

	current = list->head;

	for (i = 0; i < pos; ++i)
	{
		current = current->next;
	}

	return current;
}


DlistNode* list_create_node(element data)
{
	DlistNode* newnode;

	newnode = (DlistNode*) malloc(sizeof(DlistNode));

	memset(newnode, 0, sizeof(DlistNode));

	newnode->data = data;
	newnode->perv = 0;
	newnode->next = 0;

	return newnode;
}

int list_delete_node(DlinkedList* list, DlistNode* node)
{
	if (node->next != 0)
		node->next->perv = node->perv;
	if (node->perv != 0)
		node->perv->next = node->next;

	if (list->head == node)
		list->head = node->next;
	if (list->tail == node)
		list->tail = node->perv;

	node->next = 0;
	node->perv = 0;


	free(node);

	list->length--;

	return 0;
}


int list_delete_at(DlinkedList* list, int position)
{
	DlistNode* node = list_at(list, position);

	if (node == 0)
		error("access position err");

	return list_delete_node(list, node);
}




void list_add_after(DlinkedList* list, DlistNode* node, DlistNode* newnode)
{
	newnode->perv = node;

	if (node->next != 0)
	{
		node->next->perv = newnode;
		newnode->next = node->next;
	}
	if (list->tail == node)
	{
		list->tail = newnode;
	}

	node->next = newnode;

	list->length++;
}

void list_add_before(DlinkedList* list, DlistNode* node, DlistNode* newnode)
{
	newnode->next = node;

	if (node->perv != 0)
	{
		node->perv->next = newnode;
		newnode->perv = node->perv;
	}
	if (list->head == node)
	{
		list->head = newnode;
	}

	node->perv = newnode;

	list->length++;
}




void list_add(DlinkedList* list, int position, DlistNode* node)
{
	DlistNode* target = list_at(list, position);

	if (target == 0)
		error("access position err");

	list_add_after(list, target, node);
}

void list_add_first(DlinkedList* list, DlistNode* node)
{
	if (list->length == 0)
	{
		list->head = node;
		list->tail = node;
		list->length++;
	}
	else
		list_add_before(list, list->head, node);
}

void list_add_last(DlinkedList* list, DlistNode* node)
{
	if (list->length == 0)
	{
		list->head = node;
		list->tail = node;
		list->length++;
	}
	else
		list_add_after(list, list->tail, node);
}

void list_delete_node_at(DlinkedList* list, int position)
{
	DlistNode* target = list_at(list, position);

	if (target == 0)
		error("access position err");

	list_delete_node(list, target);
}


void list_destroy(DlinkedList* list)
{
	DlistNode* node;
	DlistNode* temp;

	node = list->tail;

	while (list->length > 0)
	{
		temp = node->perv;
		list_delete_node(list, node);

		node = temp;
	}
}


//end on list impl//========================================


void show_menu()
{
	puts("=========================================");
	puts(" 1. show all");
	puts(" 2. insert");
	puts(" 3. delete");
	puts(" 0. quit");
	puts("=========================================");
	printf("input menu no. : ");
}


void insert_item(DlinkedList* list, int increment)
{
	char temp[MAX_STRING] = {0};

	element data;

	DlistNode* node;

	int length;

	data.id = increment;

	puts("\n");
	puts("=========================================");
	puts("input name:");
	scanf("%s", temp);
	strcpy(data.name, temp);

	puts("input address:");
	scanf("%s", temp);
	strcpy(data.address, temp);

	node = list_create_node(data);

	if (node == 0)
		error("node creation failed");

	list_add_last(list, node);

	puts("new item added correctly\n");
}


void delete_item(DlinkedList* list)
{
	DlistNode* node;
	DlistNode* target;
	char temp[MAX_STRING] = {0};

	target = 0;

	if (list->length == 0)
	{
		puts("\n list is empty.");
		return;
	}

	puts("input name to delete");

	scanf("%s", temp);

	node = list->head;

	do
	{
		if (strcmp(node->data.name, temp) == 0)
		{
			target = node;
			break;
		}

		node = node->next;
	}
	while (node != 0);

	if (target == 0)
	{
		puts("not found.");
		return;
	}

	list_delete_node(list, target);

	
	puts("an item deleted.\n");
}


void show_all(DlinkedList* list)
{
	DlistNode* node;

	if (list->length == 0)
	{
		puts("\n list is empty.");
		return;
	}

	node = list->head;

	do
	{
		puts("--item---------------");
		printf("name\t: %s\n", node->data.name);
		printf("address\t: %s\n", node->data.address);
		puts("---------------------");
		node = node->next;
	}
	while (node != 0);

	printf("total %d items.\n\n", list->length);
}








//int main()
//{
//	DlinkedList list;
//	DlistNode* node;
//	DlistNode* temp;
//
//	element data;
//
//	int increment_counter = 0;
//
//	list_initialize(&list);
//
//
//	while (1)
//	{
//		int index;
//		show_menu();
//		scanf("%d", &index);
//
//		if (index == 0)
//			break;
//
//		switch(index)
//		{
//		case 1:
//			show_all(&list);
//			break;
//		case 2:
//			insert_item(&list, increment_counter);
//			increment_counter++;
//			break;
//		case 3:
//			delete_item(&list);
//			break;
//		}
//
//		//next
//	}
//
//
//	list_destroy(&list);
//
//	return 0;
//}

#endif