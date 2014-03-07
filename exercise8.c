#ifdef EXER8
#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define MAX_ELEMENT 200

#define ARRIVAL 1
#define ORDER 2
#define LEAVE 3

typedef struct{
	int key;
	int type;
	int number;
}element;

typedef struct{
	element heap[MAX_ELEMENT];
	int size;
}Heap;

Heap heap1;
int free_seats = 10;
double profit = 0;

void insert_max_heap(Heap* heap, element item)
{
	int i;
	i = ++(heap->size);

	while ((i != 1) && (item.key > heap->heap[i/2].key))
	{
		heap->heap[i] = heap->heap[i / 2];
		i /= 2;
	}

	heap->heap[i] = item;
}

void init(Heap* h)
{
	h->size = 0;
}

int is_empty(Heap* h)
{
	if (h->size == 0)
		return TRUE;
	else
		return FALSE;
}

void insert_min_heap(Heap* h, element item)
{
	int i;
	i = ++(h->size);
	while ((i != 1) && (item.key < h->heap[i/2].key))
	{
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(Heap* h)
{
	int parent, child;

	element item, temp;

	item = h->heap[1];
	temp = h->heap[h->size];

	h->size--;

	parent = 1;
	child  = 2;

	while (child <= h->size)
	{
		if ((child < h->size) &&
			(h->heap[child].key) > h->heap[child+1].key)
			child++;
		if (temp.key <= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

element delete_max_heap(Heap* h)
{
	int parent, child;

	element item, temp;

	item = h->heap[1];
	temp = h->heap[h->size];

	h->size--;

	parent = 1;
	child  = 2;

	while (child <= h->size)
	{
		if ((child < h->size) &&
			(h->heap[child].key) < h->heap[child+1].key)
			child++;
		if (temp.key >= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void main()
{
	element e1 = {10}, e2 = {5}, e3 = {30}, e4,e5,e6;

	Heap heap;

	init(&heap);

	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);

	e4 = delete_max_heap(&heap);
	printf("%d\n", e4.key);
	e5 = delete_max_heap(&heap);
	printf("%d\n", e5.key);
	e6 = delete_max_heap(&heap);
	printf("%d\n", e6.key);
}
#endif